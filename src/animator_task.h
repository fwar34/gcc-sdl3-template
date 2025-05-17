#pragma once
#include "itask.h"
#include "ianimator.h"
#include "singleton.h"
#include <unordered_set>

class AnimatorTask : public ITask, public Singleton<AnimatorTask>
{
public:
    void Callback() override;
    void AddAnimator(IAnimator *animator);
    void DelAnimator(IAnimator *animator);

protected:
    AnimatorTask() = default;
    ~AnimatorTask() = default;
    friend class Singleton<AnimatorTask>;

private:
    std::unordered_set<IAnimator *> animators_; 
};