#include "solidifier.h"

Solidifier::Solidifier(Location loc, int duration)
    : GameObject(loc)
    , m_loc(loc)
    , m_duration(duration)
{
}

int Solidifier::getDuration() const
{
    return m_duration;
}

void Solidifier::updateDuration()
{
    m_duration += -1;
}

