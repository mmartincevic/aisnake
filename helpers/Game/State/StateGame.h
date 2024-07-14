#pragma once

#include "GameState.h"
#include "StateManager.h"
#include "../../../project/Sources/Snake.h"
#include "../../../project/Sources/Population.h"
#include "../../../project/Sources/Vector2.h"
#include "../../Input/SimpleInputManager.h"

class StateGame : public IGameState
{
public:
    void Enter(StateManager* manager) override;
    void Exit(StateManager* manager) override;
    void Update(StateManager* manager) override;
    void Draw(StateManager* manager) override;
    void Toggle(StateManager* manager) override;

public:
    void DrawMatrix();
    void DrawWalls();


    void DrawScore();
    void DrawHighScore();
    void DrawMoves();
    void DrawStatus();
    void DrawGeneration();

private:
    BodyPart calculateInitialPosition(Direction direction);
    BodyPart calculateRandomInitialPosition();

private:
    Population* population = nullptr;
};
