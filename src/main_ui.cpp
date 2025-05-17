#include "fui.h"
int main(int argc, char *argv[])
{
    FUi::GetInstance().Init();
    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }
        FUi::GetInstance().Schedule();
        SDL_Delay(FUI_DELAY); // 60帧
    }

    return 0;
}