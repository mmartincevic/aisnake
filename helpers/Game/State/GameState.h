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
#include "../../Common/Uncopiable.h"

class StateManager;

class IGameState : public Uncopiable
{
public:
    virtual void Enter(StateManager* manager) = 0;
    virtual void Exit(StateManager* manager) = 0;
    virtual void Update(StateManager* manager) = 0;
    virtual void Toggle(StateManager* manager) = 0;
    virtual void Draw(StateManager* manager) = 0;
    virtual ~IGameState() = default;
};