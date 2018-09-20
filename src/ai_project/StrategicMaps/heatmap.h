#ifndef HEATMAP_H
#define HEATMAP_H

#include "public_define.h"
#include <vector>

class HeatMap
{
public:
    explicit HeatMap(FieldLayout m_layout);
    explicit HeatMap(FieldLayout m_layout, int defaultValue); // constructor declaration with default value
    virtual ~HeatMap();

    unsigned int getIndexByLocation(Location loc) const;
    Location getLocationByIndex(unsigned int index) const;

    void setValueByIndex(int value, unsigned int index);
    void setValueByLocation(int value, Location loc);

    int getValueByIndex(unsigned int index ) const;
    int getValueByLocation( Location loc ) const;
    std::vector<int> getVector() const;

    unsigned int getLen() const;
    unsigned int getNCol() const;
    unsigned int getNRow() const;
    FieldLayout getLayout() const;
private: 
    FieldLayout m_Layout;
    std::vector<int> m_myMap;
    void IndexCheck(unsigned int index) const;
    void LocationCheck(Location loc) const;
};

#endif // HEATMAP_H
