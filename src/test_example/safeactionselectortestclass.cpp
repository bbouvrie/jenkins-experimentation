#include "safeactionselectortestclass.h"
#include "goofgamestate.h"
#include "public_define.h"
#include "DecisionMaker/safeactionselector.h"
#include <vector>

void SafeActionSelectorTestClass::GivenEmptyFieldWhenCallingGetActionVectorThenShouldGetAllActions()
{
    // Given
    FieldLayout layout = {3,3};
    GoofGameState myGameState = GoofGameState(layout); // initialize playing field
    Location myLoc = {1,1};  myGameState.addMe(myLoc, 1);
    // When
    SafeActionSelector SA = SafeActionSelector();
    std::vector<ActionType> selectedActions = SA.GetActionVector(myGameState);
    std::vector<ActionType> controlVector = {ActionType::Up, ActionType::Down, ActionType::Left,ActionType::Right,ActionType::Hold, ActionType::Bomb};
    // Then
    bool correctVectorReturned = selectedActions == controlVector;
    QVERIFY2(correctVectorReturned, "Not all actions returned at empty field");
}

void SafeActionSelectorTestClass::GivenMiniFieldWhenCallingGetActionVectorThenShouldGetHold()
{
    // Given
    FieldLayout layout = {1,1};
    GoofGameState myGameState = GoofGameState(layout); // initialize playing field
    Location myLoc = {0,0};  myGameState.addMe(myLoc, 1);
    // When
    SafeActionSelector SA = SafeActionSelector();
    std::vector<ActionType> selectedActions = SA.GetActionVector(myGameState);
    std::vector<ActionType> controlVector = {ActionType::Hold};
    // Then
    bool correctVectorReturned = selectedActions == controlVector;
    QVERIFY2(correctVectorReturned, "Not only hold returned at 1 by 1 field");
}

void SafeActionSelectorTestClass::GivenMiniFieldWithWallsWhenCallingGetActionVectorThenShouldGetDownHoldBomb()
{
    // Given
    FieldLayout layout = {3,3};
    GoofGameState myGameState = GoofGameState(layout); // initialize playing field
    Location myLoc = {1,1};  myGameState.addMe(myLoc, 1);
    Location wallLoc1 = {0,0};  myGameState.addWall(wallLoc1);
    Location wallLoc2 = {1,0};  myGameState.addWall(wallLoc2);
    Location wallLoc3 = {2,0};  myGameState.addWall(wallLoc3);
    Location wallLoc4 = {0,1};  myGameState.addWall(wallLoc4);
    Location wallLoc5 = {2,1};  myGameState.addWall(wallLoc5);
    Location wallLoc6 = {0,2};  myGameState.addWall(wallLoc6);
    // When
    SafeActionSelector SA = SafeActionSelector();
    std::vector<ActionType> selectedActions = SA.GetActionVector(myGameState);
    std::vector<ActionType> controlVector = {ActionType::Down,ActionType::Hold, ActionType::Bomb};
    // Then
    bool correctVectorReturned = selectedActions == controlVector;
    QVERIFY2(correctVectorReturned, "Not down, hold, bomb, returned at small field with walls");
}

void SafeActionSelectorTestClass::GivenFieldWithBombsWhenCallingGetActionVectorThenCheckAction()
{
    // Given
    FieldLayout layout = {4,2};
    GoofGameState myGameState = GoofGameState(layout); // initialize playing field
    Location myLoc = {2,1};  myGameState.addMe(myLoc, 1);
    Location bombLoc1 = {1,0};  myGameState.addBomb(bombLoc1, 1);
    Location bombLoc2 = {3,1};  myGameState.addBomb(bombLoc2, 3);
    Location wallLoc1 = {0,0};  myGameState.addWall(wallLoc1);
    Location wallLoc2 = {2,0};  myGameState.addWall(wallLoc2);
    Location wallLoc3 = {3,0};  myGameState.addWall(wallLoc3);
    // When
    SafeActionSelector SA = SafeActionSelector();
    std::vector<ActionType> selectedActions = SA.GetActionVector(myGameState);
    std::vector<ActionType> controlVector = {ActionType::Hold, ActionType::Bomb};
    // Then
    bool correctVectorReturned = selectedActions == controlVector;
    QVERIFY2(correctVectorReturned, "Not hold, bomb, returned at small field with bombs");
}

void SafeActionSelectorTestClass::GivenFieldWithBombsAndNoSafetyWhenCallingGetActionVectorThenCheckAction()
{
    // Given
    FieldLayout layout = {4,2};
    GoofGameState myGameState = GoofGameState(layout); // initialize playing field
    Location myLoc = {2,1};  myGameState.addMe(myLoc, 1);
    Location bombLoc1 = {1,0};  myGameState.addBomb(bombLoc1, 1);
    Location bombLoc2 = {3,1};  myGameState.addBomb(bombLoc2, 2);
    Location wallLoc1 = {0,0};  myGameState.addWall(wallLoc1);
    Location wallLoc2 = {2,0};  myGameState.addWall(wallLoc2);
    Location wallLoc3 = {3,0};  myGameState.addWall(wallLoc3);
    // When
    SafeActionSelector SA = SafeActionSelector();
    std::vector<ActionType> selectedActions = SA.GetActionVector(myGameState);
    std::vector<ActionType> controlVector = { };
    // Then
    bool correctVectorReturned = selectedActions == controlVector;
    QVERIFY2(correctVectorReturned, "Not empty vector returned when there is no safety");
}

void SafeActionSelectorTestClass::GivenSmallFieldWithOpponentWhenCallingGetActionVectorLockInSafeThenCheckAction()
{
    // Given
    FieldLayout layout = {4,3};
    GoofGameState myGameState = GoofGameState(layout); // initialize playing field
    Location myLoc = {1,1};  myGameState.addMe(myLoc, 1);
    Location OppLoc = {1,2};  myGameState.addOpponent(OppLoc, 1);
    Location wallLoc1 = {0,0};  myGameState.addWall(wallLoc1);
    Location wallLoc2 = {2,0};  myGameState.addWall(wallLoc2);
    Location wallLoc3 = {0,2};  myGameState.addWall(wallLoc3);
    Location wallLoc4 = {2,2};  myGameState.addWall(wallLoc4);
    Location wallLoc5 = {3,2};  myGameState.addWall(wallLoc5);
    // When
    SafeActionSelector SA = SafeActionSelector();
    std::vector<ActionType> selectedActions = SA.GetActionVectorLockInSafe(myGameState);
    std::vector<ActionType> controlVector = {ActionType::Up, ActionType::Down, ActionType::Left,ActionType::Right,ActionType::Hold};
    // in this case, placing a bomb is not safe (the opponent is able to put a bomb at 3,1 so that both will die
    // Then
    bool correctVectorReturned = selectedActions == controlVector;
    QVERIFY2(correctVectorReturned, "Not empty vector returned when there is no safety");
}


void SafeActionSelectorTestClass::GivenSmallFieldWithOpponentAndSolidifierWhenCallingGetActionVectorLockInSafeThenCheckAction()
{
    // Given
    FieldLayout layout = {3,2};
    GoofGameState myGameState = GoofGameState(layout); // initialize playing field
    Location myLoc = {2,1};  myGameState.addMe(myLoc, 1);
    Location OppLoc = {1,1};  myGameState.addOpponent(OppLoc, 1);
    Location wallLoc1 = {0,0};  myGameState.addWall(wallLoc1);
    Location wallLoc2 = {2,0};  myGameState.addWall(wallLoc2);
    Location solLoc1 = {2,0};  myGameState.addSolidifier(solLoc1,2);
    // When
    SafeActionSelector SA = SafeActionSelector();
    std::vector<ActionType> selectedActions = SA.GetActionVectorLockInSafe(myGameState);
    std::vector<ActionType> controlVector = { };
    // in this case, there is no safety w.r.t. lock in)
    bool correctVectorReturned = selectedActions == controlVector;
    QVERIFY2(correctVectorReturned, "Not empty vector returned when there is no lock-in safety");
}



void SafeActionSelectorTestClass::GivenSmallFieldWithTwoOpponentWhenCallingGetActionVectorLockInSafeThenCheckAction()
{
    // Given
    FieldLayout layout = {5,5};
    GoofGameState myGameState = GoofGameState(layout); // initialize playing field
    Location myLoc = {2,3};  myGameState.addMe(myLoc, 1);
    Location OppLoc = {2,3};  myGameState.addOpponent(OppLoc, 1);
    Location OppLoc2 = {2,1};  myGameState.addOpponent(OppLoc2, 1);
    Location wallLoc1 = {1,2};  myGameState.addWall(wallLoc1);
    Location wallLoc2 = {3,2};  myGameState.addWall(wallLoc2);

    // When
    SafeActionSelector SA = SafeActionSelector();
    std::vector<ActionType> selectedActions = SA.GetActionVectorLockInSafe(myGameState);
    std::vector<ActionType> controlVector = {ActionType::Down, ActionType::Left, ActionType::Right, ActionType::Hold, ActionType::Bomb};
    // in this case, placing a bomb is not safe (the opponent is able to put a bomb at 3,1 so that both will die
    // Then
    bool correctVectorReturned = selectedActions == controlVector;
    QVERIFY2(correctVectorReturned, "Bot does not consider two bots cooperating or the possiblity that two bots can place bombs");
}


void SafeActionSelectorTestClass::GivenSmallFieldWithSolidifierWhenCallingGetActionVectorLockInSafeThenCheckIfNotHold() const
{
    // Given
    FieldLayout layout = {2,1};
    GoofGameState myGameState = GoofGameState(layout); // initialize playing field
    Location myLoc = {0,0};  myGameState.addMe(myLoc, 1);
    Location solLoc1 = {0,0};  myGameState.addSolidifier(solLoc1,1);
    // When
    SafeActionSelector SA = SafeActionSelector();
    std::vector<ActionType> selectedActions = SA.GetActionVectorLockInSafe(myGameState);
    std::vector<ActionType> controlVector = { ActionType::Right};
    // in this case, there is no safety w.r.t. lock in)
    bool correctVectorReturned = selectedActions == controlVector;
    QVERIFY2(correctVectorReturned, "The safeActionsLockIn does not return right when standing on a solidfier");
}
