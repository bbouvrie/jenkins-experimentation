#ifndef LOCVEC_H
#define LOCVEC_H

#include "public_define.h"
#include <vector>

// Vragen:
// deze class zou eigenlijk moeten inheriten van de vector class
// had ik dat met een template kunnen doen?
// en hoe zorg je dan voor het specifieke geval dat je zorgt dat de vector alleen unieke elementen heeft?

class LocVec
{
public:
    explicit LocVec();
    explicit LocVec(const Location &loc);
    explicit LocVec(const std::vector<Location> &loc);
    void Add(const Location &loc);
    void Add(const std::vector<Location> &locVec);
    std::vector<Location> Get() const ;
    Location Get(const unsigned int &i) const ;
    // these should be overloaded from std::vector
    unsigned int size() const;
    void clear();
    //

//    using iterator = std::vector<Location>::iterator;
//    using const_iterator = std::vector<Location>::const_iterator;
//    iterator begin()
//    {
//      return m_LocVec.begin();
//    }

//    iterator end()
//    {
//      return m_LocVec.end();
//    }

//    const_iterator cbegin() const
//    {
//      return m_LocVec.cbegin();
//    }

//    const_iterator cend() const
//    {
//      return m_LocVec.cend();
private:
    std::vector<Location> m_LocVec;
};

#endif // LOCVEC_H






