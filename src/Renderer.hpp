#pragma once

#include <cstdint>

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

class Renderer
{
public:
    Renderer(char const* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight);
    ~Renderer();
    void UpdateScreen(void const* buffer, int pitch);
    bool ProcessInput(uint8_t* keys);

private:
    SDL_Window* sdlWindow{};
    SDL_Renderer* sdlRenderer{};
    SDL_Texture* sdlTexture{};
};
