#include "DummyTest.h"
#include <QtTest>

#include <Dummy.h>

void DummyTest::GetNameTest()
{
    Dummy d = Dummy();

    QVERIFY2(d.GetName() == "Dummy", "Not the right name");
}

void DummyTest::GetActionTest()
{
    Dummy d = Dummy();

    GameStateContainer container;

    container.height = 1;
    container.width = 1;
    container.cycle = 0;

    // set up the grid
    container.tiles.push_back(TileStruct(Location(0,0), true, "Walkable"));

    // set up the players
    container.players.push_back(JPlayerStruct("Dummy", "Human", true, Location(0,0)));

    QVERIFY2(d.GetAction(container) == ActionType::Hold, "Not a dummy action anymore.");
}
