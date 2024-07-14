#include "functions.h"
#include <random>
#include <algorithm>
#include <stdexcept>
#include "../../helpers/SDL/SDLManager.h"

std::random_device rd;
std::mt19937 gen(rd());

int randomIntInRange(int min, int max)
{
    std::uniform_int_distribution<> distr(min, max);
    return distr(gen);
}

float randomFloatInRange(float min, float max)
{
    std::uniform_real_distribution<> distr(min, max);
    return distr(gen);
}

float randomGaussian(float mean, float stddev)
{
    std::normal_distribution<float> distribution(mean, stddev);
    return distribution(gen);
}

void DrawCircle(int32_t centreX, int32_t centreY, int32_t radius)
{
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(SDLManager::Instance().Renderer(), centreX + x, centreY - y);
        SDL_RenderDrawPoint(SDLManager::Instance().Renderer(), centreX + x, centreY + y);
        SDL_RenderDrawPoint(SDLManager::Instance().Renderer(), centreX - x, centreY - y);
        SDL_RenderDrawPoint(SDLManager::Instance().Renderer(), centreX - x, centreY + y);
        SDL_RenderDrawPoint(SDLManager::Instance().Renderer(), centreX + y, centreY - x);
        SDL_RenderDrawPoint(SDLManager::Instance().Renderer(), centreX + y, centreY + x);
        SDL_RenderDrawPoint(SDLManager::Instance().Renderer(), centreX - y, centreY - x);
        SDL_RenderDrawPoint(SDLManager::Instance().Renderer(), centreX - y, centreY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void DrawPoint(int32_t centreX, int32_t centreY)
{
    SDL_RenderDrawPoint(SDLManager::Instance().Renderer(), centreX, centreY);
}


void DrawLine(int32_t fromX, int32_t fromY, int32_t toX, int32_t toY, SDL_Color color)
{
    SDL_SetRenderDrawColor(SDLManager::Instance().Renderer(), color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(SDLManager::Instance().Renderer(), fromX, fromY, toX, toY);
}

