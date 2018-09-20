#include "Util.h"

#include <sstream>
#include <stdexcept>

#include "define.h"
#include "Logger.h"

namespace Util
{
    std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems) {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }

    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        Util::split(s, delim, elems);
        return elems;
    }

    std::string ActionToStr(const ActionType& move)
    {
        switch (move)
        {
        case ActionType::Left:
            return "left";
            break;
        case  ActionType::Right:
            return "right";
            break;
        case ActionType::Up:
            return "up";
            break;
        case ActionType::Down:
            return "down";
            break;
        case ActionType::Bomb:
            return "bomb";
            break;
        case ActionType::Hold:
            return "hold";
            break;
        default:
            return "unknown";
        }
    }

    ActionType StrToAction(const std::string& move)
    {
        if (!move.compare("left"))
        {
            return ActionType::Left;
        }
        else if (!move.compare("right"))
        {
            return ActionType::Right;
        }
        else if (!move.compare("up"))
        {
            return ActionType::Up;
        }
        else if (!move.compare("down"))
        {
            return ActionType::Down;
        }
        else if (!move.compare("bomb"))
        {
            return ActionType::Bomb;
        }
        else if (!move.compare("hold"))
        {
            return ActionType::Hold;
        }
        else
        {
#ifdef LOGGER
            LOGGER->Logf(Logger::Error, "[Util] Could not convert '%s' to a valid move.", move.c_str());
#endif
            return ActionType::Hold;
        }
    }

    std::string GameStateToStr(const GameState &gs)
    {
        switch( gs )
        {
        case GameState::Finished:
            return "Finished";
            break;
        case GameState::Started:
            return "Started";
            break;
        case GameState::Waiting:
            return "Waiting";
            break;
        default:
            return "Unknown";
        }
    }

    GameState StrToGameState(const std::string &gs)
    {
        if (!gs.compare("Finished"))
        {
            return GameState::Finished;
        }
        else if (!gs.compare("Started"))
        {
            return GameState::Started;
        }
        else if (!gs.compare("Waiting"))
        {
            return GameState::Waiting;
        }
        else throw std::runtime_error("Illegal conversion: " + gs);
    }

    void trimLead(std::string &str)
    {
        size_t p = str.find_first_not_of(" \t");
        str.erase(0,p);
    }

    void trimTrail(std::string &str)
    {
        size_t p = str.find_last_not_of(" \t");
        if ( std::string::npos != p )
        {
            str.erase(p+1);
        }
    }

    void trim(std::string &str)
    {
        trimLead(str);
        trimTrail(str);
    }

    const QByteArray b64toQByteArray(const std::string &b64)
    {
        QByteArray text = QByteArray::fromBase64(b64.c_str());
        return text;
    }

#ifdef QT_GUI_LIB
    const QPixmap QByteArrayToQPixmap(const QByteArray &qba)
    {
        QPixmap qpm;
        qpm.loadFromData(qba, "PNG");
        return qpm;
    }
#endif
}
