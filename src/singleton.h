#pragma once

template <typename T>
class Singleton
{
public:
    static T &GetInstance()
    {
        static T t;
        return t;
    }

protected:
    Singleton() = default;
    ~Singleton() = default;
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
    Singleton(Singleton &&) = delete;
    Singleton &operator=(Singleton &&) = delete;
};