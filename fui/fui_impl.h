#pragma once
#include <SDL3/SDL.h>

class FUiImpl
{
public:
    int Init();
    void RenderTexture(SDL_Texture *texture);
    void RenderSurface(SDL_Surface *surface);

private:
    void InitUiTasks();

private:
    SDL_Window *window_;
    SDL_Renderer *renderer_;
};