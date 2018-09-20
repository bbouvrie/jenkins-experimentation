// It would only make sense to make this an interface if getAction() can be directly used by all children
// Not the case because randomAction does not need an input while offensiveactionselector and safeactionselector require goofgamestate
// alternatively it would be useful if they could inherit some functions
#ifndef IALGORITHM_H
#define IALGORITHM_H

#include "public_define.h"

class IAlgorithm
{
public:
    IAlgorithm();
    virtual ~IAlgorithm();
    virtual ActionType getAction() const = 0; // pure virtual function
};

#endif // IALGORITHM_H
