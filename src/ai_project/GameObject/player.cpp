#include "player.h"

Player::Player(Location loc, bool alive)
    : GameObject(loc)
    , m_loc(loc)
    , m_alive(alive)
{  
}


bool Player::isAlive() const
{
    return m_alive;
}
