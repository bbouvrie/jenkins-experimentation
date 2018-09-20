#ifndef SAFEACTIONSELECTORTESTCLASS_H
#define SAFEACTIONSELECTORTESTCLASS_H

#include "autotest.h"

class SafeActionSelectorTestClass: public QObject
{
    Q_OBJECT
private slots:
    void GivenEmptyFieldWhenCallingGetActionVectorThenShouldGetAllActions();
    void GivenMiniFieldWhenCallingGetActionVectorThenShouldGetHold();
    void GivenMiniFieldWithWallsWhenCallingGetActionVectorThenShouldGetDownHoldBomb();
    void GivenFieldWithBombsWhenCallingGetActionVectorThenCheckAction();
    void GivenFieldWithBombsAndNoSafetyWhenCallingGetActionVectorThenCheckAction();
    void GivenSmallFieldWithOpponentWhenCallingGetActionVectorLockInSafeThenCheckAction();
    void GivenSmallFieldWithOpponentAndSolidifierWhenCallingGetActionVectorLockInSafeThenCheckAction();
    void GivenSmallFieldWithTwoOpponentWhenCallingGetActionVectorLockInSafeThenCheckAction();
    void GivenSmallFieldWithSolidifierWhenCallingGetActionVectorLockInSafeThenCheckIfNotHold() const;
};

DECLARE_TEST(SafeActionSelectorTestClass)

#endif // SAFEACTIONSELECTORTESTCLASS_H



