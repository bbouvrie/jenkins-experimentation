#ifndef WALKABLEMAPTESTCLASS_H
#define WALKABLEMAPTESTCLASS_H

#include "autotest.h"
#include "StrategicMaps/iswalkablemap.h"
#include "public_define.h"

class WalkableMapTestClass: public QObject
{
    Q_OBJECT

private slots:

    void init();
    void cleanup();
    void GivenFieldWhenCallingWalkableMapThenCheckOutput();
};

DECLARE_TEST(WalkableMapTestClass)

#endif // WALKABLEMAPTESTCLASS_H



