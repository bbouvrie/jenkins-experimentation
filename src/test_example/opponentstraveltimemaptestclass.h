#ifndef OPPONENTSTRAVELTIMEMAPTESTCLASS_H
#define OPPONENTSTRAVELTIMEMAPTESTCLASS_H


#include "autotest.h"
class OpponentsTravelTimeMapTestClass: public QObject
{
    Q_OBJECT
private slots:
    void GivenFieldWithThreeOpponentsWhenCallingOpponentsTravelTimeMapThenCheckResults();
};

DECLARE_TEST(OpponentsTravelTimeMapTestClass)

#endif // OPPONENTSTRAVELTIMEMAPTESTCLASS_H
