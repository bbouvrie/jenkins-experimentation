#include "offensiveactionselector.h"
#include "DecisionMaker/safeactionselector.h"
#include "DecisionMaker/randomaction.h"
#include "StrategicMaps/traveltimemap.h"
#include "StrategicMaps/iswalkablemap.h"
#include "gooffunctions.h"
//#include "bombinfluence.h"

OffensiveActionSelector::OffensiveActionSelector(const GoofGameState &myGS)
    : m_GS(myGS)
{

}

ActionType OffensiveActionSelector::GetAction() const
{
    // Initialize
    ActionType selectedAction = {};
    SafeActionSelector sAS = SafeActionSelector();
    std::vector<ActionType> safeActionsLockIn = sAS.GetActionVectorLockInSafe(m_GS);
    if(safeActionsLockIn.size() == 0)
    {
        // there are no lock in safe actions, do not attack...
        selectedAction = sAS.GetActionLockInSafe(m_GS);
    }
    else
    {
        selectedAction = GetOffensiveAction(safeActionsLockIn);
    }


    return selectedAction;
}

ActionType OffensiveActionSelector::GetOffensiveAction(const std::vector<ActionType> &sALI) const
{
    ActionType selectedAction = {};
    //Location myLoc = m_GS.getMe()->getLocation();

    // initialize value of every action at -100 (except if it is an action in sALI then set to 0
    std::vector<double> actionValue(6, -100);
    // std::vector<ActionType> allActions = {ActionType::Up, ActionType::Down, ActionType::Left, ActionType::Right, ActionType::Hold, ActionType::Bomb};
    for (auto e: sALI)
    {
        switch(e)
        {
        case ActionType::Up:    actionValue[0] = 0; break;
        case ActionType::Down:  actionValue[1] = 0; break;
        case ActionType::Left:  actionValue[2] = 0; break;
        case ActionType::Right: actionValue[3] = 0; break;
        case ActionType::Hold:  actionValue[4] = 0; break;
        case ActionType::Bomb:  actionValue[5] = 0; break;
        }
    }

    // see if you can blow up an opponent...
    std::vector<Location> LockInLocations = GetLockInLocation();
    actionValue = GetValueBlowingUpOpponent(actionValue, LockInLocations, sALI);

    // see if you can blow up crates
    actionValue = GetValueBlowingUpCrates(actionValue);

    // Get the action value at the solidification stage
    actionValue = GetValueAtSolidifcationStage(actionValue);

    // return the action with the highest value (in this case the first one to appear if there are multiple)
    selectedAction = SelectActionBasedOnValue(actionValue, sALI);


    //
    return selectedAction;
}

std::vector<Location> OffensiveActionSelector::GetLockInLocation() const
{
    // write a unit test: if an opponent is locked in, then you should not get every location as possible lock in:)
    //
    HeatMap walkMap = IsWalkableMap(m_GS);
    HeatMap myTravelTimeMap = TravelTimeMap(walkMap, m_GS.getMe()->getLocation());
    // not so nice implementation!
    SafeActionSelector sAS = SafeActionSelector( );
    //
    std::vector<Location> LockInLocations = {};
    // Now, for every opponent
    for (auto e : m_GS.getOpponents())
    {
        // std::vector<ActionType> safeActions = GetActionVector(e->getLocation(), m_GS);
        if(e->isAlive())
        {
            // first check if the opponent is not yet locked in
            GoofGameState myGScopyTEMP = GoofGameState(m_GS);
            std::vector<ActionType> safeActionsLocki = sAS.GetActionVector(e->getLocation(), myGScopyTEMP);
            if(safeActionsLocki.size() > 0)
            {
                // compute safeactions for opponent based on me...
                for (unsigned int i = 0; i < walkMap.getLen(); i++)
                {

                    if (myTravelTimeMap.getValueByIndex(i) >= 0 && myTravelTimeMap.getValueByIndex(i) < 100 )
                    {
                        // make a copy of the gamestate
                        GoofGameState myGScopy = GoofGameState(m_GS);
                        // add a bomb at the location with duration equal to traveltime + 1
                        myGScopy.addBomb(myTravelTimeMap.getLocationByIndex(i), myTravelTimeMap.getValueByIndex(i) + 1 + 4);
                        // Get the safe actions for this case at your location
                        std::vector<ActionType> safeActionsLocki = sAS.GetActionVector(e->getLocation(), myGScopy);
                        // if there is no safe action then this is a lock in location
                        if (safeActionsLocki.size() == 0)
                        {
                            LockInLocations.push_back(walkMap.getLocationByIndex(i));
                        }
                    }
                }
            }
        }
    }
    return LockInLocations;
}


std::vector<double> OffensiveActionSelector::GetValueBlowingUpOpponent(std::vector<double> &actionValue, const std::vector<Location> &LockInLocations, const std::vector<ActionType> &safeActions) const
{
    HeatMap walkMap = IsWalkableMap(m_GS);
    for (auto e_Actions : safeActions)
    {
        unsigned int iAction = 999;
        Location newLoc = m_GS.getMe()->getLocation();
        switch(e_Actions)
        {
        case ActionType::Up:     iAction = 0;  newLoc.y += -1; break;
        case ActionType::Down:   iAction = 1;  newLoc.y += 1; break;
        case ActionType::Left:   iAction = 2;  newLoc.x += -1; break;
        case ActionType::Right:  iAction = 3;  newLoc.x += 1; break;
        case ActionType::Hold:   iAction = 4;  break;
        case ActionType::Bomb:   iAction = 5;  break;
        }
        HeatMap tTrTime = TravelTimeMap(walkMap, newLoc);

        for (auto e : LockInLocations)
        {
            if(tTrTime.getIndexByLocation(e) > int(0))
            {
                actionValue[iAction] = std::max( actionValue[iAction], double(100 - tTrTime.getIndexByLocation(e)) );
            }
        }


     }

    // als we op een zo'n locatie zijn en we mogen een bom plaatsen -> plaats bom
    // hang een hoge waarde (>100) aan deze actie

    // anders:
    // Voor de overige loop acties:
    // bepaal de travel time tot de locatie
    // zet de waarde van deze actie als 100 - traveltime

    // right now, the program returns the actionValue vector
return actionValue;

}



std::vector<double> OffensiveActionSelector::GetValueBlowingUpCrates(std::vector<double> &actionValue) const
{
    Location myLoc = m_GS.getMe()->getLocation();
    if (actionValue[5] >= 0)
    {
        Bomb myBomb = Bomb(myLoc, 4);
        // BombInfluence bInfluence
        // = bInfluence.Get();
        std::vector<Location> bInfluenceVec = BombInfluence(myBomb, m_GS);
        unsigned int n_crates = 0;
        for (auto e:bInfluenceVec)
        {
            if (m_GS.hasCrate(e))
            {
                n_crates+= 1;
            }
        }
        actionValue[5]  += double(n_crates);
    }
    return actionValue;
}


std::vector<double> OffensiveActionSelector::GetValueAtSolidifcationStage(std::vector<double> &actionValue) const
{
    // if time step exceeds 500, prefer move actions that point to the middle of the board
    int timestep = m_GS.getTime();
    Location myLoc = m_GS.getMe()->getLocation();
    if (timestep >= 500)
    {
        double x_middle = (m_GS.getLayout().nCol-1)/2;
        double y_middle = (m_GS.getLayout().nRow-1)/2;
        std::vector<ActionType> moveActions = {ActionType::Up, ActionType::Down, ActionType::Left, ActionType::Right};
        for (auto e : moveActions)
        {
            unsigned int iActionVal = 10;
            double newVal = 0;
            switch(e)
            {
            case ActionType::Up:    iActionVal = 0; if(myLoc.y>y_middle){newVal = myLoc.y-y_middle;} break;
            case ActionType::Down:  iActionVal = 1; if(myLoc.y<y_middle){newVal = y_middle-myLoc.y;} break;
            case ActionType::Left:  iActionVal=  2; if(myLoc.x>x_middle){newVal = myLoc.x-x_middle;} break;
            case ActionType::Right: iActionVal = 3; if(myLoc.x<x_middle){newVal = x_middle - myLoc.x;} break;
            case ActionType::Hold:  iActionVal = 4;  break;
            default: break;
            }
            // only add values when the action is safe (i..e not -100)
            if(actionValue[iActionVal]>-100)
            {
                actionValue[iActionVal] += newVal;
            }
        }
    }
    return actionValue;
}


ActionType OffensiveActionSelector::SelectActionBasedOnValue(const std::vector<double> actionValueVector, const std::vector<ActionType> possibleActions) const
{
    ActionType selectedAction = {};
    // get the highest value
    double highestVal =-1;
    for (auto e : actionValueVector)
    {
        e = std::max(e, highestVal);
    }

    // get the element of possibleActions that have the highest value
    std::vector<ActionType> candidateActions = {};
    for (auto e : possibleActions)
    {
        unsigned int iActionVal = 0;
        switch(e)
        {
        case ActionType::Up:    iActionVal = 0;  break;
        case ActionType::Down:  iActionVal = 1;  break;
        case ActionType::Left:  iActionVal=  2;  break;
        case ActionType::Right: iActionVal = 3;  break;
        case ActionType::Hold:  iActionVal = 4;  break;
        case ActionType::Bomb:  iActionVal = 5;  break;
        }
        if(actionValueVector[iActionVal] >= highestVal)
            // QT complains that this is unsafe so I choose >= should give same result
        {
            candidateActions.push_back(e);
        }
    }

    // finally, select a random action from candidateActions
    RandomAction RA = RandomAction();
    selectedAction = RA.getAction(candidateActions);
    return selectedAction;

}
