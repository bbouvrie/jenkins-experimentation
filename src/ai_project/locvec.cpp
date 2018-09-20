#include "locvec.h"

LocVec::LocVec()
    : m_LocVec()
{

}

LocVec::LocVec(const Location &loc)
    : m_LocVec(0, loc)
{

}

LocVec::LocVec(const std::vector<Location> &locvec)
    : m_LocVec(locvec)
{

}

void LocVec::Add(const Location &loc)
{
    bool isNew = 1;
    for (auto e : m_LocVec)
    {
        //if ( e.x == loc.x && e.y == loc.y )
        if(e == loc)
        {
            isNew = 0;
        }
    }
    if (isNew)
    {
        m_LocVec.push_back(loc);
    }

}

void LocVec::Add(const std::vector<Location> &locVec)
{
    for (auto e : locVec)
    {
        Add(e);
    }
}

std::vector<Location> LocVec::Get() const
{
    return m_LocVec;
}

Location LocVec::Get(const unsigned int &i) const
{
    return m_LocVec[i];
}

unsigned int LocVec::size() const
{
     return m_LocVec.size();
}

void LocVec::clear()
{
    m_LocVec.clear();
}

