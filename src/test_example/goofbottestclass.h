#ifndef GOOFBOTTESTCLASS_H
#define GOOFBOTTESTCLASS_H


#include "autotest.h"
#include "goofgamestate.h"



class GoofBotTestClass : public QObject
{
    Q_OBJECT
private slots:
    void GetNameTest();
};

// DECLARE_TEST(GoofBotTestClass)
// skip it when uncommented?

#endif // GOOFBOTTESTCLASS_H
