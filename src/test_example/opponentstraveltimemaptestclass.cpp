#include "opponentstraveltimemaptestclass.h"
#include "public_define.h"
#include "goofgamestate.h"
#include "StrategicMaps/opponentstraveltimemap.h"
#include "StrategicMaps/heatmap.h"

void OpponentsTravelTimeMapTestClass::GivenFieldWithThreeOpponentsWhenCallingOpponentsTravelTimeMapThenCheckResults()
{
    // Given
    FieldLayout layout = {6,2};
    GoofGameState myGameState = GoofGameState(layout); // initialize playing field
    Location opLoc = {0, 0};     myGameState.addOpponent(opLoc, 1);
    Location opLoc1 = {3, 1};     myGameState.addOpponent(opLoc1, 1);
    Location opLoc2 = {5, 1};     myGameState.addOpponent(opLoc2, 0);
    Location wallLoc1 = {3,0};   myGameState.addWall(wallLoc1);
    Location wallLoc2 = {1,1};   myGameState.addWall(wallLoc2);
    // When
    // Initialize lockindangermap
    HeatMap myOppTravelTimeMap = OpponentsTravelTimeMap(myGameState);
    // Then
    std::vector<int> myOppTravelTimeVector = myOppTravelTimeMap.getVector();
    std::vector<int> checkVector(myOppTravelTimeMap.getLen(), -1);
    checkVector[0] = 0;
    checkVector[1] = 1;
    checkVector[2] = 2;
    checkVector[4] = 2;
    checkVector[5] = 3;
    checkVector[6] = 1;
    checkVector[8] = 1;
    checkVector[9] = 0;
    checkVector[10] = 1;
    checkVector[11] = 2;
    bool vectorCheck = checkVector == myOppTravelTimeVector;
    //
    QVERIFY2( vectorCheck , "Opponents travel time map not correctly constructed");
}
