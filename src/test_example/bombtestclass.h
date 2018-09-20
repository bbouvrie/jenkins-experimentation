#ifndef BOMBTESTCLASS_H
#define BOMBTESTCLASS_H

#include "autotest.h"
#include "blastmap.h"

class BombTestClass
{
public:
    BombTestClass();
};

#endif // BOMBTESTCLASS_H



#ifndef TRAVELTIMEMAPTEST_H
#define TRAVELTIMEMAPTEST_H



class TravelTimeMapTest: public QObject
{
    Q_OBJECT
private slots:
    void GivenEmptyMapWhenCallingTravelTimeMapThenCheckTravelTime();
};

DECLARE_TEST(TravelTimeMapTest)

#endif // TRAVELTIMEMAPTEST_H
