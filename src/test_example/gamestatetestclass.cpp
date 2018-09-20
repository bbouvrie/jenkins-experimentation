#include <QtTest>

#include "gamestatetestclass.h"
#include "GameObject/bomb.h"
#include "GameObject/solidifier.h"
#include "GameObject/wall.h"
#include "GameObject/crate.h"

void GameStateTestClass::GivenSomethingWhenRequestingSomethingThenThisShouldHappen() const
{
    bool d = 1;
    QVERIFY2(d, "Always passing an empty test");
}


void GameStateTestClass::TileFreeDetectionTest() const
{
    // Test outline:
    // create situations set
    bool passedTest = 1;

    FieldLayout layout = {5,5};
    GoofGameState myGameState = GoofGameState(layout); // initialize playing field

    // test 1 Check if tile 1,1 is free when nothing is added
    GoofGameState myGameStateTest1(myGameState); // copy construct temp game state
    Location myLoc = {1,1};


    bool notFreedetected = 0;
    bool wallDetected = 0;
    bool crateDetected = 0;

    for (unsigned int i_col = 0; i_col < layout.nCol; i_col++)
        for (unsigned int i_row = 0; i_row < layout.nRow; i_row++)
        {
            {
                myLoc.x = i_col; myLoc.y = i_row;
                bool isFree = myGameStateTest1.locationWalkable(myLoc);
                bool hasWall = myGameStateTest1.hasWall(myLoc);
                bool hasCrate = myGameStateTest1.hasCrate(myLoc);
                if (!isFree)  {   notFreedetected = 1; }
                if (hasWall)  {   wallDetected = 1;    }
                if (hasCrate) {   crateDetected = 1;   }

            }
        }
    if (wallDetected)
    {
        passedTest = 0;
        QVERIFY2(passedTest, "Empty game but I detected a wall");
    }

    if (crateDetected)
    {
        passedTest = 0;
        QVERIFY2(passedTest, "Empty game but I detected a crate");
    }

    if (notFreedetected)
    {
        passedTest = 0;
        QVERIFY2(passedTest, "Empty game but I detected objects");
    }



    // test 2 Now, add a wall and check if I only detect a wall
    GoofGameState myGameStateTest2(myGameState); // copy construct temp game state
    myLoc = {1,1};
    //
    notFreedetected = 0;
    wallDetected = 0;
    crateDetected = 0;
    myGameStateTest2.addWall(myLoc);

    // deze loop kan in een functie!
    for (unsigned int i_col = 0; i_col < layout.nCol; i_col++)
        for (unsigned int i_row = 0; i_row < layout.nRow; i_row++)
        {
            {
                myLoc.x = i_col; myLoc.y = i_row;
                bool isFree = myGameStateTest2.locationWalkable(myLoc);
                bool hasWall = myGameStateTest2.hasWall(myLoc);
                bool hasCrate = myGameStateTest2.hasCrate(myLoc);
                if (!isFree)  {   notFreedetected = 1; }
                if (hasWall)  {   wallDetected = 1;    }
                if (hasCrate) {   crateDetected = 1;   }

            }
        }
    if (!wallDetected)
    {
        passedTest = 0;
        QVERIFY2(passedTest, "I added wall but did not detect a wall");
    }

    if (crateDetected)
    {
        passedTest = 0;
        QVERIFY2(passedTest, "No crates added but I detected a crate");
    }

    if (!notFreedetected)
    {
        passedTest = 0;
        QVERIFY2(passedTest, "Not an empty game but I detected no objects");
    }
    //
    // test 3 Now, add a crate and check if I only detect a crate
    GoofGameState myGameStateTest3(myGameState); // copy construct temp game state
    myLoc = {1,1};
    //
    notFreedetected = 0;
    wallDetected = 0;
    crateDetected = 0;
    myGameStateTest3.addCrate(myLoc);

    for (unsigned int i_col = 0; i_col < layout.nCol; i_col++)
        for (unsigned int i_row = 0; i_row < layout.nRow; i_row++)
        {
            {
                myLoc.x = i_col; myLoc.y = i_row;
                bool isFree = myGameStateTest3.locationWalkable(myLoc);
                bool hasWall = myGameStateTest3.hasWall(myLoc);
                bool hasCrate = myGameStateTest3.hasCrate(myLoc);
                if (!isFree)  {   notFreedetected = 1; }
                if (hasWall)  {   wallDetected = 1;    }
                if (hasCrate) {   crateDetected = 1;   }

            }
        }
    if (wallDetected)
    {
        passedTest = 0;
        QVERIFY2(passedTest, "No walls but did detected a wall");
    }

    if (!crateDetected)
    {
        passedTest = 0;
        QVERIFY2(passedTest, "Crates added but I dit not detect a crate");
    }

    if (!notFreedetected)
    {
        passedTest = 0;
        QVERIFY2(passedTest, "Not an empty game but I detected no objects");
    }

    // Test 6 check bomb functionality
    GoofGameState myGameStateTest6(myGameState); // copy construct temp game state
    myLoc = {1,1};       myGameStateTest6.addBomb(myLoc, 1);
    whatIsOnField presenceLogic = CheckPlayingFieldForObjects(&myGameStateTest6);
    if (!presenceLogic.hasBomb)
    {
        passedTest = 0;
        QVERIFY2(passedTest, "No bomb detected while it was added");
    }
    if (presenceLogic.fieldIsEmpty)
    {
        passedTest = 0;
        QVERIFY2(passedTest, "Bomb added but field appears empty");
    }


}

void GameStateTestClass::GivenFieldWithBombsWhenUpdatingBombsThenCheckResult() const
{
    // Given
    FieldLayout layout = {3,3};
    GoofGameState myGameState = GoofGameState(layout); // initialize playing field
    Location bombloc1 = {0,0}; myGameState.addBomb(bombloc1, 4);
    Location bombloc2 = {0,1}; myGameState.addBomb(bombloc2, 1);
    Location bombloc3 = {0,2}; myGameState.addBomb(bombloc3, 0);
    // When
    myGameState.updateBombs();
    std::vector<Bomb*> bombVec = myGameState.getBombs();
    QVERIFY2(bombVec.size()==2, "Bombs updated but too many bombs in gamestate");
    QVERIFY2(bombVec[0]->getDuration() == 3, "First bomb duration wrong");
    QVERIFY2(bombVec[1]->getDuration() == 0, "Second bomb duration wrong");
}

void GameStateTestClass::GivenFieldWithBombsAndCrateWhenUpdatingBombsThenCheckResult() const
{
    // Given
    FieldLayout layout = {4,1};
    GoofGameState myGameState = GoofGameState(layout); // initialize playing field
    Location bombloc1 = {0,0}; myGameState.addBomb(bombloc1, 1);
    Location bombloc2 = {1,0}; myGameState.addBomb(bombloc2, 1);
    Location crateloc1 = {2,0}; myGameState.addCrate(crateloc1);
    Location crateloc2 = {3,0}; myGameState.addCrate(crateloc2);
    // When
    myGameState.updateBombs();
    std::vector<Crate*> crateVec = myGameState.getCrates();
    QVERIFY2(crateVec.size()==1, "Bombs updated but too many crates in gamestate");
    QVERIFY2(crateVec[0]->getLocation() == crateloc2, "crate not at the correct location");
}

void GameStateTestClass::GivenFieldWithSolidifiersWhenUpdatinSolidifiersThenCheckResult() const
{
    // Given
    FieldLayout layout = {3,3};
    GoofGameState myGameState = GoofGameState(layout); // initialize playing field
    Location solloc1 = {0,0}; myGameState.addSolidifier(solloc1, 4);
    Location solloc2 = {0,1}; myGameState.addSolidifier(solloc2, 2);
    Location solloc3 = {0,2}; myGameState.addSolidifier(solloc3, 1);
    Location solloc4 = {2,0}; myGameState.addSolidifier(solloc4, 0);
    // When
    myGameState.updateSolidifiers();
    std::vector<Solidifier*> solVec = myGameState.getSolidifier();
    std::vector<Wall*> walVec = myGameState.getWalls();
    Location walLoc = {0,2};
    QVERIFY2(solVec.size()==2, "Solidifiers updated but too many soldifiers in gamestate");
    QVERIFY2(solVec[0]->getDuration() == 3, "First sol duration wrong");
    QVERIFY2(solVec[1]->getDuration() == 1, "Second sol duration wrong");
    QVERIFY2(walVec[0]->getLocation() == walLoc, "No wall detected at Solidifier location when updating game state");
}

whatIsOnField GameStateTestClass::CheckPlayingFieldForObjects(const GoofGameState* myGameStateTest) const
{
    struct whatIsOnField outLogic; // initialize output struct
    Location myLoc;
    for (unsigned int i_col = 0; i_col < myGameStateTest->getLayout().nCol; i_col++)
        for (unsigned int i_row = 0; i_row < myGameStateTest->getLayout().nRow; i_row++)
        {
            {
                myLoc.x = int(i_col); myLoc.y = int(i_row);
                bool isFree = myGameStateTest->locationWalkable(myLoc);
                bool hasWall = myGameStateTest->hasWall(myLoc);
                bool hasCrate = myGameStateTest->hasCrate(myLoc);
                bool hasBomb = myGameStateTest->hasBomb(myLoc);
                if (!isFree)  {   outLogic.fieldIsEmpty = 0;}
                if (hasWall)  {   outLogic.hasWall= 1;   }
                if (hasCrate) {  outLogic.hasCrate = 1;  }
                if (hasBomb) {   outLogic.hasBomb = 1; }
            }
        }
    return outLogic;
}



