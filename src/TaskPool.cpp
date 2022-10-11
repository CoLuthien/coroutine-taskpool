

#include "TaskPool.hpp"
#include <iostream>

void TaskPool::SubmitTask(TaskPool::TaskType const &TaskToExecute)
{
    std::cout << "submit";
    {
        std::scoped_lock{queue_lock};
        m_tasks.emplace(TaskToExecute);
    }
}

TaskPool::TaskType
TaskPool::FetchTask()
{
    std::scoped_lock{queue_lock};

    if (m_tasks.empty())
    {
        return {std::coroutine_handle<void>{}};
    }

    auto task = m_tasks.front();
    m_tasks.pop();
    return task;
}

void TaskPool::ExecutorMain()
{
    std::cout << "HI";
    while (true)
    {
        TaskPool::TaskType &&cur_task = FetchTask();
        if (false == (bool)cur_task)
        {
            continue;
        }

        if (cur_task.done())
            cur_task.destroy();

        cur_task.resume();

        if (cur_task.done())
        {
            cur_task.destroy();
        }
        else
        {
            SubmitTask(std::move(cur_task));
        }
    }
}

void TaskPool::StartExecute()
{
    std::cout << "Made";
    try
    {
        m_executor = std::make_unique<std::thread>([&]()
                                                   { ExecutorMain(); });
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
void TaskPool::StopExecute()
{
    m_executor->join();
}
