
#ifndef TASK_HPP
#define TASK_HPP 1

#include <coroutine>
#include "PromiseType.hpp"

// asynchronous polling task, Base
class Task : public std::coroutine_handle<void>
{
public:
    struct promise_type : public promise_type_base<Task>
    {
        constexpr auto initial_suspend() noexcept { return std::suspend_always{}; }
        constexpr auto final_suspend() noexcept { return std::suspend_always{}; }

        void unhandled_exception() {  } // do not handle any exceptions
        void return_void() noexcept
        {
        } /*do nothing*/
    };

public:
    Task(std::coroutine_handle<void> handle = nullptr) : std::coroutine_handle<void>(handle) {}

};

#endif