#include "itask.h"
#include "fui_service.h"

void ITask::Init()
{
    FUiService::GetInstance().AddTask(this);
}
