#include "JsonClientMsg.h"

//------------JRequestClientActionMessage--------------
JRequestClientActionMessage::JRequestClientActionMessage(const JGameState& gameState)
    : JsonRequestMessage(JRequestClientActionMessage::getTypeName())
    , m_gameState(gameState)
{}

JRequestClientActionMessage::JRequestClientActionMessage(const Json::Value& jsonObj)
    : JsonRequestMessage(jsonObj)
    , m_gameState(JGameState(jsonObj[JGameState::getTypeName()]))
{}

JRequestClientActionMessage::~JRequestClientActionMessage()
{}

JGameState JRequestClientActionMessage::getGameState() const
{
    return m_gameState;
}

void JRequestClientActionMessage::concatenateFields(Json::Value& result) const
{
    result[JGameState::getTypeName()] = m_gameState.toJson();
}
//------------End JRequestClientActionMessage--------------

//------------JRequestClientActionReply--------------
JRequestClientActionReply::JRequestClientActionReply(std::string action)
    : JsonReplyMessage(JRequestClientActionReply::getTypeName())
    , m_action(action)
{}

JRequestClientActionReply::JRequestClientActionReply(const Json::Value& jsonObj)
    : JsonReplyMessage(jsonObj)
    , m_action(jsonObj["action"].asString())
{}

JRequestClientActionReply::~JRequestClientActionReply()
{}

std::string JRequestClientActionReply::getClientAction() const
{
    return m_action;
}

void JRequestClientActionReply::concatenateFields(Json::Value& result) const
{
    result["action"] = m_action;
}
//------------End JRequestClientActionReply--------------


//-----------------JRequestClientIconMessage---------------
JRequestClientIconMessage::JRequestClientIconMessage()
    : JsonRequestMessage(JRequestClientIconMessage::getTypeName())
{}

JRequestClientIconMessage::JRequestClientIconMessage(const Json::Value& jsonObj)
    : JsonRequestMessage(jsonObj)
{}

JRequestClientIconMessage::~JRequestClientIconMessage() {}

void JRequestClientIconMessage::concatenateFields(Json::Value& /*result*/) const
{}
//-----------End JRequestClientIconMessage-----------------

//----------------JRequestClientIconReply----------------
JRequestClientIconReply::JRequestClientIconReply(const std::string& icon)
    : JsonReplyMessage(JRequestClientIconReply::getTypeName())
    , m_icon(icon)
{}

JRequestClientIconReply::JRequestClientIconReply(const Json::Value& jsonObj)
    : JsonReplyMessage(jsonObj)
    , m_icon(jsonObj["icon"].asString())
{
}

JRequestClientIconReply::~JRequestClientIconReply()
{}

const std::string& JRequestClientIconReply::getClientIcon() const
{
    return m_icon;
}

void JRequestClientIconReply::concatenateFields(Json::Value& result) const
{
    result["icon"] = m_icon;
}
//------------End JRequestClientIconReply----------------


//-----------------JRequestClientNameMessage---------------
JRequestClientNameMessage::JRequestClientNameMessage()
    : JsonRequestMessage(JRequestClientNameMessage::getTypeName())
{}

JRequestClientNameMessage::JRequestClientNameMessage(const Json::Value& jsonObj)
    : JsonRequestMessage(jsonObj)
{}

JRequestClientNameMessage::~JRequestClientNameMessage() {}

void JRequestClientNameMessage::concatenateFields(Json::Value& /*result*/) const
{}
//-----------End JRequestClientNameMessage-----------------

//----------------JRequestClientNameReply----------------
JRequestClientNameReply::JRequestClientNameReply(const std::string& name)
    : JsonReplyMessage(JRequestClientNameReply::getTypeName())
    , m_name(name)
{}

JRequestClientNameReply::JRequestClientNameReply(const Json::Value& jsonObj)
    : JsonReplyMessage(jsonObj)
    , m_name(jsonObj["name"].asString())
{
}

JRequestClientNameReply::~JRequestClientNameReply()
{}

const std::string& JRequestClientNameReply::getClientName() const
{
    return m_name;
}

void JRequestClientNameReply::concatenateFields(Json::Value& result) const
{
    result["name"] = m_name;
}
//------------End JRequestClientNameReply----------------


//------------JSetPlayerNameMessage--------------
JSetPlayerNameMessage::JSetPlayerNameMessage(std::string playerName)
    : JsonRequestMessage(JSetPlayerNameMessage::getTypeName())
    , m_playerName(playerName)
{}

JSetPlayerNameMessage::JSetPlayerNameMessage(const Json::Value &jsonObj)
    : JsonRequestMessage(jsonObj)
    , m_playerName(jsonObj["playername"].asString())
{}

JSetPlayerNameMessage::~JSetPlayerNameMessage()
{}

std::string JSetPlayerNameMessage::getPlayerName() const
{
    return m_playerName;
}

void JSetPlayerNameMessage::concatenateFields(Json::Value &result) const
{
    result["playername"] = m_playerName;
}
//------------End JSetPlayerNameMessage--------------

//----------------JSetPlayerNameReply----------------
JSetPlayerNameReply::JSetPlayerNameReply()
    : JsonReplyMessage(JSetPlayerNameReply::getTypeName())
{}

JSetPlayerNameReply::JSetPlayerNameReply(const Json::Value& jsonObj)
    : JsonReplyMessage(jsonObj)
{
}

JSetPlayerNameReply::~JSetPlayerNameReply()
{}

void JSetPlayerNameReply::concatenateFields(Json::Value& /*result*/) const
{}
//------------End JRequestClientNameReply----------------
