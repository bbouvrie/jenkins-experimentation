#ifndef BOMB_H
#define BOMB_H

#include "gameobject.h"
#include "public_define.h"
#include <string>
#include <vector>

class Bomb : public GameObject
{
public:
    explicit  Bomb(Location loc, int duration);
    int getDuration() const;
    void updateDuration();
private:
    Location m_loc;  
    int m_duration;
};

#endif // BOMB_H

