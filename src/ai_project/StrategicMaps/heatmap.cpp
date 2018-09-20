#include "heatmap.h"
#include <public_define.h>


HeatMap::HeatMap(FieldLayout layout)
    :m_Layout(layout),
     m_myMap(layout.nCol*layout.nRow, 0) // by default construct with value 0
{

}

HeatMap::HeatMap(FieldLayout layout, int defaultValue)
    :m_Layout(layout),
     m_myMap(layout.nCol*layout.nRow,  defaultValue) // by default construct with value 0
{

}


HeatMap::~HeatMap( )
{

}

unsigned int HeatMap::getIndexByLocation(Location loc) const
{
    // check if the location is a valid location
    LocationCheck(loc);

    // Get the index
    unsigned int indexOut =  m_Layout.nCol*unsigned(loc.y) + unsigned(loc.x);
    // a vector's first element is 0 !

    return indexOut;
}

Location HeatMap::getLocationByIndex(unsigned int index) const
{
    // Check if this is a valid index
   IndexCheck(index);
    // Get the location
    int y = int(index/m_Layout.nCol);
    int x = int(index) - y*int(m_Layout.nCol);

    Location myLoc = {x, y};
    return myLoc;
}

void HeatMap::setValueByIndex(int value, unsigned int index)
{
    // check if this is a valid index
    IndexCheck(index);

    // set value
    m_myMap[index] = value;
}

void HeatMap::setValueByLocation(int value, Location loc)
{
    // check if this is a valid index
    LocationCheck(loc);

    unsigned int index = HeatMap::getIndexByLocation(loc);
    m_myMap[index] = value;
}

int HeatMap::getValueByIndex(unsigned int index ) const
{
    // check if this is a valid index
    IndexCheck(index);

    return m_myMap[index];
}

int HeatMap::getValueByLocation( Location loc ) const
{
    // check if this is a valid index
    LocationCheck(loc);

    unsigned int index = HeatMap::getIndexByLocation(loc);
    return m_myMap[index];
}

std::vector<int> HeatMap::getVector() const
{
    return m_myMap;
}


// Get layout info
FieldLayout HeatMap::getLayout() const
{
    return m_Layout;
}

unsigned int HeatMap::getLen() const
{
    return m_Layout.nCol*m_Layout.nRow;
}

 unsigned int HeatMap::getNCol() const
 {
      return m_Layout.nCol;
 }

 unsigned int HeatMap::getNRow() const
 {
      return m_Layout.nRow;
 }

 void HeatMap::IndexCheck(unsigned int index) const
 {
     if ( int(index) < 0)
     {
      throw std::invalid_argument("HeatMap::IndexCheck: index cannot benegative");
         // This is impossible by the way! Because index is unsigned!
     }

      if (index > this->getLen())
         // for a vector of 10, the element 9 is the last but is the size 9 as well?
     {
         throw std::invalid_argument("HeatMap::IndexCheck: Index points to location not in map");
     }

 }

 void HeatMap::LocationCheck(Location loc) const
 {
    if (loc.x < 0)
    {
        throw std::invalid_argument("HeatMap::LocationCheck: Given x value of location smaller than 0");
    }
    if (loc.x > int(m_Layout.nCol) - 1)
    {
        throw std::invalid_argument("HeatMap::LocationCheck:Given x value of location larger than number of columns");
    }
    if (loc.y < 0)
    {
        throw std::invalid_argument("HeatMap::LocationCheck:Given y value of location smaller than 0");
    }
    if (loc.y > int(m_Layout.nRow) - 1)
    {
        throw std::invalid_argument("HeatMap::LocationCheck:Given y value of location larger than number of rows");
    }
 }
