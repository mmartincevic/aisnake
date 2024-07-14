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
#include "StateManager.h"

void StateManager::SetState(IGameState* currentState)
{
    if (m_CurrentState != nullptr)
    {
        m_CurrentState->Exit(this);
    }

    m_CurrentState = currentState;

    if (m_CurrentState != nullptr)
    {
        m_CurrentState->Enter(this);
    }
}

void StateManager::Toggle()
{
    m_CurrentState->Toggle(this);
}

void StateManager::Update()
{
    m_CurrentState->Update(this);
}

void StateManager::Draw()
{
    m_CurrentState->Draw(this);
}

void StateManager::Exit()
{
    m_CurrentState->Exit(this);
}