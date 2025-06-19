#ifndef WIDGETPOOL_H
#define WIDGETPOOL_H

#include <QWidget>
#include <QMutex>
#include <QList>
#include <QMutexLocker>
#include <QStack>
#include <QDebug>

// 创建多路摄像头窗口对象池
template <typename T>
class widgetPool
{
public:
    // 构造函数
    widgetPool(int poolSize = 16, QWidget *parent = nullptr)
        : m_poolSize(poolSize), m_usedSize(poolSize)
    {
        // 初始化池中的对象
        for (int i = 0; i < m_poolSize; ++i) {
            T* widget = new T(); // 创建新的窗口对象
            widget->setParent(parent); // 设置父窗口
            widget->hide();
            m_pool.push(widget);      // 将对象添加到池中
        }
        // 初始化使用大小为0
        m_usedSize = 0;
    }

    ~widgetPool() {
        clearPool();
    }

    // 从池中获取一个窗口对象
    T* acquire(QWidget *parent = nullptr)
    {
        QMutexLocker locker(&m_mutex);
        if (!m_pool.isEmpty()) {
            T* widget = m_pool.top();   // 从池中取出第一个对象
            widget->setParent(parent);  // 设置父窗口
            widget->show();
            m_pool.pop();
            m_usedSize++;
            return widget; // 返回对象
        }
        return nullptr; // 如果池为空，返回nullptr
    }

    // 将窗口对象放回池中
    void release(T* widget)
    {
        if (!widget) return;                // 如果传入的widget为空，直接返回
        QMutexLocker locker(&m_mutex);
        if (m_usedSize <= m_poolSize) {     // 检查池的大小是否超过限制
            m_pool.push(widget);            // 将对象放回池中
            widget->hide();
            m_usedSize--;                   // 增加当前大小计数
        } else {
            delete widget;                  // 如果池已满，删除对象
        }
    }   

    // 获取池的当前大小
    int currentSize() const { return m_poolSize - m_usedSize; }

    // 获取池的最大大小
    int poolSize() const { return m_poolSize; }


    // 清空池中的所有窗口对象
    void clearPool() {
        QMutexLocker locker(&m_mutex);
        while (!m_pool.isEmpty())  // 使用条件判断来确保池不为空
        {
            T* widget = m_pool.top(); // 从池中取出一个对象
            m_pool.pop();
            delete widget;            // 删除对象
            --m_poolSize;     // 减少当前大小计数
        }
        // 清空池后，当前可用大小重置为0
        m_poolSize = 0;
    }     

    // 获取池中所有窗口对象的数量
    int getWidgetCount() const {
        QMutexLocker locker(&m_mutex);
        return m_pool.size();
    }   

    // 检查池中是否有可用的窗口对象
    bool isEmpty() const {
        QMutexLocker locker(&m_mutex);
        return m_pool.isEmpty();
    }   

private:
    int m_poolSize;             // 池的最大大小
    int m_usedSize;     // 当前池的可用大小
    QStack<T*> m_pool;          // 池的对象栈
    QMutex m_mutex;             // 池的互斥锁

};



#endif // WIDGETPOOL_H
