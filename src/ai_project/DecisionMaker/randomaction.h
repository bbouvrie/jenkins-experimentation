#ifndef RANDOMACTION_H
#define RANDOMACTION_H

#include "public_define.h"
#include "ialgorithm.h"
#include <vector>

class __declspec(dllexport) RandomAction : public IAlgorithm
{
public:
    RandomAction();
    ActionType getAction() const;
    ActionType getAction(std::vector<ActionType> inActions) const;
};

#endif // RANDOMACTION_H
