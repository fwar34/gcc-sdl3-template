#include "fui_service.h"

void FUiService::AddTask(ITask *task)
{
    if (!task) {
        return;
    }

    tasks_.push_back(task);
    tasks_.unique();
}

void FUiService::Schedule()
{
    for (auto task : tasks_) {
        task->Callback();
    }
}
