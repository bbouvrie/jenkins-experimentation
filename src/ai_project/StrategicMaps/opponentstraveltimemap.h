// Map that takes the minimum of the travel times of your opponents to a tile
// if opponents cannot reach the tile the travel time is set to 100 (basically infinity)
// if the tile is not walkable, the travel time = 1..
// note this is currently a slightly naive map, it does not account for routes that become available when bombs disappear
#ifndef OPPONENTSTRAVELTIMEMAP_H
#define OPPONENTSTRAVELTIMEMAP_H

#include "StrategicMaps/heatmap.h"
#include "goofgamestate.h"

class __declspec(dllexport) OpponentsTravelTimeMap: public HeatMap
{
public:
    explicit OpponentsTravelTimeMap(const GoofGameState& myGameState);
};

#endif // OPPONENTSTRAVELTIMEMAP_H



