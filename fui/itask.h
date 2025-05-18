#pragma once

class ITask
{
public:
    void Init();
    virtual void Callback() = 0;
};