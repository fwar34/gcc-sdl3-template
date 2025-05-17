#pragma once

enum class AnimatorState
{
    ANIMATOR_START,
    ANIMATOR_PAUSE,
    ANIMATOR_STOP,
};

class IAnimator
{
public:
    virtual void Play() = 0;
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual void Pause() = 0;
    virtual void Resume() = 0;

protected:
    AnimatorState state_ = AnimatorState::ANIMATOR_STOP;
};