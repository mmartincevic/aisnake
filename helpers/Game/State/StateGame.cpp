#include "StateGame.h"
#include "../../../helpers/SDL/SDLManager.h"
#include "../../../project/Sources/definitions.h"
#include <iostream>

void StateGame::Enter(StateManager* manager)
{
    std::cout << "State game enter" << std::endl;
    population = new Population(100);
}

void StateGame::Update(StateManager* manager)
{
    if (population->isDone())
    {
        population->calculateFitness();
        population->naturalSelection();
    } 
    else
    {
        population->update();
    }
}

void StateGame::Draw(StateManager* manager)
{
    DrawScore();
    DrawHighScore();
    DrawMoves();
    DrawStatus();
    DrawMatrix();
    DrawWalls();
    DrawGeneration();
    population->show();

}

void StateGame::Exit(StateManager* manager) 
{
    /*delete snake;
    snake = nullptr;*/
    delete population;
}

void StateGame::Toggle(StateManager* manager) {}

void StateGame::DrawWalls()
{
    SDL_SetRenderDrawColor(SDLManager::Instance().Renderer(), 255, 0, 0, 255);
    SDL_RenderDrawLine(SDLManager::Instance().Renderer(), 650, 50, 1450, 50);
    SDL_RenderDrawLine(SDLManager::Instance().Renderer(), 650, 50, 650, 750);
    SDL_RenderDrawLine(SDLManager::Instance().Renderer(), 650, 750, 1450, 750);
    SDL_RenderDrawLine(SDLManager::Instance().Renderer(), 1450, 50, 1450, 750);
}

void StateGame::DrawMatrix()
{
    int numCols = FIELD_WIDTH / CELL_DIMENSION;
    int numRows = FIELD_HEIGHT / CELL_DIMENSION;

    int x = FIELD_START_X;
    int y = FIELD_START_Y;

    SDL_Rect rect;
    SDL_SetRenderDrawColor(SDLManager::Instance().Renderer(), 240, 240, 240, 255);

    for (int row = 0; row < numRows; ++row)
    {
        for (int col = 0; col < numCols; ++col)
        {
            rect.x = x;
            rect.y = y;
            rect.w = CELL_DIMENSION;
            rect.h = CELL_DIMENSION;
            SDL_RenderDrawRect(SDLManager::Instance().Renderer(), &rect);
            x += CELL_DIMENSION;
        }

        y += CELL_DIMENSION;
        x = FIELD_START_X;
    }

}

BodyPart StateGame::calculateInitialPosition(Direction direction)
{
    int centerX = FIELD_START_X + (FIELD_WIDTH / 2);
    int centerY = FIELD_START_Y + (FIELD_HEIGHT / 2);

    int nearestCellX = centerX - (centerX % CELL_DIMENSION) + (CELL_DIMENSION / 2);
    int nearestCellY = centerY - (centerY % CELL_DIMENSION) + (CELL_DIMENSION / 2);

    BodyPart initialPosition;
    initialPosition.m_position = Vector2(nearestCellX, nearestCellY);
    initialPosition.m_width = CELL_DIMENSION;
    initialPosition.m_height = CELL_DIMENSION;
    initialPosition.m_direction = direction;
    return initialPosition;
}

BodyPart StateGame::calculateRandomInitialPosition()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int randX = FIELD_START_X + (std::rand() % (FIELD_WIDTH / CELL_DIMENSION)) * CELL_DIMENSION;
    int randY = FIELD_START_Y + (std::rand() % (FIELD_HEIGHT / CELL_DIMENSION)) * CELL_DIMENSION;

    BodyPart initialPosition;
    initialPosition.m_position = Vector2(randX, randY);
    initialPosition.m_width = CELL_DIMENSION;
    initialPosition.m_height = CELL_DIMENSION;
    initialPosition.m_direction = Direction::LEFT;
    return initialPosition;
}


void StateGame::DrawScore()
{
    char buffer[50];
    std::sprintf(buffer, "SCORE: %d", population->bestSnake()->getScore());

    SDL_Color color = { 123, 123, 123, 255 };
    SDL_Texture* textTexture = SDLManager::Instance().renderText(buffer, color);

    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);
    SDL_Rect destRect = { 10, 70, textWidth, textHeight };  // Position at (100, 100)
    SDL_RenderCopy(SDLManager::Instance().Renderer(), textTexture, nullptr, &destRect);
}

void StateGame::DrawHighScore()
{
    char buffer[50];
    std::sprintf(buffer, "HIGHSCORE: %d", 1);

    SDL_Color color = { 123, 123, 123, 255 };
    SDL_Texture* textTexture = SDLManager::Instance().renderText(buffer, color);

    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);
    SDL_Rect destRect = { 10, 50, textWidth, textHeight };  // Position at (100, 100)
    SDL_RenderCopy(SDLManager::Instance().Renderer(), textTexture, nullptr, &destRect);
}

void StateGame::DrawMoves()
{
    char buffer[50];
    std::sprintf(buffer, "Moves: %d", population->bestSnake()->getMoves());

    SDL_Color color = { 123, 123, 123, 255 };
    SDL_Texture* textTexture = SDLManager::Instance().renderText(buffer, color);

    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);
    SDL_Rect destRect = { 10, 30, textWidth, textHeight };  // Position at (100, 100)
    SDL_RenderCopy(SDLManager::Instance().Renderer(), textTexture, nullptr, &destRect);
}

void StateGame::DrawStatus()
{
    char buffer[50];
    std::string testAlive = (population->isDone()) ? "Alive" : "Dead";
    std::sprintf(buffer, "Status: %s", testAlive.c_str());

    SDL_Color color = { 123, 123, 123, 255 };
    SDL_Texture* textTexture = SDLManager::Instance().renderText(buffer, color);

    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);
    SDL_Rect destRect = { 10, 10, textWidth, textHeight };  // Position at (100, 100)
    SDL_RenderCopy(SDLManager::Instance().Renderer(), textTexture, nullptr, &destRect);
}

void StateGame::DrawGeneration()
{
    char buffer[50];
    std::sprintf(buffer, "Generation: %d", population->getGeneration());

    SDL_Color color = { 123, 123, 123, 255 };
    SDL_Texture* textTexture = SDLManager::Instance().renderText(buffer, color);

    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);
    SDL_Rect destRect = { 10, 90, textWidth, textHeight };  // Position at (100, 100)
    SDL_RenderCopy(SDLManager::Instance().Renderer(), textTexture, nullptr, &destRect);
}