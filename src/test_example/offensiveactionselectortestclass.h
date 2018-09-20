#ifndef OFFENSIVEACTIONSELECTORTESTCLASS_H
#define OFFENSIVEACTIONSELECTORTESTCLASS_H

#include "autotest.h"

class OffensiveActionSelectorTestClass: public QObject
{
    Q_OBJECT
private slots:
    void GivenFieldWhenCallingSafeActionSelectorThenShouldNotThrow() const;
};

DECLARE_TEST(OffensiveActionSelectorTestClass)

#endif // OFFENSIVEACTIONSELECTORTESTCLASS_H



