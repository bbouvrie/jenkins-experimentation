#ifndef CRATE_H
#define CRATE_H

#include "gameobject.h"
#include "public_define.h"
#include <string>
#include <vector>

class Crate: public GameObject
{
public:
    explicit Crate(Location loc);
private:
    Location m_loc;  
};

#endif // CRATE_H


