#pragma once
#include "itask.h"
#include "singleton.h"
#include <list>

class FUiService : public Singleton<FUiService>
{
public:
    void AddTask(ITask *task);
    void Schedule();

private:
    FUiService() {};
    friend class Singleton<FUiService>;

private:
    std::list<ITask *> tasks_;
};