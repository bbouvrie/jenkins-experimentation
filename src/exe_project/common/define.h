/**
 * @file    define.h
 * @author  Hugo de Haas <Hugo.de.Haas@alten.nl>
 * @version 0.1
 *
 * @section DESCRIPTION
 *
 * Bomberman game framework
 *
 */

#ifndef __DEFINE_H__
#define __DEFINE_H__

#include <stdlib.h>
#include <assert.h>

#include "public_define.h"

enum class GameState { Waiting, Started, Finished };
enum class TileType {Solid, Walkable};
enum class EntityType {Player, Bomb, Explosion};
enum class PowerUpType { Power, Amount };

// Structs used in library and AI's
struct Direction
{
    int dx;
    int dy;

    Direction() :
        dx(),
        dy()
    {}

    Direction( int dx_, int dy_ ) :
        dx( dx_ ),
        dy( dy_ )
    {}
};

// Structs used for inter library communication
struct PlayerStruct
{
    int playerId;
     bool alive;
    Location loc;

    PlayerStruct() :
        playerId(),
        alive(),
        loc()
    {}

    PlayerStruct( int playerId_, bool alive_, const Location& loc_ ) :
        playerId( playerId_ ),
        alive( alive_ ),
        loc( loc_ )
    {}
};

// Minimum and maximum game limits that are hardcoded
const int g_minPlayers = 2;
const int g_maxPlayers = 4;
const int g_minFieldWidth = 5;
const int g_maxFieldWidth = 21;
const int g_minFieldHeight = 5;
const int g_maxFieldHeight = 21;
// End

inline bool operator==(const Location& lhs, const Location& rhs) {
    return (lhs.x==rhs.x && lhs.y==rhs.y);
}

typedef std::vector<const std::string *> iconvector;
#endif // __DEFINE_H__
