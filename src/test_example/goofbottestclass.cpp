#include <QtTest>

#include "goofbottestclass.h"
#include "public_define.h"
#include <GoofBot.h>


#include <string>


void GoofBotTestClass::GetNameTest()
{
    GoofBot d = GoofBot();
    QVERIFY2(d.GetName() == "GoofBot", "Not the right name");
}
