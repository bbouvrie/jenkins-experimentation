#include "goofgamestate.h"
#include "locvec.h"
#include "gooffunctions.h"
//#include "bombinfluence.h"

GoofGameState::GoofGameState(FieldLayout layout, std::string myName)// constructor definition
    : m_layout( layout ),
      m_timeStep(),
      m_myName(myName),
      m_Walls(),
      m_Crates(),
      m_Bombs(),
      m_Solidifiers(),
      m_me(),
      m_Opponents()
{

}

GoofGameState::GoofGameState(const GameStateContainer &container, std::string myName) // constructor when using info of container
    : m_layout( FieldLayout(unsigned(container.width), unsigned(container.height) ) ),
      m_timeStep( container.cycle),
      m_myName(myName),
      m_Walls(),
      m_Crates(),
      m_Bombs(),
      m_me(),
      m_Opponents()
{    

    // get locations of walls, ..
    for (auto e :container.tiles)
    {
        if (e.type == "Solid")
        {
            GoofGameState::addWall(e.loc);
        }

        if(e.crate)
        {
            GoofGameState::addCrate(e.loc);
        }
    }

    // get bombs and solidifiers
    for (auto e : container.entities)
    {
        if (e.type == "Bomb")
        {
            GoofGameState::addBomb(e.loc, e.duration);
        }
        if (e.type == "Solidifier")
        {
            GoofGameState::addSolidifier(e.loc, e.duration);
        }
    }

    // get my location and alive status, and create me as an object (in fact a pointer to ...)
    for (auto e : container.players)
    {
        if (e.playerName == m_myName) // you found yourself! store yourself
        {
            GoofGameState::addMe(e.loc, e.alive);
        }

        else // opponent
        {
            GoofGameState::addOpponent(e.loc, e.alive);
        }
    }


}


GoofGameState::GoofGameState(const GoofGameState& source) // define the copy constructor
    : GoofGameState(source.getLayout(), source.m_myName)
{
    m_timeStep = source.m_timeStep;
    // When copying you want to copy everything (not copy the pointer)
    for (auto e : source.m_Walls)
    {
        addWall(e->getLocation());
    }

    for (auto e : source.m_Crates)
    {
        addCrate(e->getLocation());
    }
    for (auto e : source.m_Bombs)
    {
        addBomb(e->getLocation(), e->getDuration());
    }
    for (auto e : source.m_Solidifiers)
    {
        addSolidifier(e->getLocation(), e->getDuration());
    }
    //
    if (source.m_me)
    {
        addMe(source.m_me->getLocation(), source.m_me->isAlive());
    }
    //
    for (auto e : source.m_Opponents)
    {
        addOpponent(e->getLocation(), e->isAlive());
    }

}


FieldLayout GoofGameState::getLayout() const
{
    return m_layout;
}

int GoofGameState::getTime() const
{
    return m_timeStep;
}

bool GoofGameState::hasWall(const Location &Loc) const
{
    bool hasWall = 0;
    for (auto e : m_Walls)
    {
        if (e->getLocation() == Loc)
        {
            hasWall = 1;
        }
    }
    return hasWall;
}

// DRY? use more standardized function? is that possible?
bool GoofGameState::hasCrate(const Location &Loc) const
{
    bool hasCrate = 0;
    for (auto e : m_Crates)
    {
        if (e->getLocation() == Loc)
        {
            hasCrate = 1;
        }
    }
    return hasCrate;
}

// DRY? use more standardized function? is that possible?
bool GoofGameState::hasBomb(const Location &Loc) const
{
    bool hasBomb = 0;
    for (auto e : m_Bombs)
    {
        if (e->getLocation() == Loc)
        {
            hasBomb = 1;
        }
    }
    return hasBomb;
}

bool GoofGameState::hasSolidifier(const Location &Loc) const
{
    bool hasSolidifier = 0;
    for (auto e : m_Solidifiers)
    {
        //if (e->getLocation().x == Loc.x && e->getLocation().y == Loc.y)
        if (e->getLocation() == Loc)
        {
            hasSolidifier = 1;
        }
    }
    return hasSolidifier;
}


bool GoofGameState::locationWalkable(const Location &Loc) const
{
    bool locWalkable = 0;
    bool locHasWall = GoofGameState::hasWall(Loc);
    bool locHasCrate = GoofGameState::hasCrate(Loc);
    bool locHasBomb = GoofGameState::hasBomb(Loc);
    bool locHasSolidifier = GoofGameState::hasSolidifier(Loc);
    if (!locHasWall && !locHasCrate && !locHasBomb && !locHasSolidifier)
    {
        locWalkable = 1;
    }
    return locWalkable;
}

const Player* GoofGameState::getMe() const
{
    return m_me;
}



// Declar functions to add objects manually
void GoofGameState::addMe(Location loc, bool alive)
{
    LocationCheck(loc);
    m_me = new Player(loc, alive);
}

void GoofGameState::addWall(Location loc)
{
    LocationCheck(loc);
    Wall* tempWall = new Wall(loc);
    m_Walls.push_back(tempWall);
}

void GoofGameState::addCrate(Location loc)
{
    LocationCheck(loc);
    Crate* tempCrate = new Crate(loc);
    m_Crates.push_back(tempCrate);
}

void GoofGameState::addBomb(Location loc, int duration)
{
    LocationCheck(loc);
    Bomb* tempBomb = new Bomb(loc, duration);
    m_Bombs.push_back(tempBomb);
}

void GoofGameState::addSolidifier(Location loc, int duration)
{
    LocationCheck(loc);
    Solidifier* tempSolidifier = new Solidifier(loc, duration);
    m_Solidifiers.push_back(tempSolidifier);
}


void GoofGameState::addOpponent(Location loc, bool alive)
{
    LocationCheck(loc);
    Player* opponent = new Player(loc, alive);
    m_Opponents.push_back(opponent);
}

std::vector<Wall*> GoofGameState::getWalls() const
{
    return m_Walls;
}

std::vector<Crate*> GoofGameState::getCrates() const
{
    return m_Crates;
}

std::vector<Bomb*> GoofGameState::getBombs() const
{
    return m_Bombs;
}

std::vector<Solidifier*> GoofGameState::getSolidifier() const
{
    return m_Solidifiers;
}

std::vector<Player*> GoofGameState::getOpponents() const
{
    return m_Opponents;
}



int GoofGameState::getBombDuration(const Location &Loc) const
{
    int bombDuration = 100;
    for (auto e : m_Bombs)
    {
        if (e->getLocation() == Loc)
        {
            bombDuration = e->getDuration();
        }
    }
    return bombDuration;
}

int GoofGameState::getSolidifierDuration(const Location &Loc) const
{
    int solDuration = 100;
    for (auto e : m_Solidifiers)
    {
        if (e->getLocation() == Loc)
        {
            solDuration = e->getDuration();
        }
    }
    return solDuration;
}


void GoofGameState::updateBombs()
{
    std::vector<Bomb*> updatedBombs={};
    LocVec bombsImpact = LocVec();
    for (auto e : m_Bombs)
    {
        e->updateDuration();
        if (e->getDuration() > 0)
        {
            updatedBombs.push_back(e);
        }
        else if(e->getDuration()==0)
        {
            updatedBombs.push_back(e);
            //BombInfluence bI = BombInfluence(*e, *this);
            //std::vector<Location> bILocations = bI.Get();
            std::vector<Location> bILocations = BombInfluence(*e, *this);

            bombsImpact.Add(bILocations);
        }
    }
    // reset m_Bombs
    m_Bombs = updatedBombs;
    // update crates...
    std::vector<Crate*> updatedCrates = {};
    std::vector<Location> bombImpactLocations = bombsImpact.Get();
    for (auto e : m_Crates)
    {

        bool AddThisCrate = 1;
        for (auto e_loc : bombImpactLocations)
        {
            if(e->getLocation() == e_loc)
            {
                AddThisCrate = 0;
            }
        }
        if(AddThisCrate)
        {
            updatedCrates.push_back(e);
        }
    }
    m_Crates = updatedCrates;
}

void GoofGameState::updateSolidifiers()
{
    std::vector<Solidifier*> updatedSolidifiers={};
    for (auto e : m_Solidifiers)
    {
        e->updateDuration();
        if (e->getDuration() > 0)
        {
            updatedSolidifiers.push_back(e);
        }
        else
        {
            addWall(e->getLocation());
        }
    }
    // reset m_Solidifiers
    m_Solidifiers = updatedSolidifiers;
}

void GoofGameState::updateGameState()
{
    updateBombs();
    updateSolidifiers();
}

// this function is also used in heatmap.h
void GoofGameState::LocationCheck(Location loc) const
{
   if (loc.x < 0)
   {
       throw std::invalid_argument("HeatMap::LocationCheck: Given x value of location smaller than 0");
   }
   if (loc.x > int(m_layout.nCol) - 1)
   {
       throw std::invalid_argument("HeatMap::LocationCheck:Given x value of location larger than number of columns");
   }
   if (loc.y < 0)
   {
       throw std::invalid_argument("HeatMap::LocationCheck:Given y value of location smaller than 0");
   }
   if (loc.y > int(m_layout.nRow) - 1)
   {
       throw std::invalid_argument("HeatMap::LocationCheck:Given y value of location larger than number of rows");
   }
}

