#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "public_define.h"
#include <vector>
#include <string>


class __declspec(dllexport) GameObject
{
public:
    GameObject(Location location); // constructor
    virtual ~GameObject(); // destructor;
    Location getLocation() const;  // function declaration   
private:
    Location m_loc;    
};

#endif // GAMEOBJECT_H
