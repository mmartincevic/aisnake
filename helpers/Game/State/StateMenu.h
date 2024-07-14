#pragma once

#include "GameState.h"
#include "StateManager.h"

class StateMenu : public IGameState
{
public:
    void Enter(StateManager* manager) override;
    void Exit(StateManager* manager) override;
    void Update(StateManager* manager) override;
    void Draw(StateManager* manager) override;
    void Toggle(StateManager* manager) override;
};
