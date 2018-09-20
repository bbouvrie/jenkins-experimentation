#ifndef WALL_H
#define WALL_H

#include "gameobject.h"
#include "public_define.h"
#include <string>
#include <vector>

class Wall : public GameObject
{
public:
    explicit Wall(Location loc);  
private:
    Location m_loc; 
};

#endif // WALL_H

