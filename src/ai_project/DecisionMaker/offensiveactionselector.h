// this action selector first gets a safe action vector
// if there are such actions, it will check if an opponent can be locked in
// if so, it will choose the action accordingly
// if not, it will check if it can blow up crates
// if the end of the game is reached (t>500) it will prefer to the center of the game

#ifndef OFFENSIVEACTIONSELECTOR_H
#define OFFENSIVEACTIONSELECTOR_H

//#include "DecisionMaker/ialgorithm.h"
#include "goofgamestate.h"

class  __declspec(dllexport) OffensiveActionSelector//: public IAlgorithm
{
public:
    explicit OffensiveActionSelector(const GoofGameState &myGS);
    ActionType GetAction() const;
    ActionType GetOffensiveAction(const std::vector<ActionType> &sALI) const;
    std::vector<Location> GetLockInLocation() const;
    std::vector<double> GetValueBlowingUpOpponent(std::vector<double> &actionValue, const std::vector<Location> &LockInLocation, const std::vector<ActionType> &safeActions) const;
    std::vector<double> GetValueBlowingUpCrates(std::vector<double> &actionValue) const;
    std::vector<double> GetValueAtSolidifcationStage(std::vector<double> &actionValue) const;
    ActionType SelectActionBasedOnValue(const std::vector<double> actionValue, const std::vector<ActionType> possibleActions) const;
private:
    const GoofGameState &m_GS;
};

#endif // OFFENSIVEACTIONSELECTOR_H
