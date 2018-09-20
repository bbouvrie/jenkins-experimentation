#include "offensiveactionselectortestclass.h"
#include "goofgamestate.h"
#include "public_define.h"
#include "DecisionMaker/offensiveactionselector.h"

void OffensiveActionSelectorTestClass::GivenFieldWhenCallingSafeActionSelectorThenShouldNotThrow() const
{
    // Given
    FieldLayout layout = {5,5};
    GoofGameState myGameState = GoofGameState(layout); // initialize playing field
    Location myLoc = {1,2};  myGameState.addMe(myLoc, 1);
    Location OppLoc = {1,2};  myGameState.addOpponent(OppLoc, 1);
    Location wallLoc1 = {1,1};  myGameState.addWall(wallLoc1);
    Location wallLoc2 = {3,1};  myGameState.addWall(wallLoc2);
    Location wallLoc3 = {1,3};  myGameState.addWall(wallLoc3);
    Location wallLoc4 = {3,3};  myGameState.addWall(wallLoc4);
    Location bombLoc1 = {0,2};  myGameState.addBomb(bombLoc1, 3);
    Location bombLoc2 = {1,2};  myGameState.addBomb(bombLoc2, 4);
    Location wallLoc5 = {1,0};  myGameState.addWall(wallLoc5);
    Location solLoc1 = {2,0}; myGameState.addSolidifier(solLoc1, 0);
    Location wallLoc6 = {3,0};  myGameState.addWall(wallLoc6);
    // When

    const unsigned int n_tries = 50;
    unsigned int n_counts = 0;
    for (unsigned int i = 0; i < n_tries; i++)
    {
        OffensiveActionSelector offActionSelector = OffensiveActionSelector(myGameState);
        ActionType selectedOffensiveAction = offActionSelector.GetAction();
        switch(selectedOffensiveAction)
        {
        case ActionType::Hold: n_counts += 1; break;
        case ActionType::Bomb: n_counts += 1; break;
        case ActionType::Right: n_counts += 1; break;
        default: break;
        }
    }
    bool correctActionReturned = n_counts == n_tries;


    QVERIFY2(correctActionReturned, "Not correct action returned");
}

