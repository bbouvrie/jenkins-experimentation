#include "JsonBaseMsg.h"

//------------JsonPublishMessasge--------------

JsonPublishMessage::JsonPublishMessage(const std::string &command, const std::string &roomName)
    :m_command(command), m_roomName(roomName)
{}

JsonPublishMessage::JsonPublishMessage(const Json::Value &json)
    :m_command(json["Publish"].asString()),
     m_roomName(json["RoomName"].asString())
{}

JsonPublishMessage::~JsonPublishMessage(){}

Json::Value JsonPublishMessage::toJson() const
{
    Json::Value result;
    result["Publish"] = m_command;
    result["RoomName"] = m_roomName;
    concatenateFields(result);

    return result;
}

//------------End JsonPublishMessasge--------------





//------------JsonRequestMessage--------------
JsonRequestMessage::JsonRequestMessage(const std::string &command)
    : m_command(command)
{}

JsonRequestMessage::JsonRequestMessage(const Json::Value &json)
    : m_command(json["Request"].asString())
{}

JsonRequestMessage::~JsonRequestMessage()
{}

Json::Value JsonRequestMessage::toJson() const
{
    Json::Value result;
    result["Request"] = m_command;
    concatenateFields(result);

    return result;
}

//------------End JsonRequestMessage--------------





//------------JsonReplyMessage--------------
JsonReplyMessage::JsonReplyMessage(const std::string &command)
    : m_command(command)
{}

JsonReplyMessage::JsonReplyMessage(const Json::Value &json)
    : m_command(json["Reply"].asString())
{}


JsonReplyMessage::~JsonReplyMessage()
{}


Json::Value JsonReplyMessage::toJson() const
{
    Json::Value result;
    result["Reply"] = m_command;
    concatenateFields(result);

    return result;
}

//------------End JsonReplyMessage--------------


//------------JErrorReplyMessage--------------
JErrorReplyMessage::JErrorReplyMessage(std::string command, std::string errorType, std::string userMessage)
    :JsonReplyMessage(JErrorReplyMessage::getTypeName()), m_onCommand(command), m_errorType(errorType), m_userMessage(userMessage)
{}

JErrorReplyMessage::JErrorReplyMessage(const Json::Value &json)
    : JsonReplyMessage(json),
      m_onCommand(json["OnCommand"].asString()),
      m_errorType(json["ErrorType"].asString()),
      m_userMessage(json["UserMessage"].asString())
{}

JErrorReplyMessage::~JErrorReplyMessage()
{}

std::string JErrorReplyMessage::getOnWhichCommand() const
{
    return m_onCommand;
}

std::string JErrorReplyMessage::getErrorType() const
{
    return m_errorType;
}

std::string JErrorReplyMessage::getErrorMessage() const
{
    return m_userMessage;
}

void JErrorReplyMessage::concatenateFields(Json::Value &result) const
{
    result["OnCommand"] = m_onCommand;
    result["ErrorType"] = m_errorType;
    result["UserMessage"] = m_userMessage;
}



//------------End JErrorReplyMessage--------------
