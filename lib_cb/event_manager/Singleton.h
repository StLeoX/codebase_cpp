//
// Created by StLeoX on 2022/10/17.
//

#pragma once

template<typename T>
class Singleton
{
public:
    Singleton() {}

    ~Singleton() {}

    static T &GetSingleton()
    {
        static T s_singleton;
        return s_singleton;
    }

private:
    Singleton(const Singleton &) = delete;

    const Singleton &operator=(const Singleton &) = delete;
};
