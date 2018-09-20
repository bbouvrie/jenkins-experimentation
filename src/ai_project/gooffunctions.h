#ifndef GOOFFUNCTIONS_H
#define GOOFFUNCTIONS_H

#include "public_define.h"
#include "goofgamestate.h"


// declare free functions here:
std::vector<ActionType> ActionVectorUnion(const std::vector<ActionType> vecA, const std::vector<ActionType> vecB); // function declaration
Location UpdateLocationBasedOnGameState(const ActionType &action, const Location &oldLoc, const GoofGameState &myGS);
std::vector<Location> BombInfluence(const Bomb &myBomb, const GoofGameState &myGS);
//void locToIndex(Location loc, int nCol); // function declaration?


#endif // GOOFFUNCTIONS_H
