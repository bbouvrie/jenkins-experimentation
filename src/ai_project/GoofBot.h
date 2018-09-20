#ifndef GOOFBOT_H
#define GOOFBOT_H

#include "goofgamestate.h"
#include "AIBaseClass.h"


#include <string>
#include <vector>



class __declspec(dllexport) GoofBot : public AIBaseClass
// om te testen __ toegevoegd
{
public:
    GoofBot();

    ~GoofBot();

    const std::string& GetName();

    const std::string& GetIcon();

    ActionType GetAction(const GameStateContainer& container);

     private:
    // DO NOT CHANGE //
    static const std::string m_name;

    static const std::string m_icon;
};


#endif // GOOFBOT_H
