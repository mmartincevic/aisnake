#include "Button.h"
#include "../../helpers/SDL/SDLManager.h"

void Button::Show() const
{
    SDL_Rect rect;
    rect.x = m_PositionX;
    rect.y = m_PositionY;
    rect.w = m_Width;
    rect.h = m_Height;
    SDL_RenderDrawRect(SDLManager::Instance().Renderer(), &rect);
}