/*
*           ___            __    ___  __    ___       _ _                 _       _
*          / __\ __  _ __ / _\  /   \/ /   / __\ ___ (_) | ___ _ __ _ __ | | __ _| |_ ___
*         / / | '_ \| '_ \\ \  / /\ / /   /__\/// _ \| | |/ _ \ '__| '_ \| |/ _` | __/ _ \
*        / /__| |_) | |_) |\ \/ /_// /___/ \/  \ (_) | | |  __/ |  | |_) | | (_| | ||  __/
*        \____/ .__/| .__/\__/___,'\____/\_____/\___/|_|_|\___|_|  | .__/|_|\__,_|\__\___|
*             |_|   |_|                                            |_|
*
* Created by:   djomla
* Updated by:   djomla
*/
#pragma once
#include <iostream>
#include "GameState.h"


class StateManager
{
public:
    StateManager() : m_CurrentState(nullptr) {}
    void Toggle();
    void Update();
    void Draw();
    void Exit();
    void SetState(IGameState* currentState);

    template<typename T, class... ARGS>
    void SetNextState(ARGS... args)
    {
        this->SetState(new T(args...));
    }

    inline IGameState* GetCurrentState() { return m_CurrentState; }

    ~StateManager()
    {
        if (m_CurrentState && m_CurrentState != nullptr)
        {
            delete m_CurrentState;
        }
    }
protected:
    IGameState* m_CurrentState;
};