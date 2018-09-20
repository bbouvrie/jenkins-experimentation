#ifndef __JSONOBJECTSFORMESSAGES_H__
#define __JSONOBJECTSFORMESSAGES_H__

#include "JsonBaseMsg.h"
#include "define.h"
#include <sstream>

//------------JGameRoomMap--------------
/**
 * @brief Data representation of the map of a game
 * (i.e. the tiles, players, entities and map dimensions)
 */
class JGameMap
{
public:
    /**
     * @brief JGameMap Creates a JGameMap and sets the players, entities and tiles.
     * @param players Vector of players on the Map.
     * @param entities Vector of entities on the Map.
     * @param tiles Vector of tiles of the Map.
     */
    JGameMap(const int width, const int height,
             const std::vector<JPlayerStruct> &players,
             const std::vector<EntityStruct> &entities,
             const std::vector<TileStruct> &tiles);
    /**
     * @brief JGameMap Creates a JGameMap based on a Json representation
     * @param json Json representation of JGameMap
     */
    JGameMap(const Json::Value &json);
    ~JGameMap();

    Json::Value toJson() const;

    /**
     * @brief getWidth Gets the width of the GameRoom.
     * @return
     */
    int getWidth() const { return m_width;}
    /**
     * @brief getHeight Gets the height of the GameRoom.
     * @return
     */
    int getHeight() const { return m_height;}
    /**
     * @brief getPlayers Gets the players in the GameRoom
     * @return
     */
    std::vector<JPlayerStruct> getPlayers() const {return m_players;}
    /**
     * @brief getEntities Gets the entities in the GameRoom
     * @return
     */
    std::vector<EntityStruct> getEntities() const {return m_entities;}
    /**
     * @brief getTiles Gets the tiles of the GameRoom
     * @return
     */
    std::vector<TileStruct> getTiles() const {return m_tiles;}

    /**
     * @brief getTypeName The name of this type of message
     */
    inline static std::string getTypeName() { return "GameMap"; }

private:
    std::vector<JPlayerStruct> m_players;
    std::vector<EntityStruct> m_entities;
    std::vector<TileStruct> m_tiles;
    int m_width, m_height;

    //private functions
    Json::Value serializePlayers() const;
    Json::Value serializeEntities() const;
    Json::Value serializeTiles() const;
    void constructTiles(const Json::Value &json);
    void constructEntities(const Json::Value &json);
    void constructPlayers(const Json::Value &json);
    Location constructLocation(const Json::Value &json);
};
//------------End JGameRoomMap--------------





//------------JGameState--------------

/**
 * @brief Data representation of a single cycle of a game.
 * Has knowledge of a GameMap and current cycle of a complete game.
 */
class JGameState
{
public:
    /**
     * @brief Constructs a JGameState object from a Json representation
     * @param json Json value containing a JGameState representation
     */
    JGameState(const Json::Value &json);
    /**
     * @brief JGameState Constructs a JGameState from its core building blocks
     * @param cycle the current cycle of the game (i.e. the round)
     * @param players vector containing the participating players on the GameMap
     * @param entities a vector containing entities (e.g. bombs and explosions) on the GameMap
     * @param tiles a vector of all the tiles of the GameMap
     */
    JGameState(const int width, const int height, const int cycle,
               const std::vector<JPlayerStruct> &players,
               const std::vector<EntityStruct> &entities,
               const std::vector<TileStruct> &tiles);

    /**
     * @brief JGameState Constructs a JGameState from its core building blocks
     * @param cycle the current cycle of the game (i.e. the round)
     * @param game The GameMap for the corresponding cycle
     */
    JGameState(int cycle, JGameMap game);

    ~JGameState();

    Json::Value toJson() const;
    /**
     * @brief Returns the JGameMap part of the JGameState
     * @return
     */
    JGameMap getMap() const {return m_map;}
    /**
     * @brief Returns the current cycle of the game
     * @return
     */
    int getCycle() const {return m_cycle;}

    /**
     * @brief getTypeName The name of this type of message
     */
    inline static std::string getTypeName() { return "GameState"; }

private:
    int m_cycle;
    JGameMap m_map;
};
//------------End JGameState--------------


//------------JIcons--------------

class JIcons
{
public:
    /**
     * @brief Constructs a JIcons object from a Json representation
     * @param json Json value containing a JIcons representation
     */
    JIcons(const Json::Value &json);
    /**
     * @brief JIcons Constructs a JIcons from its core building blocks
     * @param playernmbrs vector represents the player numbers
     * @param totplayernmbr is the total number of players and thus icons
     * @param icons is a vector containing the icon strings
     */
    JIcons(int nmbrofplayers, std::vector<std::string> &icons);


    ~JIcons();

    Json::Value toJson() const;
    /**
     * @brief Returns the number of players and thus icons
     * @return
     */
    int getNmbrOfPlayers() const {return m_nmbrofplayers;}

    std::vector<std::string> getIcons() const {return m_icons;}

    /**
     * @brief getTypeName The name of this type of message
     */
    inline static std::string getTypeName() { return "Icons"; }

private:
    Json::Value serializeIcons() const;
    void constructIcons(const Json::Value &json);
    int m_nmbrofplayers;
    std::vector<std::string> m_icons;
};
//------------End JIcons--------------


//------------ JLobby--------------
/**
 * @brief Representation of a gameLobby, which is not the game itself
 * but the 'lobby' on the client side at game setup time
 */
class JLobby
{
public:

    JLobby();
    /**
     * @brief Constructs a JLobby from its core building blocks
     * @param roomName name of lobby
     * @param maxNbrPlayers the maximum allowed number of players in the lobby
     * @param playerIds vector containing the names of current players in the lobby
     */
    JLobby(std::string roomName, size_t maxNrPlayers,
                  const std::vector<JPlayerLobbyStruct> &playerNames, const GameState& gameState, const iconvector &aiIcons);

    /**
     * @brief Constructs a JLobby object from a Json representation
     * @param json Json value containing a JLobby representation
     */
    JLobby(const Json::Value& json);
    ~JLobby();

    Json::Value toJson() const;

    /**
     * @brief getMaxNrPlayers Gets the max number of players allowed in the Lobby
     * @return
     */
    size_t getMaxNrPlayers() const;

    /**
     * @brief getRoomName Gets the name of the lobby
     * @return
     */
    std::string getRoomName() const;

    const std::vector<std::string> &getIcons() const;

    /**
     * @brief getPlayerNames Gets Vector of playernames that are in the room
     * @return
     */
    std::vector<JPlayerLobbyStruct> getPlayerNames() const;

    GameState getGameState() const;

    /**
     * @brief getTypeName The name of this type of message
     */
    inline static std::string getTypeName() { return "Lobby"; }
private:
    size_t m_maxNrPlayers;
    std::string m_roomName;
    std::vector<JPlayerLobbyStruct> m_playerNames;
    GameState m_gameState;
    std::vector<std::string> m_aiIcons;
};
//------------End JLobby--------------





//------------JError--------------
/**
 * @brief Representation of a data object that has user readable error messages
 * for when a request cannot be finished succesfully for whatever reason
 */
class JError
{
public:

    JError();
    /**
     * @brief JError Basic constructor of a JError object
     * @param errorType The type of the error, usually a keyword
     * @param userMessage A human readable error message that describes the error
     */
    JError(std::string errorType, std::string userMessage);

    /**
     * @brief Constructs a JError object from a Json representation
     * @param json Json value containing a JError representation
     */
    JError(const Json::Value& json);

    ~JError();
    Json::Value toJson() const;

    /**
     * @brief getErrorType Gets the error type keyword
     * @return
     */
    std::string getErrorType() const;

    /**
     * @brief getUserErrorMessage Gets the human readable error message
     * @return
     */
    std::string getUserErrorMessage() const;

    /**
     * @brief getTypeName The name of this type of message
     */
    inline static std::string getTypeName() { return "Error"; }

private:
    std::string m_errorType;
    std::string m_userMessage;
};
//------------End JError--------------


#endif // __JSONOBJECTSFORMESSAGES_H__
