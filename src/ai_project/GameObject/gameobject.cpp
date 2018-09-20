
#include "gameobject.h"

GameObject::GameObject(Location location)
    : m_loc(location)
{

}

GameObject::~GameObject()
{

}


Location GameObject::getLocation() const  // function definition
{
    return m_loc;
}


