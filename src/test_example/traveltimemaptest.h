#ifndef TRAVELTIMEMAPTEST_H
#define TRAVELTIMEMAPTEST_H

#include "autotest.h"
#include "StrategicMaps/traveltimemap.h"
#include "public_define.h"

class TravelTimeMapTest: public QObject
{
    Q_OBJECT
private slots:
    void GivenEmptyMapWhenCallingTravelTimeMapThenCheckTravelTime();
};

DECLARE_TEST(TravelTimeMapTest)

#endif // TRAVELTIMEMAPTEST_H



