#include "fui.h"
#include "fui_service.h"

int FUi::Init()
{
    return impl.Init();
}

void FUi::Schedule()
{
    FUiService::GetInstance().Schedule();
}

void FUi::RenderTexture(SDL_Texture *texture)
{
    impl.RenderTexture(texture);
}

void FUi::RenderSurface(SDL_Surface *surface)
{
    impl.RenderSurface(surface);
}
