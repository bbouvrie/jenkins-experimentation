#ifndef BLASTMAPTESTCLASS_H
#define BLASTMAPTESTCLASS_H

#include "autotest.h"
#include "StrategicMaps/blastmap.h"

class BlastMapTestClass: public QObject
{
    Q_OBJECT


private slots:

    void init();
    void cleanup();

    void GivenEmptyFieldWithBombWhenCallingBlastMapThenCheckGivenBlasts();
    void GivenSimpleFieldWithTwoBombsWhenCallingBlastMapThenCheckGivenBlasts();
    //void GivenEmptyFieldWithTwoBombsWhenCallingBlastMapThenCheckGivenBlasts();
    void GivenWithBombsWhenCallingBlastMapThenCheckGivenBlastsAllDirections();
    void GivenFieldWithBombAndObjectsWhenCallingBlastMapThenCheckGivenBlasts();
private:
    double m_data;
};

DECLARE_TEST(BlastMapTestClass)

#endif // BLASTMAPTESTCLASS_H





