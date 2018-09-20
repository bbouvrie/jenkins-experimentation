#include "StrategicMaps/traveltimemap.h"
#include "GoofBot.h"
#include <stdexcept>

TravelTimeMap::TravelTimeMap(const HeatMap &myWalkableMap, Location loc)
    : HeatMap( HeatMap(myWalkableMap.getLayout(), -1) )
{
    // Initialize
    std::vector<Location> currentLocs;
    currentLocs.push_back(loc);

    int currentTravelTime = 0;
    this->setValueByLocation(currentTravelTime, loc);
    bool notDone = 1;

    while (notDone)
    {
        currentTravelTime += 1; // increment travel time
        std::vector<Location> updateLocs;
        // For every current location ...
        for (auto e : currentLocs)
        {
            // 1) compute travel time (I could use get possible move actions functionality perhaps?) but I do not like to use the bot functionality here so sort of redefine
            std::vector<ActionType> tempActions = {ActionType::Up, ActionType::Down, ActionType::Left, ActionType::Right};

            for (auto el : tempActions)
            {
                Location newLoc = e;
                switch( el )
                {
                case ActionType::Up    : newLoc.y += -1; break;
                case ActionType::Down  : newLoc.y += 1;  break;
                case ActionType::Left  : newLoc.x += -1;  break;
                case ActionType::Right : newLoc.x += 1; break;
                default: throw std::invalid_argument("In TravelTimeMap::TravelTimeMap I got bomb or hold as possible move action");
                }
                // Check if we ware inside the playing field (otherwise getValueByLocation will give an error...
                if (newLoc.y >= 0 && newLoc.y < int( this->getNRow() ) &&
                        newLoc.x >= 0 && newLoc.x < int( this->getNCol())  )
                {
                    // Then,  also check if there is not yet a travel time filled out and if the tile is walkable
                    if (this->getValueByLocation(newLoc) == -1 &&
                            myWalkableMap.getValueByLocation(newLoc) )
                    {
                        // 3) if so,
                        //      a) fill out the travel time
                        //      b) add the loc to updateLocs
                        this->setValueByLocation(currentTravelTime, newLoc);
                        updateLocs.push_back(newLoc);
                    }
                }
            }
        }

        if (updateLocs.size()>0)
        {
            //currentLocs.clear();
            currentLocs = updateLocs; // is this allowed?
            updateLocs.clear();
        }
        else
        {
            notDone = 0;
        }


    }
}

