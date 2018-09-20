#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <string>
#include <QByteArray>

#ifdef QT_GUI_LIB
#include <QPixmap>
#endif

enum class ActionType;
enum class GameState;

namespace Util
{
    /**
     * @brief split Takes a string s, splits it in chuncks at position delim
     * @param s String to be split
     * @param delim Character to split stream at
     * @param elems String vector to place separate chunks in
     * @return
     */
    std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems);

    /**
     * @brief split Takes a string s, splits it in chuncks at position delim
     * @param s String to be split
     * @param delim Character to split stream at
     * @return
     */
    std::vector<std::string> split(const std::string &s, char delim);

    /**
     * @brief ActionToStr Returns a string given an action type
     * @param move ActionType to be converted to string
     * @return
     */
    std::string ActionToStr(const ActionType& move);

    /**
     * @brief StrToAction Returns an action type given a string
     * @param move The string to be converted to ActionType
     * @return
     */
    ActionType StrToAction(const std::string& move);

    /**
     * @brief GameStateToStr Returns a string given a GameState
     * @param gs The GameState to be converted to string
     * @return
     */
    std::string GameStateToStr(const GameState& gs);

    /**
     * @brief StrToGameState Returns a GameState given a string
     * @param gs The string to be converted to GameState
     * @return
     */
    GameState StrToGameState(const std::string& gs);

    void trimLead( std::string& str );

    void trimTrail( std::string& str );

    void trim( std::string& str );

    const QByteArray b64toQByteArray( const std::string& b64);

#ifdef QT_GUI_LIB
    const QPixmap QByteArrayToQPixmap( const QByteArray& qba);
#endif
}

#endif //UTIL_H
