#ifndef DUMMYTEST_H
#define DUMMYTEST_H

#include "autotest.h"

class DummyTest : public QObject
{
    Q_OBJECT
private slots:
    void GetNameTest();
    void GetActionTest();
};

//DECLARE_TEST(DummyTest)

#endif // DUMMYTEST_H
