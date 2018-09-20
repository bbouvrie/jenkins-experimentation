#ifndef ISWALKABLEMAP_H
#define ISWALKABLEMAP_H

#include "StrategicMaps/heatmap.h"
#include "goofgamestate.h"
#include "public_define.h"

class __declspec(dllexport) IsWalkableMap : public HeatMap
{
public:
   explicit IsWalkableMap(const GoofGameState& myGameState); 
private:
};


#endif // ISWALKABLEMAP_H
