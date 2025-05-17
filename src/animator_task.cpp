#include "animator_task.h"

void AnimatorTask::Callback()
{
    for (auto animator : animators_) {
        animator->Play();
    }
}

void AnimatorTask::AddAnimator(IAnimator *animator)
{
    auto it = animators_.find(animator);
    if (it != animators_.end()) {
        return;
    }

    animators_.insert(animator);
}

void AnimatorTask::DelAnimator(IAnimator *animator)
{
    auto it = animators_.find(animator);
    if (it != animators_.end()) {
        animators_.erase(it);
    }
}
