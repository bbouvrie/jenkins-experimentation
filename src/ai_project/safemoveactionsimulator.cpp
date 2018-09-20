#include "safemoveactionsimulator.h"
#include "StrategicMaps/heatmap.h"
#include "GameObject/bomb.h"
#include "StrategicMaps/iswalkablemap.h"
#include "StrategicMaps/blastmap.h"

SafeMoveActionSimulator::SafeMoveActionSimulator(const GoofGameState& myGameState)
    : m_gameState(myGameState)
    , m_loc(myGameState.getMe()->getLocation())
{

}


std::vector<ActionType> SafeMoveActionSimulator::GetSafeMoveActions()
{
    std::vector<ActionType> safeActions = {};

    // Work from location m_loc
    std::vector<ActionType> possibleMoveActions = { ActionType::Up, ActionType::Down, ActionType::Left,ActionType::Right, ActionType::Hold};
    std::vector<Location> safeLocations = {m_loc};
    // std::vector<Bomb*> myBombsOriginal = m_gameState.getBombs();
    // std::vector<Bomb> myBombs = {};

    // get max duration of bombs
    int max_duration = getMaxDuration();


    int time = 0; // start at next time step
    GoofGameState myGSCopy = m_gameState;

    while (time < max_duration)
    {
        // update time
        time += 1;
        // update duration of bombs
        myGSCopy.updateBombs();
        // update walkable map
        HeatMap myWalkMap = IsWalkableMap(myGSCopy);
        HeatMap myBlastMap = BlastMap(myWalkMap, myGSCopy.getBombs());
        // Now, for every location in safeLocations....
        std::vector<Location> newSafeLocations = { };
        std::vector<ActionType> newSafeActions = {};
        for (auto e : safeLocations)
        {
            //
            std::vector<ActionType> newSafeActions = getActionsFromLoc(e, myGSCopy);
            //

            for (auto eMove : possibleMoveActions)
            {
                Location newLoc = e;
                switch(eMove)
                {
                case ActionType::Up    : newLoc.y += -1;  break;
                case ActionType::Down  : newLoc.y += 1;   break;
                case ActionType::Left  : newLoc.x += -1;  break;
                case ActionType::Right : newLoc.x += 1;   break;
                case ActionType::Hold  : break;
                default : continue;
                }
                if (newLoc.y >= 0 && newLoc.y < int(myGSCopy.getLayout().nRow) &&
                        newLoc.x >= 0 && newLoc.x < int(myGSCopy.getLayout().nCol) )
                {
                    // if walkable and blastmap = not 0
                    if (myWalkMap.getValueByLocation(newLoc) && myBlastMap.getValueByLocation(newLoc)>0)
                    {
                        newSafeLocations.push_back(newLoc);
                        newSafeActions.push_back(eMove);
                    }
                }
            }

        }
        // if there are safe locations....
        if (newSafeLocations.size()>0)
        {
            safeLocations = newSafeLocations;
        }


    }
    return safeActions;
}

// get max duration of bombs
int SafeMoveActionSimulator::getMaxDuration() const
{
    int max_duration = 0;
    for (auto e : m_gameState.getBombs())
    {
        max_duration = std::max( max_duration, e->getDuration() );
    }
    return max_duration;
}

std::vector<ActionType> SafeMoveActionSimulator::getActionsFromLoc(Location loc, GoofGameState myGSCopy) const
{
    std::vector<ActionType> possibleMoveActions = { ActionType::Up, ActionType::Down, ActionType::Left,ActionType::Right, ActionType::Hold};
    std::vector<ActionType> newSafeActions = { };
    //
    HeatMap myWalkMap = IsWalkableMap(myGSCopy);
    HeatMap myBlastMap = BlastMap(myWalkMap, myGSCopy.getBombs());
    //
    for (auto eMove : possibleMoveActions)
    {
        Location newLoc = loc;
        switch(eMove)
        {
        case ActionType::Up    : newLoc.y += -1;  break;
        case ActionType::Down  : newLoc.y += 1;   break;
        case ActionType::Left  : newLoc.x += -1;  break;
        case ActionType::Right : newLoc.x += 1;   break;
        case ActionType::Hold  : break;
        default : continue;
        }
        if (newLoc.y >= 0 && newLoc.y < int(myGSCopy.getLayout().nRow) &&
                newLoc.x >= 0 && newLoc.x < int(myGSCopy.getLayout().nCol) )
        {
            // if walkable and blastmap = not 0
            if (myWalkMap.getValueByLocation(newLoc) && myBlastMap.getValueByLocation(newLoc)>0)
            {
                //newSafeLocations.push_back(newLoc);
                newSafeActions.push_back(eMove);
            }
        }

    }
    return newSafeActions;
}
