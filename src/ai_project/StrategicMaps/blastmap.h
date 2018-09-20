#ifndef BLASTMAP_H
#define BLASTMAP_H

#include "StrategicMaps/heatmap.h"
#include "GameObject/bomb.h"
#include "public_define.h"


class __declspec(dllexport) BlastMap : public HeatMap
{
public:
    explicit BlastMap(const HeatMap &myWalkableMap, std::vector<Bomb*> myBombs);
private:   
};

#endif // BLASTMAP_H
