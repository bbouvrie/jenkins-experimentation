#ifndef JSONCLIENTMSG_H
#define JSONCLIENTMSG_H

#include <stdlib.h>

#include "JsonObjectsForMsg.h"
#include "JsonBaseMsg.h"

//------------JRequestClientActionMessage---------------
/**
 * @brief Data representation of a request
 * to perform a game action.
 */
class JRequestClientActionMessage : public JsonRequestMessage
{
public:
    /**
     * @brief Creates a JRequestClientActionMessage request
     */
    JRequestClientActionMessage(const JGameState &gameState);

    /**
     * @brief Creates a JRequestClientActionMessage from its Json representation
     * @param jsonObj Json representation of a JRequestClientActionMessage object
     */
    JRequestClientActionMessage(const Json::Value &jsonObj);

    ~JRequestClientActionMessage();

    /**
     * @brief getGameState gets the GameState that the AI needs to determine a move
     * @return
     */
    JGameState getGameState() const;

    /**
     * @brief getTypeName The name of this type of message
     */
    inline static std::string getTypeName() { return "ClientAction"; }

protected:
    void concatenateFields(Json::Value &result) const;

private:
    JGameState m_gameState;
};
//------------End JRequestClientActionMessage-----------

//------------JRequestClientActionReply--------------
/**
 * @brief Data representation of a reply to the JRequestClientActionReply
 */
class JRequestClientActionReply : public JsonReplyMessage
{
public:
    /**
     * @brief Constructs a JRequestClientActionReply object from its core building blocs
     * @param action the action to execute in string form
     */
    JRequestClientActionReply(std::string action);

    /**
     * @brief JRequestClientActionReply Contruct message from a json representation
     * @param json The json value containing a JRequestClientActionReply representation
     */
    JRequestClientActionReply(const Json::Value &jsonObj);

    ~JRequestClientActionReply();

    /**
     * @brief getAction gets the action the client wants to perform in string form
     */
    std::string getClientAction() const;

    /**
     * @brief getTypeName The name of this type of message
     */
    inline static std::string getTypeName() { return "ClientAction"; }

protected:
    void concatenateFields(Json::Value &result) const;

private:
    std::string m_action;
};
//------------End JRequestClientActionReply--------------


//---------------JRequestClientIconMessage--------------
class JRequestClientIconMessage : public JsonRequestMessage
{
public:
    /**
     * @brief JRequestClientIconMessage
     */
    JRequestClientIconMessage();

    /**
     * @brief JRequestClientIconMessage
     * @param jsonObj
     */
    JRequestClientIconMessage(const Json::Value& jsonObj);

    ~JRequestClientIconMessage();

    /**
     * @brief getTypeName The name of this type of message
     */
    inline static std::string getTypeName() { return "ClientIcon"; }

protected:
    void concatenateFields(Json::Value &result) const;

private:
    // No data
};
//------------End JRequestClientIconMessage--------------

//-------------JRequestClientIconReply-------------------
class JRequestClientIconReply : public JsonReplyMessage
{
public:
    /**
     * @brief JRequestClientIconReply
     * @param icon
     */
    JRequestClientIconReply(const std::string& icon);

    /**
     * @brief JRequestClientIconReply
     * @param jsonObj
     */
    JRequestClientIconReply(const Json::Value& jsonObj);

    ~JRequestClientIconReply();

    /**
     * @brief getClientIcon gets the icon of an AI
     */
    const std::string& getClientIcon() const;

    /**
     * @brief getTypeName The name of this type of message
     */
    inline static std::string getTypeName() { return "ClientIcon"; }

protected:
    void concatenateFields(Json::Value &result) const;

private:
    const std::string m_icon;
};
//------------End JRequestClientIconReply----------------


//---------------JRequestClientNameMessage--------------
class JRequestClientNameMessage : public JsonRequestMessage
{
public:
    /**
     * @brief JRequestClientNameMessage
     */
    JRequestClientNameMessage();

    /**
     * @brief JRequestClientNameMessage
     * @param jsonObj
     */
    JRequestClientNameMessage(const Json::Value& jsonObj);

    ~JRequestClientNameMessage();

    /**
     * @brief getTypeName The name of this type of message
     */
    inline static std::string getTypeName() { return "ClientName"; }

protected:
    void concatenateFields(Json::Value &result) const;

private:
    // No data
};
//------------End JRequestClientNameMessage--------------

//-------------JRequestClientNameReply-------------------
class JRequestClientNameReply : public JsonReplyMessage
{
public:
    /**
     * @brief JRequestClientNameReply
     * @param name
     */
    JRequestClientNameReply(const std::string& name);

    /**
     * @brief JRequestClientNameReply
     * @param jsonObj
     */
    JRequestClientNameReply(const Json::Value& jsonObj);

    ~JRequestClientNameReply();

    /**
     * @brief getClientName gets the name of an AI
     */
    const std::string& getClientName() const;

    /**
     * @brief getTypeName The name of this type of message
     */
    inline static std::string getTypeName() { return "ClientName"; }

protected:
    void concatenateFields(Json::Value &result) const;

private:
    const std::string m_name;
};
//------------End JRequestClientNameReply----------------


//------------JSetPlayerNameMessage--------------
class JSetPlayerNameMessage : public JsonRequestMessage
{
public:
    /**
     * @brief Creates a JSetPlayerNameMessage
     * @param playerName The name of the player
     */
    JSetPlayerNameMessage(std::string playerName);

    /**
     * @brief Creates a JSetPlayerNameMessage from its Json representation
     * @param jsonObj Json representation of a JSetPlayerNameMessage object
     */
    JSetPlayerNameMessage(const Json::Value &jsonObj);

    ~JSetPlayerNameMessage();

    std::string getPlayerName() const;

    /**
     * @brief getTypeName The name of this type of message
     */
    inline static std::string getTypeName() { return "SetPlayerName"; }

protected:
    void concatenateFields(Json::Value &result) const;

private:
    std::string m_playerName;
};
//------------End JSetPlayerNameMessage--------------

//-------------JSetPlayerNameReply-------------------
class JSetPlayerNameReply : public JsonReplyMessage
{
public:
    /**
     * @brief JSetPlayerNameReply
     * @param name
     */
    JSetPlayerNameReply();

    /**
     * @brief JSetPlayerNameReply
     * @param jsonObj
     */
    JSetPlayerNameReply(const Json::Value& jsonObj);

    ~JSetPlayerNameReply();

    /**
     * @brief getTypeName The name of this type of message
     */
    inline static std::string getTypeName() { return "SetPlayerName"; }

protected:
    void concatenateFields(Json::Value &result) const;

private:
    const std::string m_name;
};
//------------End JSetPlayerNameReply----------------

#endif // JSONCLIENTMSG_H
