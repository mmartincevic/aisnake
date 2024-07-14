#include "SDLManager.h"
#include <iostream>
#include <SDL_image.h>

SDLManager& SDLManager::Instance()
{
    static SDLManager instance;
    return instance;
}

SDLManager::SDLManager() : m_window(nullptr), m_renderer(nullptr), m_quit(false) {}

SDLManager::~SDLManager()
{
    Cleanup();
}

bool SDLManager::Init(const std::string& title, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!m_window)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_renderer)
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        // Handle error...
    }

    m_font = TTF_OpenFont("../vendors/sfprobold.ttf", 16);
    if (m_font == nullptr)
    {
        std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return 1;
    }

    SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    return true;
}

void SDLManager::Cleanup()
{
    m_textures.clear();

    if (m_renderer)
    {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
    if (m_window)
    {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }

    if (m_font)
    {
        TTF_CloseFont(m_font);
        m_font = nullptr;
    }

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

bool SDLManager::LoadTexture(const std::string& id, const std::string& path)
{
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface)
    {
        std::cerr << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    if (!texture)
    {
        std::cerr << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    m_textures[id] = std::make_unique<SDLTexture>(texture);
    return true;
}

SDLTexture* SDLManager::GetTexture(const std::string& id)
{
    auto it = m_textures.find(id);
    if (it != m_textures.end())
    {
        return it->second.get();
    }
    return nullptr;
}

void SDLManager::Clear()
{
    SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(m_renderer);
}

void SDLManager::Present()
{
    SDL_RenderPresent(m_renderer);
}

bool SDLManager::HandleEvents()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            m_quit = true;
        }
    }
    return !m_quit;
}

SDL_Texture* SDLManager::renderText(const std::string& text, SDL_Color color)
{
    SDL_Surface* surface = TTF_RenderText_Solid(m_font, text.c_str(), color);
    if (surface == nullptr)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    if (texture == nullptr)
    {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
    }

    SDL_FreeSurface(surface);
    return texture;
}