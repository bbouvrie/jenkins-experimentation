#include "safeactionselector.h"

#include "locvec.h"
#include "StrategicMaps/heatmap.h"
#include "StrategicMaps/iswalkablemap.h"
#include "StrategicMaps/blastmap.h"
#include "StrategicMaps/opponentstraveltimemap.h"
#include "DecisionMaker/randomaction.h"
#include "gooffunctions.h"

SafeActionSelector::SafeActionSelector( )
{

}

ActionType SafeActionSelector::getAction( ) const
{
    RandomAction RA = RandomAction();
    ActionType selectedAction = RA.getAction( );
    return selectedAction;
}


ActionType SafeActionSelector::getAction(const GoofGameState &myGS) const
{
    std::vector<ActionType> safeActions = GetActionVector(myGS);
    RandomAction RA = RandomAction();
    ActionType selectedAction = RA.getAction(safeActions);
    return selectedAction;
}

ActionType SafeActionSelector::GetActionLockInSafe(const GoofGameState &myGS) const
{
    std::vector<ActionType> safeActions = GetActionVectorLockInSafe(myGS);
    // if you cannot find a safe action w.r.t. lock in safety do something
    // but do not place a bomb!
    if (safeActions.size()==0)
    {
        std::vector<ActionType> safeActionsTemp = GetActionVector(myGS);
        // remove bomb action
        for (auto e : safeActionsTemp)
        {
            if (e != ActionType::Bomb)
            {
                safeActions.push_back(e);
            }
        }
    }
    // select a random action
    RandomAction RA = RandomAction();
    ActionType selectedAction = RA.getAction(safeActions);
    return selectedAction;
}



std::vector<ActionType> SafeActionSelector::GetActionVector(const GoofGameState & myGS) const
{
    std::vector<ActionType> safeActions = GetActionVector(myGS.getMe()->getLocation(), myGS);
    return safeActions;
}

std::vector<ActionType> SafeActionSelector::GetActionVector(const Location& myLoc, const GoofGameState & myGS) const
{
    // Initialization
    std::vector<ActionType> safeActions = {};
    std::vector<ActionType> AllActions = { ActionType::Up, ActionType::Down, ActionType::Left,ActionType::Right, ActionType::Hold, ActionType::Bomb};

    Location oldLoc = myLoc;

    // Check for every action whether it is safe.....
    for (auto e : AllActions)
    {
        // start from time = 0
        int time = 0;
        bool actionIsSafe = 0;
        bool stillAlive = 1;

        // Make a copy of the gamestate
        GoofGameState GSCopy = GoofGameState(myGS);

        // if you place a bomb, add it!
        if (e == ActionType::Bomb)
        {
            GSCopy.addBomb(oldLoc, 5);
        }

        // go to the next time step
        time += 1;
        // update the gamestate
        GSCopy.updateGameState();
        // get the walkable map and blast map
        HeatMap walkMap = IsWalkableMap(GSCopy);
        HeatMap blastMap = BlastMap(walkMap, GSCopy.getBombs());

        // compute the new location
        Location newLoc = UpdateLocationBasedOnGameState(e, oldLoc, GSCopy);

        // Check blast map at newLoc
        LocVec oldLocVec = LocVec();
        if (newLoc.x>=0 && newLoc.y >= 0 && newLoc.x < int(GSCopy.getLayout().nCol) && newLoc.y < int(GSCopy.getLayout().nRow))
        {

                switch(blastMap.getValueByLocation(newLoc))
                {
                case 0:   stillAlive = 0;  break;   // blast = 0 at your loc means your dead
                case 100: actionIsSafe = 1; safeActions.push_back(e); break; // blast = 100 means no blast in the future = safe!
                }


            oldLocVec.Add(newLoc);
        }
        else
        {
            stillAlive = 0;
        }

        // continue this while loop until you found safety or you are dead...
        while (stillAlive && !actionIsSafe)
        {
            // update time (not used yet)
            time += 1;
            // update the gamestate
            // GSCopy.updateBombs();
            GSCopy.updateGameState();
            // get the walkable map and blast map
            HeatMap walkMap = IsWalkableMap(GSCopy);
            HeatMap blastMap = BlastMap(walkMap, GSCopy.getBombs());

            // get vector with possible, reachable actions
            LocVec newLocVec = GetNewLocVec(oldLocVec, GSCopy);

            oldLocVec.clear();
            // iterate over newLocVec
            for (unsigned int i = 0; i < newLocVec.size(); i++)
            {
                Location e_loc = newLocVec.Get(i);
                // Check blast map at e_loc
                switch(blastMap.getValueByLocation(e_loc))
                {
                case 0:   break;   // blast = 0 at your loc means your dead (do nothing)
                case 100: actionIsSafe = 1; oldLocVec.Add(e_loc); break; // blast = 100 means no blast in the future = safe!
                default: oldLocVec.Add(e_loc); break;
                }
            }
            // clear new loc vec
            newLocVec.clear();

            // If the action is safe....
            if (actionIsSafe)
            {
                safeActions.push_back(e);
            }
            // If there are no locations with blastMap value > 0 you are dead
            if (oldLocVec.size() == 0)
            {
                stillAlive = 0;
            }
            // go to next while statement
        }
        // go to next action
    }
    return safeActions;
}


LocVec SafeActionSelector::GetNewLocVec(const LocVec &oldLocVec, const GoofGameState& myGS) const
{
    LocVec newLocVec = LocVec();
    std::vector<ActionType> ActionsToCheck = { ActionType::Up, ActionType::Down, ActionType::Left,ActionType::Right, ActionType::Hold};

    for (unsigned int i = 0; i < oldLocVec.size(); i++)
    {
        Location e_loc = oldLocVec.Get(i);
        for (auto eAction : ActionsToCheck)
        {
            // compute the new location (returns empty if it is not walkable)
            Location newLoc = UpdateLocationBasedOnGameState(eAction, e_loc, myGS);
            // returns (-1,-1) if invalid location else a new loc
            // add the location to newLocVec (makes sure that every lock in newLocVec is unique)
            if (newLoc.x>= 0 && newLoc.y >= 0)
            {
                newLocVec.Add(newLoc);
            }
        }
    }
    return newLocVec;
}

std::vector<ActionType> SafeActionSelector::GetActionVectorLockInSafe(const GoofGameState &myGS) const
{
    // Compute the opponents travel time map
    OpponentsTravelTimeMap oppTrTimeMap = OpponentsTravelTimeMap(myGS);

    // Initialize output vector
    std::vector<ActionType> safeActions = GetActionVector(myGS);

    // At every location, add a bomb with duration of opponents travel time + 1 and check the safe actions....
    for (unsigned int i = 0; i < oppTrTimeMap.getLen(); i++)
    {
        if (oppTrTimeMap.getValueByIndex(i) >= 0 && oppTrTimeMap.getValueByIndex(i) < 100 && safeActions.size()>0 )
        {
            // make a copy of the gamestate
            GoofGameState myGScopy = GoofGameState(myGS);
            // add a bomb at the location with duration equal to traveltime + 1
            myGScopy.addBomb(oppTrTimeMap.getLocationByIndex(i), oppTrTimeMap.getValueByIndex(i) + 1 + 4);
            // Get the safe actions for this case at your location
            std::vector<ActionType> safeActionsLocki = GetActionVector(myGScopy);
            // Take the union of both vectors....
            std::vector<ActionType> safeActionsOut = ActionVectorUnion(safeActions, safeActionsLocki);
            // replace safeActions with safeActionsOut
            safeActions = safeActionsOut;
        }
    }
    return safeActions;
}

