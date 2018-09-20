 #include "JsonObjectsForMsg.h"

#include "Logger.h"
#include "Util.h"

//------------JGameMap--------------
JGameMap::JGameMap(const int width, const int height,
                   const std::vector<JPlayerStruct> &players,
                   const std::vector<EntityStruct> &entities,
                   const std::vector<TileStruct> &tiles)
            : m_players(players),
              m_entities(entities),
              m_tiles(tiles),
              m_width(width),
              m_height(height)
{}

JGameMap::JGameMap(const Json::Value &json)
    : m_width(json["width"].asInt()),
      m_height(json["height"].asInt())
{
    constructTiles(json["map"]);
    constructPlayers(json["players"]);
    constructEntities(json["entities"]);
}

JGameMap::~JGameMap()
{}

Json::Value JGameMap::toJson() const
{    
    Json::Value result;
    result["width"] = m_width;
    result["height"] = m_height;
    result["players"] = serializePlayers();            
    result["entities"] = serializeEntities();         
    result["map"] = serializeTiles();    
    return result;
}

Json::Value JGameMap::serializePlayers() const
{
    Json::Value players;
    for(auto it = m_players.begin();it != m_players.end(); it++ )
    {
        Json::Value player;
        player["playerName"] = (*it).playerName;
        player["x"] = (*it).loc.x;
        player["y"] = (*it).loc.y;
        player["alive"] = (*it).alive;
        player["playerAttribute"] = it->playerAttribute;

        players.append(player);
    }

    return players;
}

Json::Value JGameMap::serializeEntities() const
{
    Json::Value entities;
    for (auto it = m_entities.begin(); it != m_entities.end(); it++)
    {
        Json::Value entitie;
        entitie["type"] = (*it).type;
        entitie["x"] = (*it).loc.x;
        entitie["y"] = (*it).loc.y;

        // if entity is a bomb, insert Duration as well
        if (it->type == "Bomb" || it->type == "PowerUp" || it->type == "Solidifier")
        {
            entitie["duration"] = it->duration;
        }

        // TODO Add power up   verify type because of two

        entities.append(entitie);
    }
    return entities;
}

Json::Value JGameMap::serializeTiles() const
{
    Json::Value map;
    for (auto it = m_tiles.begin(); it != m_tiles.end(); it++)
    {
        Json::Value tile;
        tile["x"] = (*it).loc.x;
        tile["y"] = (*it).loc.y;
        tile["crate"] = (*it).crate;
        tile["type"] = (*it).type;
        map.append(tile);
    }

    return map;
}

void JGameMap::constructTiles(const Json::Value &json)
{
    int tileCount = json.size();
    for(int i=0;i<tileCount; ++i)
    {
        TileStruct tile;
        tile.crate = json[i]["crate"].asBool();
        tile.loc = constructLocation(json[i]);
        tile.type = json[i]["type"].asString();
        m_tiles.push_back(tile);
    }
}

void JGameMap::constructEntities(const Json::Value &json)
{
    int entitiesCount = json.size();
    for(int i=0;i<entitiesCount;++i)
    {
        Json::Value durationVal = json[i]["duration"];
        int duration = 0;
        if(!durationVal.empty())
            duration = durationVal.asInt();

        EntityStruct entity;
        entity.loc = constructLocation(json[i]);
        entity.type = json[i]["type"].asString();
        entity.duration = duration;
        m_entities.push_back(entity);
    }
}

void JGameMap::constructPlayers(const Json::Value &json)
{
    int playersCount = json.size();
    for(int i=0;i<playersCount;++i)
    {
        Location loc = constructLocation(json[i]);
        bool alive = json[i]["alive"].asBool();
        std::string playerName = json[i]["playerName"].asString();
        std::string playerAttribute = json[i]["playerAttribute"].asString();
        JPlayerStruct player{playerName, playerAttribute, alive, loc};
        m_players.push_back(player);
    }
}

Location JGameMap::constructLocation(const Json::Value &json)
{
    Location loc;
    loc.x = json["x"].asInt();
    loc.y = json["y"].asInt();
    return loc;
}

//------------End JGameMap--------------





//------------JGameState--------------
JGameState::JGameState(const Json::Value &json) :
    m_cycle(json["Cycle"].asInt()),m_map(JGameMap(json[JGameMap::getTypeName()]))
{}

JGameState::JGameState(const int width, const int height, const int cycle,
                       const std::vector<JPlayerStruct> &players,
                       const std::vector<EntityStruct> &entities,
                       const std::vector<TileStruct> &tiles) :
    JGameState(cycle, JGameMap(width, height, players, entities, tiles))
{}

JGameState::JGameState(int cycle,JGameMap game) :
    m_cycle(cycle), m_map(game)
{}

JGameState::~JGameState(){}

Json::Value JGameState::toJson() const
{    
    Json::Value result;
    result["Cycle"] = m_cycle;
    result[JGameMap::getTypeName()] = m_map.toJson();
    return result;
}


//------------End JGameState--------------


//------------JIcons--------------
JIcons::JIcons(const Json::Value &json) :
    m_nmbrofplayers(json["Nmbr of PlayerIcons"].asInt())
{
    constructIcons(json["Icons"]);
}

JIcons::JIcons(int nmbrofplayers, std::vector<std::string> &icons) :
    m_nmbrofplayers(nmbrofplayers),
    m_icons(icons)
{
}

JIcons::~JIcons(){}

Json::Value JIcons::toJson() const
{
    Json::Value result;

    result["Icons"] = serializeIcons();
    result["Nmbr of PlayerIcons"] = m_nmbrofplayers;
    return result;
}

void JIcons::constructIcons(const Json::Value &json)
{
    int IconCount = json.size();
    for(int i=0;i<IconCount;++i)
    {
        std::string icon = json[i]["icon"].asString();
        m_icons.push_back(icon);
    }
}

Json::Value JIcons::serializeIcons() const
{
    Json::Value icons;
    for(int i = 0; i < (int) m_icons.size(); ++i )
    {
        Json::Value icon;
        std::string in = "icon";
//        std::string istring = std::to_string(i);
//        in.append(" ");
//        in.append(istring);
        icon[in] = m_icons[i];

        icons.append(icon);
    }

    return icons;
}

//------------End JIcons--------------



//------------ JLobby--------------
JLobby::JLobby() :
    m_maxNrPlayers(0), m_roomName(""), m_playerNames(), m_gameState(GameState::Waiting), m_aiIcons()
{

}

JLobby::JLobby(std::string roomName, size_t maxNrPlayers, const std::vector<JPlayerLobbyStruct> &playerNames, const GameState &gameState, const iconvector &aiIcons)
 :  m_maxNrPlayers(maxNrPlayers),m_roomName(roomName), m_playerNames(playerNames), m_gameState(gameState)
{
    for ( unsigned int i = 0; i < aiIcons.size(); ++i )
    {
        m_aiIcons.push_back(*aiIcons[i]);
    }
}

JLobby::JLobby(const Json::Value &json) :
    m_maxNrPlayers(json["Spaces"].asInt()), m_roomName(json["RoomID"].asString()), m_aiIcons(JsonBaseMsg::arrayFromJson(json["Icons"]))
{
   std::vector<JPlayerLobbyStruct> playerNames;
   Json::Value Players = json["Players"];
   for (unsigned int i = 0; i < Players.size();i++)
   {
       JPlayerLobbyStruct player;
       player.playerName = Players[i]["PlayerName"].asString();
       player.playerAttribute = Players[i]["PlayerAttribute"].asString();

       playerNames.push_back(player);
   }

    m_playerNames = playerNames;
    m_gameState = Util::StrToGameState(json["GameState"].asString());
}

JLobby::~JLobby(){}

size_t JLobby::getMaxNrPlayers() const
{
    return m_maxNrPlayers;
}

std::string JLobby::getRoomName() const
{
    return m_roomName;
}

const std::vector<std::string> &JLobby::getIcons() const
{
    return m_aiIcons;
}

std::vector<JPlayerLobbyStruct> JLobby::getPlayerNames() const
{
    return m_playerNames;
}

GameState JLobby::getGameState() const
{
    return m_gameState;
}

Json::Value JLobby::toJson() const
{
    Json::Value result;
    result["RoomID"] = m_roomName;
    result["Spaces"] = m_maxNrPlayers;

    Json::Value Players;
    for(auto it = m_playerNames.begin(); it != m_playerNames.end(); it++)
    {
        Json::Value Player;
        Player["PlayerName"] = (*it).playerName;
        Player["PlayerAttribute"] = (*it).playerAttribute;
        Players.append(Player);
    }

    result["Players"] = Players;
    result["GameState"] = Util::GameStateToStr(m_gameState);
    result["Icons"] = JsonBaseMsg::arrayToJson(m_aiIcons);
    return result;
}
//------------End JLobby--------------





//------------JError--------------
JError::JError() :
    m_errorType(""), m_userMessage("")
{}

JError::JError(std::string errorType, std::string userMessage) :
    m_errorType(errorType), m_userMessage(userMessage)
{
#ifdef LOGGER
    LOGGER->Log(Logger::Info, "[JError] " + m_errorType + " " + m_userMessage);
#endif
}

JError::JError(const Json::Value &json) :
    m_errorType(json["ErrorType"].asString()), m_userMessage(json["UserMessage"].asString())
{
#ifdef LOGGER
    LOGGER->Log(Logger::Info, "[JError] " + m_errorType + " " + m_userMessage);
#endif
}

JError::~JError() {}

std::string JError::getErrorType() const
{
    return m_errorType;
}

std::string JError::getUserErrorMessage() const
{
    return m_userMessage;
}

Json::Value JError::toJson() const
{
    Json::Value result;
    result["ErrorType"] = m_errorType;
    result["UserMessage"] = m_userMessage;
    return result;
}

//------------End JError--------------
