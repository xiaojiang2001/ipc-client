#ifndef SINGLETON_H
#define SINGLETON_H


#include <QMutex>
#include <QMutexLocker>
#include <QScopedPointer>

// 单例模式模板类
template <typename T>
class Singleton
{
public:
    // 获取单例实例
    static T& getInstance();

    Singleton(const Singleton &other) = default; // 禁止复制构造函数
    Singleton<T> &operator=(const Singleton &other) = default;   // 禁止赋值操作符

    ~Singleton() = default; // 默认析构函数
private:
    static QMutex mutex;
    static QScopedPointer<T> instance;         
};


template<typename T>
T & Singleton<T>::getInstance()
{
 if (instance.isNull()) {
        mutex.lock();
        if (instance.isNull()) {
            instance.reset(new T());
        }
        mutex.unlock();
    }
    return *instance.data();    // 返回单例实例的引用
}

// 使用宏简化单例模式的声明
// 例如: SINGLETON(MyClass) 
#define SINGLETON(Class) \
    private: \
    Class(); \
    ~Class(); \
    Class(const Class &other); \
    Class &operator =(const Class &other); \
    friend class Singleton<Class>; \
    friend struct QScopedPointerDeleter<Class>;


#endif // SINGLETON_H
