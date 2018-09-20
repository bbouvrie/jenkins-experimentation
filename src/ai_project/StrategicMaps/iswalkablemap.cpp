#include "iswalkablemap.h"

IsWalkableMap::IsWalkableMap(const GoofGameState& myGameState )
    : HeatMap( HeatMap(myGameState.getLayout(), 1) )
{
    for (auto e : myGameState.getWalls())
    {
        this->setValueByLocation(0, e->getLocation()) ;
    }

    for (auto e : myGameState.getBombs())
    {
        if (e->getDuration() < 4)
            // bomb is not walkable if duration < 4 (otherwise it is still to be placed)
        {
            this->setValueByLocation(0, e->getLocation()) ;
        }

    }

    for (auto e : myGameState.getCrates())
    {
        this->setValueByLocation(0, e->getLocation()) ;
    }

    for (auto e : myGameState.getSolidifier())
    {
        //this->setValueByLocation(0, e->getLocation());
        if (e->getDuration() == 0)
        {
            this->setValueByLocation(0, e->getLocation());
        }
    }


}

