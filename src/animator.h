#pragma once
#include "ianimator.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include <string>

class Animator : public IAnimator
{
public:
    enum class AnimatorLoadType
    {
        ANIMATOR_LOAD_SINGLE,
        ANIMATOR_LOAD_ALL,
    };
    Animator() = default;
    Animator(const std::string &imageSrc, size_t imageCount, 
        int intervalMs, AnimatorLoadType loadType);
    ~Animator();

    void Setup(const std::string &imageSrc, size_t imageCount, 
        int intervalMs, AnimatorLoadType loadType);
    void Start() override;
    void Stop() override;
    void Pause() override;
    void Resume() override;
    void Play() override;

private:
    void Reset();
    std::string ConcateImageName(int imageIndex_);
    std::string NextImage();
    void LoadAllImages();
    void UpdateStartIndex();

private:
    std::vector<SDL_Surface *> images_;
    int startIndex_ = 0;
    int curIndex_ = 0;
    int intervalMs_;
    uint64_t lastTick_ = 0;
    std::string imageSrc_;
    size_t imageCount_;
    bool infinite_ = false;
    AnimatorLoadType loadType_ = AnimatorLoadType::ANIMATOR_LOAD_ALL;
};