#ifndef SAFEMOVEACTIONSIMULATOR_H
#define SAFEMOVEACTIONSIMULATOR_H
#include "public_define.h"
#include "goofgamestate.h"


class  __declspec(dllexport) SafeMoveActionSimulator
{
public:
    explicit SafeMoveActionSimulator(const GoofGameState& myGameState);
    std::vector<ActionType> GetSafeMoveActions();
private:
    const GoofGameState& m_gameState;
    int getMaxDuration() const;
    std::vector<ActionType> getActionsFromLoc(Location loc, GoofGameState myGSCopy) const;
    Location m_loc;
};

#endif // SAFEMOVEACTIONSIMULATOR_H
