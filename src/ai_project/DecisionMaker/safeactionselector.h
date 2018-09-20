#ifndef SAFEACTIONSELECTOR_H
#define SAFEACTIONSELECTOR_H

#include "public_define.h"
#include "DecisionMaker/ialgorithm.h"
#include "locvec.h"
#include "StrategicMaps/heatmap.h"
#include "goofgamestate.h"

class __declspec(dllexport) SafeActionSelector : public IAlgorithm
{
public:
    explicit SafeActionSelector( );
    ActionType getAction( ) const;
    ActionType getAction(const GoofGameState &myGS) const;
    std::vector<ActionType> GetActionVector(const GoofGameState & myGS) const;
    std::vector<ActionType> GetActionVector(const Location& myLoc, const GoofGameState & myGS) const;
    ActionType GetActionLockInSafe(const GoofGameState &myGS) const;
    std::vector<ActionType> GetActionVectorLockInSafe(const GoofGameState &myGS) const;
private:      
    LocVec GetNewLocVec(const LocVec &oldLocVec, const GoofGameState &myGS) const;
};

#endif // SAFEACTIONSELECTOR_H



