#include "bombinfluence.h"

BombInfluence::BombInfluence(const Bomb &myBomb, const GoofGameState &myGS)
    : m_bombInfluence()
{
    Location bombLoc = myBomb.getLocation();
    m_bombInfluence.push_back(bombLoc);
    int bombPower = 3;
    bool bombActive = 1;
    // go up
    Location newLoc = bombLoc;
    while(bombActive && bombPower > 0)
    {
        newLoc.y += -1;
        if (newLoc.y >= 0)
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
                m_bombInfluence.push_back(newLoc);
            }
        }
        else
        {
            bombActive = 0;
        }
        // if we are stil active
        if (bombActive)
        {
            m_bombInfluence.push_back(newLoc);
            bombPower += - 1;
        }
    }

    // go down
    bombPower = 3;
    bombActive = 1;
    newLoc = bombLoc;
    while(bombActive && bombPower > 0)
    {
        newLoc.y += 1;
        if (newLoc.y < int(myGS.getLayout().nRow))
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
                m_bombInfluence.push_back(newLoc);
            }
        }
        else
        {
            bombActive = 0;
        }
        // if we are stil active
        if (bombActive)
        {
            m_bombInfluence.push_back(newLoc);
            bombPower += - 1;
        }
    }

    // go left
    bombPower = 3;
    bombActive = 1;
    newLoc = bombLoc;
    while(bombActive && bombPower > 0)
    {
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
                m_bombInfluence.push_back(newLoc);
            }
        }
        else
        {
            bombActive = 0;
        }
        // if we are stil active
        if (bombActive)
        {
            m_bombInfluence.push_back(newLoc);
            bombPower += - 1;
        }
    }

    // go rightt
    bombPower = 3;
    bombActive = 1;
    newLoc = bombLoc;
    while(bombActive && bombPower > 0)
    {
        newLoc.x += 1;
        if (newLoc.x < int(myGS.getLayout().nCol))
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
                m_bombInfluence.push_back(newLoc);
            }
        }
        else
        {
            bombActive = 0;
        }
        // if we are stil active
        if (bombActive)
        {
            m_bombInfluence.push_back(newLoc);
            bombPower += - 1;
        }
    }

}


 std::vector<Location> BombInfluence::Get() const
 {
     return m_bombInfluence;
 }
