#include "walkablemaptestclass.h"

void WalkableMapTestClass::init()
{

}

void WalkableMapTestClass::cleanup()
{

}

void WalkableMapTestClass::GivenFieldWhenCallingWalkableMapThenCheckOutput()
{
    //Given
    FieldLayout layout = {3,4};
    GoofGameState myGameState = GoofGameState(layout); // initialize playing field
    Location wallLoc1 = {0,0};   myGameState.addWall(wallLoc1);
    Location wallLoc2 = {1,0};   myGameState.addWall(wallLoc2);

    int duration = 2;
    Location bombLoc1 = {1,1};  myGameState.addBomb(bombLoc1, duration);
    Location bombLoc2 = {2,1};  myGameState.addBomb(bombLoc2, duration);
    Location bombLoc3 = {0,1};  myGameState.addBomb(bombLoc3, 5);

    Location crateLoc1 = {0,2};  myGameState.addCrate(crateLoc1);
    Location crateLoc2 = {2,2};  myGameState.addCrate(crateLoc2);

    Location solidifierLoc1 = {0,3};  myGameState.addSolidifier(solidifierLoc1,4);
    Location solidifierLoc2 = {1,3};  myGameState.addSolidifier(solidifierLoc2,0);
    // When
    IsWalkableMap myWalkableMap = IsWalkableMap(myGameState);

    std::vector<int> controlWalkMap(myWalkableMap.getLen(), 0);
    controlWalkMap[2] = 1;
    controlWalkMap[3] = 1;
    controlWalkMap[7] = 1;
    controlWalkMap[9] = 1;
    controlWalkMap[11] = 1;

    // Then
    bool vectorSame = controlWalkMap == myWalkableMap.getVector();
        QVERIFY2(vectorSame, "Walkable map did not return expected result");

}
