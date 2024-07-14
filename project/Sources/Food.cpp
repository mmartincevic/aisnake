#include "Food.h"
#include "../../helpers/SDL/SDLManager.h"

void Food::Show() const
{
    SDL_Rect rect;
    rect.x = m_Position.x;
    rect.y = m_Position.y;
    rect.w = m_Width;
    rect.h = m_Height;
    SDL_SetRenderDrawColor(SDLManager::Instance().Renderer(), 0x00, 0x00, 0xFF, 0xFF);
    SDL_RenderFillRect(SDLManager::Instance().Renderer(), &rect);
}