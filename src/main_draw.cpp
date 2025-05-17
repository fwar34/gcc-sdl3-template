#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

void DrawRect(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    // 空心矩形
    SDL_FRect rect = {100, 100, 200, 150};
    SDL_RenderRect(renderer, &rect);

    SDL_FRect filledRect = {300, 400, 100, 150};
    SDL_RenderFillRect(renderer, &filledRect);
}
int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Shape demo", 800, 600, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);


    int running = 1;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        /* --- 绘制操作在此处进行 --- */
        DrawRect(renderer);

        // 更新屏幕
        SDL_RenderPresent(renderer);
    }

    // 清理资源
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}