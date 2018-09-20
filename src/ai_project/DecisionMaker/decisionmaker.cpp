#include "DecisionMaker/decisionmaker.h"
#include "DecisionMaker/offensiveactionselector.h"
#include <stdexcept>
#include <iostream>

DecisionMaker::DecisionMaker(const GoofGameState& myGameState)
    : m_gameState(myGameState)
{
}


ActionType DecisionMaker::getAction() const {
    // (falls back to safeactionselector if there is no offensive action available...
    if (m_gameState.getMe()->isAlive())  {
        OffensiveActionSelector offActionSelector = OffensiveActionSelector(m_gameState);
        ActionType selectedOffensiveAction = offActionSelector.GetAction();
        return selectedOffensiveAction;
    }
}

