#include "blastmaptestclass.h"
#include "goofgamestate.h"
#include "StrategicMaps/iswalkablemap.h"
#include <vector>



void BlastMapTestClass::init( )
{
    m_data = 4.0;  
}

void BlastMapTestClass::cleanup()
{
    m_data = 0.0;   
}

void BlastMapTestClass::GivenEmptyFieldWithBombWhenCallingBlastMapThenCheckGivenBlasts()
{
    // Given
    FieldLayout layout = {7,7};
    GoofGameState myGameState = GoofGameState(layout); // initialize playing field
    Location bombLoc = {3,3}; // != middle, (2,2) = middle! but ok for now
    int duration = 2;
    myGameState.addBomb(bombLoc, duration);
    // When
    IsWalkableMap myWalkableMap = IsWalkableMap(myGameState);
    BlastMap myBlastMap = BlastMap(myWalkableMap, myGameState.getBombs());
    std::vector<int> myBlastVector = myBlastMap.getVector();
    std::vector<int> controlBlastVector(myBlastMap.getLen(), 100);
    controlBlastVector[3] = duration;
    controlBlastVector[10] = duration;
    controlBlastVector[17] = duration;
    controlBlastVector[24] = duration;
    controlBlastVector[31] = duration;
    controlBlastVector[38] = duration;
    controlBlastVector[45] = duration;
    controlBlastVector[21] = duration;
    controlBlastVector[22] = duration;
    controlBlastVector[23] = duration;
    controlBlastVector[25] = duration;
    controlBlastVector[26] = duration;
    controlBlastVector[27] = duration;
    //Then
    //QVERIFY2(controlBlastVector == controlBlastVector , "Blast map did not return expected result");
    bool vectorCheck = controlBlastVector == myBlastVector;
    QVERIFY2(vectorCheck , "Blast map did not return expected result");
}

void BlastMapTestClass::GivenSimpleFieldWithTwoBombsWhenCallingBlastMapThenCheckGivenBlasts()
{
    // Given
    FieldLayout layout = {8,1};
    GoofGameState myGameState = GoofGameState(layout); // initialize playing field
    Location bombLoc = {0,0};
    int duration = 1;
    myGameState.addBomb(bombLoc, duration);
    Location bombLoc2 = {3,0};
    int duration2 = 4;
    myGameState.addBomb(bombLoc2, duration2);
    // When
    IsWalkableMap myWalkableMap = IsWalkableMap(myGameState);
    BlastMap myBlastMap = BlastMap(myWalkableMap, myGameState.getBombs());
    std::vector<int> myBlastVector = myBlastMap.getVector();
    std::vector<int> controlBlastVector(myBlastMap.getLen(), 100);
    controlBlastVector[0] = 1;
    controlBlastVector[1] = 1;
    controlBlastVector[2] = 1;
    // actually don't know; does a blast stop at a bomb?
    controlBlastVector[3] = 1;
    controlBlastVector[4] = 4;
    controlBlastVector[5] = 4;
    controlBlastVector[6] = 4;
    //Then
    //QVERIFY2(controlBlastVector == controlBlastVector , "Blast map did not return expected result");
    bool vectorCheck = controlBlastVector == myBlastVector;
    QVERIFY2(vectorCheck , "Blast map did not return expected result");
}

void BlastMapTestClass::GivenWithBombsWhenCallingBlastMapThenCheckGivenBlastsAllDirections()
{
    // Given
    FieldLayout layout = {3,3};
    GoofGameState myGameState = GoofGameState(layout); // initialize playing field
    Location bombLoc1 = {0,0};    myGameState.addBomb(bombLoc1, 1);
    Location bombLoc2 = {2,0};    myGameState.addBomb(bombLoc2, 2);
    Location bombLoc3 = {0,2};    myGameState.addBomb(bombLoc3, 3);
    Location bombLoc4 = {2,2};    myGameState.addBomb(bombLoc4, 4);
    Location bombLoc5 = {1,1};    myGameState.addBomb(bombLoc5, 5);
    // When
    IsWalkableMap myWalkableMap = IsWalkableMap(myGameState);
    BlastMap myBlastMap = BlastMap(myWalkableMap, myGameState.getBombs());
    std::vector<int> myBlastVector = myBlastMap.getVector();
    std::vector<int> controlBlastVector(myBlastMap.getLen(), 100);
    controlBlastVector[0] = 1;
    controlBlastVector[1] = 1;
    controlBlastVector[2] = 1;
    // actually don't know; does a blast stop at a bomb?
    controlBlastVector[3] = 1;
    controlBlastVector[4] = 5;
    controlBlastVector[5] = 2;
    controlBlastVector[6] = 1;
    controlBlastVector[7] = 3;
    controlBlastVector[8] = 2;
    //Then
    //QVERIFY2(controlBlastVector == controlBlastVector , "Blast map did not return expected result");
    bool vectorCheck = controlBlastVector == myBlastVector;
    QVERIFY2(vectorCheck , "Blast map did not return expected result");
}

//void BlastMapTestClass::GivenEmptyFieldWithTwoBombsWhenCallingBlastMapThenCheckGivenBlasts()
//{
//    // Given
//    FieldLayout layout = {7,7};
//    GoofGameState myGameState = GoofGameState(layout); // initialize playing field
//    Location bombLoc = {3,3};
//    int duration = 4;
//    myGameState.addBomb(bombLoc, duration);
//    Location bombLoc2 = {3,6};
//    int duration2 = 2;
//    myGameState.addBomb(bombLoc2, duration2);
//    // When
//    IsWalkableMap myWalkableMap = IsWalkableMap(myGameState);
//    BlastMap myBlastMap = BlastMap(myWalkableMap, myGameState.getBombs());
//    std::vector<int> myBlastVector = myBlastMap.getVector();
//    std::vector<int> controlBlastVector(myBlastMap.getLen(), 100);
//    controlBlastVector[3] = duration;
//    controlBlastVector[10] = duration;
//    controlBlastVector[17] = duration;
//    controlBlastVector[24] = duration;
//    controlBlastVector[31] = duration2;
//    controlBlastVector[38] = duration2;
//    controlBlastVector[45] = duration2;
//    controlBlastVector[21] = duration;
//    controlBlastVector[22] = duration;
//    controlBlastVector[23] = duration;
//    controlBlastVector[25] = duration;
//    controlBlastVector[26] = duration;
//    controlBlastVector[27] = duration;
//    controlBlastVector[42] = duration2;
//    controlBlastVector[43] = duration2;
//    controlBlastVector[44] = duration2;
//    controlBlastVector[46] = duration2;
//    controlBlastVector[47] = duration2;
//    controlBlastVector[48] = duration2;
//    //Then
//    //QVERIFY2(controlBlastVector == controlBlastVector , "Blast map did not return expected result");
//    bool vectorCheck = controlBlastVector == myBlastVector;
//    QVERIFY2(vectorCheck , "Blast map did not return expected result");
//}

void BlastMapTestClass::GivenFieldWithBombAndObjectsWhenCallingBlastMapThenCheckGivenBlasts()
{
    // Given   
    FieldLayout layout = {5,5};
    GoofGameState myGameState = GoofGameState(layout); // initialize playing field
    Location bombLoc = {2,2};    int duration = 4;
    myGameState.addBomb(bombLoc, duration);
    Location wallLoc = {2,0};
    myGameState.addWall(wallLoc);
    Location crateLoc = {0,2};
    myGameState.addCrate(crateLoc);

    // When
    IsWalkableMap myWalkableMap = IsWalkableMap(myGameState);
    BlastMap myBlastMap = BlastMap(myWalkableMap, myGameState.getBombs());
    std::vector<int> myBlastVector = myBlastMap.getVector();

    std::vector<int> controlBlastVector(myBlastMap.getLen(), 100);
    controlBlastVector[11] = duration;
    controlBlastVector[12] = duration;
    controlBlastVector[13] = duration;
    controlBlastVector[14] = duration;
    controlBlastVector[7] = duration;
    controlBlastVector[17] = duration;
    controlBlastVector[22] = duration;
    //Then
    //QVERIFY2(controlBlastVector == controlBlastVector , "Blast map did not return expected result");
    bool vectorCheck = controlBlastVector == myBlastVector;
    QVERIFY2(vectorCheck , "Blast map did not return expected result");
}
