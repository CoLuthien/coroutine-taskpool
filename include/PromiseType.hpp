#ifndef PROMISE_TYPE_HPP
#define PROMISE_TYPE_HPP 1

#include <coroutine>

template <class T>
struct promise_type_base
{
    T get_return_object()
    {
        return T{std::coroutine_handle<typename T::promise_type>::from_promise(
            *static_cast<typename T::promise_type *>(this))};
    }
};

#endif