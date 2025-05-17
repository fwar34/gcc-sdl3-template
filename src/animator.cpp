#include "animator.h"
#include "fui.h"
#include "animator_task.h"

Animator::Animator(const std::string &imageSrc, size_t imageCount, 
    int intervalMs, AnimatorLoadType loadType) : 
    imageSrc_(imageSrc), imageCount_(imageCount), 
    intervalMs_(intervalMs), loadType_(loadType)
{
    UpdateStartIndex();
}

Animator::~Animator()
{
    for (auto surface : images_) {
        if (surface) {
            SDL_DestroySurface(surface);
        }
    }
}

void Animator::Setup(const std::string &imageSrc, size_t imageCount, 
    int intervalMs, AnimatorLoadType loadType)
{
    imageSrc_ = imageSrc;
    imageCount_ = imageCount;
    intervalMs_ = intervalMs;
    loadType_ = loadType;
    UpdateStartIndex();
}

void Animator::Start()
{
    state_ = AnimatorState::ANIMATOR_START;
    AnimatorTask::GetInstance().AddAnimator(this);
}

void Animator::Stop()
{
    Reset();
    state_ = AnimatorState::ANIMATOR_STOP;
    AnimatorTask::GetInstance().DelAnimator(this);
}

void Animator::Pause()
{
    state_ = AnimatorState::ANIMATOR_PAUSE;
    AnimatorTask::GetInstance().DelAnimator(this);
}

void Animator::Resume()
{
    Start();
}

void Animator::Play()
{
    if (state_ != AnimatorState::ANIMATOR_START) {
        return;
    }

    uint64_t currentTick = SDL_GetTicks();
    if (currentTick - lastTick_ >= intervalMs_) {
        lastTick_ = currentTick;
        if (loadType_ == AnimatorLoadType::ANIMATOR_LOAD_ALL) {
            if (images_.empty()) {
                LoadAllImages();
            }

            FUi::GetInstance().RenderSurface(images_[curIndex_++]);
            if (curIndex_ >= imageCount_ || curIndex_ >= images_.size()) {
                curIndex_ = 0;
            }
        } else {
            std::string imageName = NextImage();
            SDL_Surface *surface = IMG_Load(imageName.c_str());
            FUi::GetInstance().RenderSurface(surface);
            SDL_DestroySurface(surface);
        }
    }
}

void Animator::Reset()
{
    curIndex_ = 0;
}

std::string Animator::ConcateImageName(int imageIndex_)
{
    std::string imageName = "A_";
    imageName += imageIndex_;
    imageName += ".jpg";
    return imageName;
}

std::string Animator::NextImage()
{
    std::string imageName = ConcateImageName(curIndex_);
    curIndex_++;
    if (curIndex_ >= startIndex_ + imageCount_) {
        curIndex_ = startIndex_;
    }
    return imageName;
}

void Animator::LoadAllImages()
{
    std::string imageName;
    if (images_.empty() && loadType_ == AnimatorLoadType::ANIMATOR_LOAD_ALL) {
        for (int i = startIndex_; i < startIndex_ + imageCount_; i++) {
            imageName = ConcateImageName(i);
            images_.push_back(IMG_Load(imageName.c_str()));
        }
    }
}

void Animator::UpdateStartIndex()
{
    std::string::size_type pos = imageSrc_.find_last_of('_');
    std::string::size_type posOfPoint = imageSrc_.find_last_of('.');
    if (pos != std::string::npos && 
        posOfPoint != std::string::npos && pos < posOfPoint) {
        std::string numStr = imageSrc_.substr(pos + 1, posOfPoint - pos - 1);
        startIndex_ = std::stoi(numStr);
    }
}
