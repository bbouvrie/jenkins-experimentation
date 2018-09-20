#include "opponentstraveltimemap.h"
#include "StrategicMaps/traveltimemap.h"
#include "StrategicMaps/iswalkablemap.h"

OpponentsTravelTimeMap::OpponentsTravelTimeMap(const GoofGameState& myGameState)
    : HeatMap( HeatMap(myGameState.getLayout(), 100) )
{
    HeatMap waklableMap = IsWalkableMap(myGameState);
    for (auto e : myGameState.getOpponents())
    {
        if (e->isAlive())
        {
            HeatMap eTravelTimeMap = TravelTimeMap(waklableMap, e->getLocation());
            for (unsigned int i = 0; i < this->getLen(); i++)
            {
                int t_tr = eTravelTimeMap.getValueByIndex(i);
                if (t_tr < this->getValueByIndex(i))
                {
                    this->setValueByIndex(t_tr, i);
                }
            }
        }
    }
    // if a tile has -1 but is walkable, set the opptrtimemap to 100
   for (unsigned int i = 0; i < this->getLen(); i++)
   {
       if (this->getValueByIndex(i) == -1 && waklableMap.getValueByIndex(i))
       {
            this->setValueByIndex(100, i);
       }
   }

}
