    #ifndef PLAYER_H
#define PLAYER_H

#include "gameobject.h"
//#include "public_define.h"
#include <string>
class Player: public GameObject
{
public:
    Player(Location loc, bool alive);
    bool isAlive() const;
private:
    Location m_loc;
    bool m_alive;  
};

#endif // PLAYER_H


