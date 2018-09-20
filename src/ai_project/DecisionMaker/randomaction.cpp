#include "randomaction.h"

RandomAction::RandomAction()
{

}

ActionType RandomAction::getAction() const
{
    std::vector<ActionType> inActions = {ActionType::Bomb, ActionType::Down, ActionType::Hold, ActionType::Left, ActionType::Right, ActionType::Up};

    ActionType selectedAction = RandomAction::getAction(inActions);
    return selectedAction;

}

ActionType RandomAction::getAction(std::vector<ActionType> inActions) const
{

    unsigned int nActions = inActions.size();
    if (nActions == 0)
    {
         return ActionType::Hold;
    }
    else
    {
        unsigned int iSelectedAction = unsigned(rand()) % nActions;
        return inActions[iSelectedAction];
    }
}
