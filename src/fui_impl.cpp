#include "fui_impl.h"
#include "fui_config.h"
#include "fui_error.h"
#include "animator_task.h"
#include <SDL3_image/SDL_image.h>

int FUiImpl::Init()
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(FUI_LOG, "SDL_Init error: %s", SDL_GetError());
        return FUI_ERROR_SDL_ERROR;
    }

    if (!SDL_CreateWindowAndRenderer("Test FUi", 800, 600, SDL_WINDOW_HIDDEN, &window_, &renderer_)) {
        SDL_LogError(FUI_LOG, "SDL_CreateWindowAndRenderer error: %s", SDL_GetError());
        return FUI_ERROR_SDL_ERROR;
    }

    SDL_ShowWindow(window_);

    InitUiTasks();

    return FUI_ERROR_OK;
}

void FUiImpl::RenderTexture(SDL_Texture *texture)
{
    /* Display the image */
    SDL_RenderTexture(renderer_, texture, NULL, NULL);
    SDL_RenderPresent(renderer_);
}

void FUiImpl::RenderSurface(SDL_Surface *surface)
{
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer_, surface);
    RenderTexture(texture);
}

void FUiImpl::InitUiTasks()
{
    AnimatorTask::GetInstance().Init();
}
