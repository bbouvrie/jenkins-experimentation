#ifndef GOOFGAMESTATE_H
#define GOOFGAMESTATE_H



#include "GameObject/gameobject.h"
#include "GameObject/wall.h"
//#include "me.h"
#include "GameObject/crate.h"
#include "GameObject/player.h"
#include "GameObject/bomb.h"
#include "GameObject/solidifier.h"


#include "AIBaseClass.h" // also calls: #include <publif_define.h>
#include <vector>
#include <string>

class __declspec(dllexport) GoofGameState
//class GoofGameState
{
    public:
    // GoofGameState(int nRow, int nCol, std::string myName = "");// constructor declaration default name = empty
    explicit GoofGameState(FieldLayout layout, std::string myName = "");// constructor declaration default name = empty
    explicit GoofGameState(const GameStateContainer& container, std::string myName);// constructor declaration
    GoofGameState(const GoofGameState& source); // copy constructor declaration
    // copy constructor needed?
    const Player* getMe() const;
    //int getNRow() const;
    //int getNCol() const;
    FieldLayout getLayout() const;
    // declare functions to initialize a gamestate manually
   //
    std::vector<Wall*> getWalls() const;
    std::vector<Crate*> getCrates() const;
    std::vector<Bomb*> getBombs() const;
    std::vector<Solidifier*> getSolidifier() const;
    std::vector<Player*>    getOpponents() const;
    int getTime() const;
    //  friend class GoofBotTestClass;
    //public:

    // functions to check if a location is walkable
    // move this functionality to seperate classes
    bool hasWall(const Location &Loc) const;
    bool hasCrate(const Location &Loc) const;
    bool hasBomb(const Location &Loc) const;
    bool hasSolidifier(const Location &Loc) const;
    bool locationWalkable(const Location &Loc) const;
    int getBombDuration(const Location &Loc) const;
    int getSolidifierDuration(const Location &Loc) const;
    // update gamestate
    void updateBombs();
    void updateSolidifiers();
    void updateGameState();
    //private:
    // these functions should be private but how to unit test them?
    // --> solve later
    void addMe(Location loc, bool alive);
    void addOpponent(Location loc, bool alive);
    void addWall(Location loc);
    void addCrate(Location loc);
    void addBomb(Location loc, int duration);
    void addSolidifier(Location loc, int duration);
    void LocationCheck(Location loc) const;
    private:
    //int m_nRow;
    //int m_nCol;
    FieldLayout m_layout;
    int m_timeStep;
    std::string m_myName;
    // game objects
    std::vector<Wall*> m_Walls;
    std::vector<Crate*> m_Crates;
    std::vector<Bomb*> m_Bombs;
    std::vector<Solidifier*>  m_Solidifiers;
    const Player* m_me; // const wel / niet, ook hieronder?
    std::vector<Player*> m_Opponents; // weaar ok al weer de const? (const bij de pointer)
};

#endif // GOOFGAMESTATE_H

