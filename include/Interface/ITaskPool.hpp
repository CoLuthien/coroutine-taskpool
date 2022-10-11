
#ifndef I_TASK_POOL_HPP
#define I_TASK_POOL_HPP 1

#include <coroutine>

// CR
template <class T>
class ITaskPool
{
public:
    using TaskType = T;

public:
    ITaskPool() = default;
    virtual ~ITaskPool() = default;

public:
    virtual void SubmitTask(TaskType const& TaskToExecute) = 0;
    virtual void StartExecute() = 0;
    virtual void StopExecute() = 0;
};

#endif