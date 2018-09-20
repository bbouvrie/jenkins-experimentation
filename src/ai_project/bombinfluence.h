#ifndef BOMBINFLUENCE_H
#define BOMBINFLUENCE_H

#include "public_define.h"
#include "goofgamestate.h"

class BombInfluence
{
public:
    explicit BombInfluence(const Bomb &myBomb, const GoofGameState &myGS);
    std::vector<Location> Get() const;
private:
    std::vector<Location> m_bombInfluence;
};

#endif // BOMBINFLUENCE_H
