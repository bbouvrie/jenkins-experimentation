#ifndef SOLIDIFIER_H
#define SOLIDIFIER_H

#include "gameobject.h"
#include "public_define.h"
#include <string>

class Solidifier : public GameObject
{
public:
    explicit Solidifier(Location loc, int duration);
    int getDuration() const;
    void updateDuration();
private:
    Location m_loc;
    int m_duration;
};

#endif // SOLIDIFIER_H

