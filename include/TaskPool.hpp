
#ifndef TASK_POOL_HPP
#define TASK_POOL_HPP 1

#include <coroutine>
#include <memory>
#include <thread>
#include <mutex>
#include <queue>

#include "Interface/ITaskPool.hpp"
#include "Task.hpp"

// SingleThreaded
class TaskPool : public ITaskPool<Task>
{
public:
    using TaskType = Task;

public:
    virtual void SubmitTask(TaskType const& TaskToExecute) override;
    virtual void StartExecute() override;
    virtual void StopExecute() override;

private:
    void ExecutorMain();
    TaskType FetchTask();

private:
    std::unique_ptr<std::thread> m_executor;
    std::queue<TaskType> m_tasks;
    std::mutex queue_lock;
};

#endif