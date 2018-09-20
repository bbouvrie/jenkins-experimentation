#include "bomb.h"

Bomb::Bomb(Location loc, int duration)
    : GameObject(loc),
    m_loc(loc),   
  m_duration(duration)
{   
}


 int Bomb::getDuration() const
 {
     return m_duration;
 }

void Bomb::updateDuration()
 {
     m_duration += -1;
 }
