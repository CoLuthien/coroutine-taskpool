
#ifndef I_TASK_EXECUTOR_HPP
#define I_TASK_EXECUTOR_HPP 1

template <class T>
class ITaskExecutor
{
public:
    void AssignTask()
    {
        static_cast<T*>(this)->Assign();
    }

};
#endif