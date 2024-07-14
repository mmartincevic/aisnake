#include "SDLTexture.h"

SDLTexture::SDLTexture(SDL_Texture* texture) : m_texture(texture) {}

SDLTexture::~SDLTexture()
{
    if (m_texture)
    {
        SDL_DestroyTexture(m_texture);
    }
}