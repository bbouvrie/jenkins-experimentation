#ifndef TRAVELTIMEMAP_H
#define TRAVELTIMEMAP_H

#include "StrategicMaps/heatmap.h"
#include "StrategicMaps/iswalkablemap.h"
#include "public_define.h"

class  __declspec(dllexport) TravelTimeMap : public HeatMap
{
public:
   explicit TravelTimeMap(const HeatMap &myWalkableMap, Location loc);
private:
};

#endif // TRAVELTIMEMAP_H
