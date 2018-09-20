#ifndef DECISIONMAKER_H
#define DECISIONMAKER_H

#include "public_define.h"
#include "randomaction.h"
#include "goofgamestate.h"

class __declspec(dllexport) DecisionMaker
{
public:
    explicit DecisionMaker(const GoofGameState& myGameState);
    ActionType getAction() const;
private:
    const GoofGameState& m_gameState;
};

#endif // DECISIONMAKER_H
