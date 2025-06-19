#ifndef SINGLETON_H
#define SINGLETON_H

#include <QMutex>
#include <QScopedPointer>

template <typename T>
class Singleton
{
public:
    static T *getInstance() {
        // C++11保证局部静态变量的初始化是线程安全的
        static T instance;
        return &instance;
    }
    Singleton(const Singleton &other) = default;
    Singleton<T> &operator=(const Singleton &other) = default;

private:
    Singleton() = default;
    virtual ~Singleton() = default;

};

// 简化的宏定义
#define SINGLETON(Class) \
    private: \
        Class(); \
        ~Class(); \
        friend class Singleton<Class>;

#endif // SINGLETON_H

