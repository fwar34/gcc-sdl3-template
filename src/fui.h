#pragma once
#include "fui_impl.h"
#include "fui_config.h"
#include "singleton.h"

class FUi : public Singleton<FUi>
{
public:
    int Init();
    void Schedule();
    void RenderTexture(SDL_Texture *texture);
    void RenderSurface(SDL_Surface *surface);

protected:
    FUi() = default;
    ~FUi() = default;
    friend class Singleton<FUi>;

private:
    FUiImpl impl;
};