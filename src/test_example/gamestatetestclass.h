#ifndef GAMESTATETESTCLASS_H
#define GAMESTATETESTCLASS_H

#include "autotest.h"
#include "goofgamestate.h"

struct whatIsOnField
{
    bool fieldIsEmpty = 1;
    bool hasCrate = 0;
    bool hasWall = 0;
    bool hasBomb = 0;
};


class GameStateTestClass: public QObject
{
    Q_OBJECT
private slots:
   void GivenSomethingWhenRequestingSomethingThenThisShouldHappen() const;
   void TileFreeDetectionTest() const;
   whatIsOnField CheckPlayingFieldForObjects(const GoofGameState* myGameStateTest) const;
   void GivenFieldWithBombsWhenUpdatingBombsThenCheckResult() const;
   void GivenFieldWithBombsAndCrateWhenUpdatingBombsThenCheckResult() const;
   void GivenFieldWithSolidifiersWhenUpdatinSolidifiersThenCheckResult() const;
};

DECLARE_TEST(GameStateTestClass)


#endif  // GAMESTATETESTCLASS_H

