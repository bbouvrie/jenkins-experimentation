#ifndef GAMEOBJECTTESTCLASS_H
#define GAMEOBJECTTESTCLASS_H

#include "autotest.h"
#include "GameObject/gameobject.h"


class GameObjectTestClass: public QObject
{
    Q_OBJECT
private slots:
   // GameObjectTestClass();
   void GivenLocationToGameObjectWhenAskingForLocationGetSameLocation();
};

DECLARE_TEST(GameObjectTestClass)

#endif // GAMEOBJECTTESTCLASS_H
