#include "../fui/fui.h"
#include <unistd.h>
int main(int argc, char *argv[])
{
    FUi::GetInstance().Init();

    // 打印当前工作目录
    // char cwd[1024];
    // if (getcwd(cwd, sizeof(cwd)) != NULL) {
    //     printf("当前工作目录: %s\n", cwd);
    // }

    Animator animator;
    // animator.Setup(std::string("A_0000.jpg"), 60, 16, // 圆形
    //     Animator::AnimatorLoadType::ANIMATOR_LOAD_ALL);
    animator.Setup(std::string("A_0000.jpg"), 240, 16,  // 花朵
        Animator::AnimatorLoadType::ANIMATOR_LOAD_SINGLE);
    animator.Start();

    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.key == SDLK_Q) {
                    quit = true;
                }
            } else if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }
        FUi::GetInstance().Schedule();
        SDL_Delay(FUI_DELAY); // 60帧
    }

    animator.Stop();

    return 0;
}