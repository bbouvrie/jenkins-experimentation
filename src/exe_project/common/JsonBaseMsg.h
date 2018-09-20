#ifndef __JSONBASEMESSAGE_H__
#define __JSONBASEMESSAGE_H__

#include <iostream>
#include "json/json.h"

//------------JsonBaseMsg--------------
/**
 * @brief Abstract class defining an interface for all Requests, Replies and Publish messages
 * that go back and forth between the client and the server
 */
class JsonBaseMsg
{
public:
    /**
     * @brief JsonBaseMsg This is an abstract class that cannot be instantiated directly
     */
    JsonBaseMsg(){}
    virtual ~JsonBaseMsg(){}

    /**
     * @brief arrayToJson Creates a Json representation of a vector of string values
     * @param values Values to be converted into a Json representation
     * @return
     */
    inline static Json::Value arrayToJson(const std::vector<std::string> &values)
    {
        Json::Value value;
        for(auto it = values.begin(); it != values.end(); it++)
            value.append((*it));

        return value;
    }

    /**
     * @brief arrayFromJson Creates a vector of strings from a json representation of an array of strings
     * @param json A json object that is an array of strings
     * @return The resulting vector of strings from the json input
     */
    inline static std::vector<std::string> arrayFromJson(const Json::Value& json)
    {
        std::vector<std::string> result;
        for (unsigned int i = 0; i < json.size();i++)
        {
            result.push_back(json[i].asString());
        }
        return result;
    }

    /**
     * @brief toJson Virtual function that returns the Json representation of an object
     * inheriting from JsonBaseMsg
     * @return
     */
    virtual Json::Value toJson() const = 0;
};
//------------End JsonBaseMsg--------------





//------------JsonPublishMessage--------------
/**
 * @brief  Abstract class defining publish notifications sent by the server to all clients
 * Publish messages are always sent to a particular room, which is why it needs a roomName
 * as argument
 */
class JsonPublishMessage : public JsonBaseMsg
{
public:
    /**
     * @brief JsonPublishMessage This abstract constructor is called by subclasses,
     * which supply the publish command.
     * @param command The textual representation command which corresponds to
     * a specific JsonPublishMessage's TypeName
     * @param roomName reference to a specific roomName which the publish message has influence on
     */
    JsonPublishMessage(const std::string &command, const std::string &roomName);

    /**
     * @brief JsonPublishMessage abstract constructor to recreate this class from
     * a json representation
     * @param json the json object representing an JsonPublishMessage
     */
    JsonPublishMessage(const Json::Value &json);

    virtual ~JsonPublishMessage();

    virtual Json::Value toJson() const;

    /**
     * @brief getCommand gets the command type of an incoming publish message
     * @param json the json object that represents a specific publish message
     * @return
     */
    inline static std::string getCommand(const Json::Value &json)
    {
        return json["Publish"].asString();
    }

    /**
     * @brief getRoomName gets the roomname of an incoming publish message
     * @param json the json object that represents a publish message
     * @return
     */
    inline static std::string getRoomName(const Json::Value &json)
    {
        return json["RoomName"].asString();
    }
protected:
    /**
     * @brief concatenateFields Concatenates information from base classes
     * (deriving from JsonBaseMsg) with information from derived classes. This method is
     * used by JsonBaseMsg::toJson()
     */
    virtual void concatenateFields(Json::Value&) const = 0;


private:
    std::string m_command;

    std::string m_roomName;
};
//------------End JsonPublishMessage--------------





//------------JsonRequestMessage--------------
/**
 * @brief Abstract class defining requests that a client can send to the server
 * One request message has to correspond to one or more reply message
 */
class JsonRequestMessage  : public JsonBaseMsg
{
public:
    /**
     * @brief JsonRequestMessage This abstract constructor is called by subclasses,
     * which supply the command that the client want to invoke on the server.
     * @param command The textual representation command which corresponds to
     * a specific JsonRequestMessage's TypeName
     */
    JsonRequestMessage(const std::string &command);

    /**
     * @brief JsonRequestMessage abstract constructor to recreate this class from
     * a json representation
     * @param json the json object representing an JsonRequestMessage
     */
    JsonRequestMessage(const Json::Value &json);

    virtual ~JsonRequestMessage();

    virtual Json::Value toJson() const;

    /**
     * @brief getCommand gets the command type of an incoming request message
     * @param json the json object that represents a specific request message
     * @return
     */
    inline static std::string getCommand(const Json::Value &json)
    {
        return json["Request"].asString();
    }

protected:

    /**
     * @brief concatenateFields Concatenates information from base classes
     * (deriving from JsonBaseMsg) with information from derived classes. This method is
     * used by JsonBaseMsg::toJson()
     */
    virtual void concatenateFields(Json::Value&) const = 0;

private:
    std::string m_command;
};
//------------End JsonRequestMessage--------------





//------------JsonReplyMessage--------------
/**
 * @brief Abstract class defining replies that are answers to a client's request.
 * Every reply message has to correspond to one or more request message
 */
class JsonReplyMessage : public JsonBaseMsg
{
public:
    /**
     * @brief JsonReplyMessage This abstract constructor is called by subclasses,
     * which supply the reply command.
     * @param command The textual representation command which corresponds to
     * a specific Jsonreplymessage's TypeName
     */
    JsonReplyMessage(const std::string &command);

    /**
     * @brief JsonReplyMessage abstract constructor to recreate this class from
     * a json representation
     * @param json the json object representing an jsonreplymessage
     */
    JsonReplyMessage(const Json::Value &json);

    virtual ~JsonReplyMessage();

    virtual Json::Value toJson() const;

    /**
     * @brief getCommand gets the command type of an incoming reply message
     * @param json the json object that represents a specific reply message
     * @return
     */
    inline static std::string getCommand(const Json::Value &json)
    {
        return json["Reply"].asString();
    }

protected:
    /**
     * @brief concatenateFields Concatenates information from base classes
     * (deriving from JsonBaseMsg) with information from derived classes. This method is
     * used by JsonBaseMsg::toJson()
     */
    virtual void concatenateFields(Json::Value&) const = 0;

private:
    std::string m_command;
};
//------------End JsonReplyMessage--------------


//------------JErrorReplyMessage--------------
/**
 * @brief Data representation of a reply that is sent
 * in response to a client's request that went wrong
 */
class JErrorReplyMessage : public JsonReplyMessage
{
public:
    /**
     * @brief Creates a JErrorMessage
     * @param reply The command that the client tried to invoke on the server
     * @param type The type of error
     * @param message The reason for the failure
     */
    JErrorReplyMessage(std::string command,std::string errorType, std::string userMessage);
    /**
     * @brief Construct a JErrorMessage object from its Json representation
     * @param json representation
     */
    JErrorReplyMessage(const Json::Value &json);

    ~JErrorReplyMessage();

    std::string getOnWhichCommand() const;
    std::string getErrorType() const;
    std::string getErrorMessage() const;

    /**
     * @brief getTypeName The name of this type of message
     */
    inline static std::string getTypeName() { return "Error"; }
protected:
    void concatenateFields(Json::Value &result) const;

private:
    std::string m_onCommand, m_errorType, m_userMessage;
};

//------------End JErrorReplyMessage--------------



#endif // __JSONBASEMESSAGE_H__
