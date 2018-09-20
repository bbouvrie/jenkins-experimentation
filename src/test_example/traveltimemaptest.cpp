#include "traveltimemaptest.h"

#include "goofgamestate.h"
#include "StrategicMaps/iswalkablemap.h"
#include <vector>

void TravelTimeMapTest::GivenEmptyMapWhenCallingTravelTimeMapThenCheckTravelTime()
{
    // Given
    FieldLayout layout = {3,3};
    GoofGameState myGameState = GoofGameState(layout); // initialize playing field
    Location myLoc = {0,0}; // != middle, (2,2) = middle! but ok for now
    myGameState.addMe(myLoc, 1);
    // When
    IsWalkableMap myWalkableMap = IsWalkableMap(myGameState);
    TravelTimeMap myTravelTimeMap = TravelTimeMap(myWalkableMap, myLoc); 
    //Then
    std::vector<int> myTravelTimeVector = myTravelTimeMap.getVector();
    std::vector<int> controlTravelTimeMap = {0, 1, 2, 1, 2, 3, 2, 3, 4};
    bool checkVector = controlTravelTimeMap == myTravelTimeVector;
    QVERIFY2( checkVector , "Travel Time Map did not return expected result");
}


