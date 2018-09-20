#include "gooffunctions.h"


std::vector<ActionType> ActionVectorUnion(const std::vector<ActionType> vecA, const std::vector<ActionType> vecB){
    std::vector<ActionType> vecOut = {};
    for (auto eA : vecA) {
        bool foundElement = 0;
        for (auto eB : vecB) {
            if (eA == eB) {
                foundElement = 1;
            }
        }
        if (foundElement) {
            vecOut.push_back(eA);
        }
    }
    return vecOut;
}


Location UpdateLocationBasedOnGameState(const ActionType &action, const Location &oldLoc, const GoofGameState &myGS){
    Location outLoc = {-1,-1};
    Location newLoc = oldLoc;
    bool locWalkable = 1;

    switch(action) {
        case ActionType::Up    : newLoc.y += -1;  break;
        case ActionType::Down  : newLoc.y += 1;   break;
        case ActionType::Left  : newLoc.x += -1;  break;
        case ActionType::Right : newLoc.x += 1;   break;
        case ActionType::Hold  : break;
        case ActionType::Bomb  : break;
    }

    if (newLoc.y >= 0 && newLoc.y < int(myGS.getLayout().nRow) &&
            newLoc.x >= 0 && newLoc.x < int(myGS.getLayout().nCol) )
        // only look at valid locations
    {
        // you cannot step on a wall or crate
        if ( myGS.hasWall(newLoc) || myGS.hasCrate(newLoc) ) {
            locWalkable = 0;
        }

        if( myGS.hasBomb(newLoc)) {
            // you cannot step ONTO a bomb (but if you are on it then that is ok)
            if( !(newLoc == oldLoc) ) {
                if (myGS.getBombDuration(newLoc)< 4) {
                    locWalkable = 0;
                }
            }

        }
        // if walkable return newLoc as outLoc, else return (-1,-1)
        if (locWalkable) {
            outLoc = newLoc;
        }
    }
    return outLoc;
}

std::vector<Location> BombInfluence(const Bomb &myBomb, const GoofGameState &myGS){
    std::vector<Location> bombInfluence = {};
    Location bombLoc = myBomb.getLocation();
    bombInfluence.push_back(bombLoc);
    int bombPower = 3;
    bool bombActive = 1;
    // go up
    Location newLoc = bombLoc;
    while(bombActive && bombPower > 0) {
        newLoc.y += -1;
        if (newLoc.y >= 0) {
            // stop if found wall
            if (myGS.hasWall(newLoc)) {
                bombActive = 0;
            }
            // stop if found crate
            if (myGS.hasCrate(newLoc)) {
                bombActive = 0;
                bombInfluence.push_back(newLoc);
            }
        }
        else {
            bombActive = 0;
        }
        // if we are stil active
        if (bombActive){
            bombInfluence.push_back(newLoc);
            bombPower += - 1;
        }
    }

    // go down
    bombPower = 3;
    bombActive = 1;
    newLoc = bombLoc;
    while(bombActive && bombPower > 0) {
        newLoc.y += 1;
        if (newLoc.y < int(myGS.getLayout().nRow)) {
            // stop if found wall
            if (myGS.hasWall(newLoc)) {
                bombActive = 0;
            }
            // stop if found crate
            if (myGS.hasCrate(newLoc)) {
                bombActive = 0;
                bombInfluence.push_back(newLoc);
            }
        }
        else  {
            bombActive = 0;
        }
        // if we are stil active
        if (bombActive) {
            bombInfluence.push_back(newLoc);
            bombPower += - 1;
        }
    }

    // go left
    bombPower = 3;
    bombActive = 1;
    newLoc = bombLoc;
    while(bombActive && bombPower > 0) {
        newLoc.x += -1;
        if (newLoc.x >= 0)
        {
            // stop if found wall
            if (myGS.hasWall(newLoc))
            {
                bombActive = 0;
            }
            // stop if found crate
            if (myGS.hasCrate(newLoc))
            {
                bombActive = 0;
                bombInfluence.push_back(newLoc);
            }
        }
        else  {
            bombActive = 0;
        }
        // if we are stil active
        if (bombActive)  {
            bombInfluence.push_back(newLoc);
            bombPower += - 1;
        }
    }

    // go rightt
    bombPower = 3;
    bombActive = 1;
    newLoc = bombLoc;
    while(bombActive && bombPower > 0) {
        newLoc.x += 1;
        if (newLoc.x < int(myGS.getLayout().nCol)){
            // stop if found wall
            if (myGS.hasWall(newLoc)){
                bombActive = 0;
            }
            // stop if found crate
            if (myGS.hasCrate(newLoc)){
                bombActive = 0;
                bombInfluence.push_back(newLoc);
            }
        }
        else{
            bombActive = 0;
        }
        // if we are stil active
        if (bombActive){
            bombInfluence.push_back(newLoc);
            bombPower += - 1;
        }
    }
return bombInfluence;
}
