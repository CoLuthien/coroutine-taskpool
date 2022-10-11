
#include <memory>
#include <iostream>
#include <coroutine>

#include "Task.hpp"
#include "TaskPool.hpp"

auto CoroutineTest(int a, int b) -> Task
{

    std::cout << "First Input is: " << a << '\n';
    co_await std::suspend_always{};

    std::cout << "Next Input is :" << b << '\n';

    co_return;
}

void DoTest(std::shared_ptr<TaskPool> pool)
{
    pool->SubmitTask(CoroutineTest(3, 4));
    pool->SubmitTask(CoroutineTest(12, 1));
}

int main()
{
    std::cout << "0";
    auto pool = std::make_shared<TaskPool>();
    std::cout << "1";
    std::cout << "2";
    DoTest(pool);
    pool->StartExecute();
    DoTest(pool);
    pool->StopExecute();
    DoTest(pool);
    pool->StartExecute();

}