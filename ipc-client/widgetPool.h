#ifndef WIDGETPOOL_H
#define WIDGETPOOL_H

#include <QWidget>
#include <QMutex>
#include <QList>
#include <QMutexLocker>

// 创建多路摄像头窗口对象池
template <typename T>
class widgetPool
{
public:
    // 构造函数
    widgetPool(int poolSize = 16, QWidget *parent = nullptr)
        : m_poolSize(poolSize), m_curAvailableSize(poolSize)
    {
        m_pool.reserve(poolSize); // 预留池的空间
        // 初始化池中的对象
        for (int i = 0; i < m_poolSize; ++i) {
            T* widget = new T(parent); // 创建新的窗口对象
            m_pool.push(widget);      // 将对象添加到池中
        }
        m_curAvailableSize = m_poolSize; // 设置当前大小为池的大小
    }

    ~widgetPool() {
        clearPool();
    }

    // 从池中获取一个窗口对象
    T* getWidget()
    {
        QMutexLocker locker(&m_mutex);
        if (!m_pool.isEmpty()) {
            T* widget = m_pool.top(); // 从池中取出第一个对象
             m_pool.pop();
            --m_curAvailableSize;
            return widget; // 返回对象
        }
        return nullptr; // 如果池为空，返回nullptr
    }

    // 将窗口对象放回池中
    void releaseWidget(T* widget)
    {
        if (!widget) return;                // 如果传入的widget为空，直接返回
        QMutexLocker locker(&m_mutex);
        if (m_curAvailableSize < m_poolSize) {   // 检查池的大小是否超过限制
            m_pool.push(widget);          // 将对象放回池中
            ++m_curAvailableSize;                // 增加当前大小计数
        } else {
            delete widget; // 如果池已满，删除对象
        }
    }   

    // 获取池的当前大小
    int currentSize() const { return m_curAvailableSize; }

    // 获取池的最大大小
    int poolSize() const { return m_poolSize; }

    
    // 设置池的最大大小
    void setPoolSize(int size) 
    {
        QMutexLocker locker(&m_mutex);
        m_poolSize = size;
        // 如果当前大小小于新大小，则创建新的对象填充池
        while (m_curAvailableSize < m_poolSize) {
            T* widget = new T(); // 创建新的窗口对象
            m_pool.push(widget); // 将对象添加到池中
            ++m_curAvailableSize; // 增加当前大小计数
        }
        // 确保池的大小不超过新大小
        m_pool.resize(m_poolSize); // 调整池的大小到新大小

        // 这将确保池中最多有m_poolSize个对象
        // 如果池的大小超过新大小，则删除多余的对象
        while (m_curAvailableSize > m_poolSize && !m_pool.isEmpty()) {
            delete m_pool.pop(); // 删除池中最后一个对象
            --m_curAvailableSize; // 减少当前大小计数
        }
        // 以上操作确保池的大小始终在限制范围内
    }

    // 清空池中的所有窗口对象
    void clearPool() {
        QMutexLocker locker(&m_mutex);
        while (!m_pool.isEmpty())  // 使用条件判断来确保池不为空
        {
            T* widget = m_pool.pop(); // 从池中取出一个对象
            delete widget;            // 删除对象
            --m_curAvailableSize;     // 减少当前大小计数
        }
        // 清空池后，当前可用大小重置为0
        m_curAvailableSize = 0;
    }   

    // 获取池中所有窗口对象的列表
    QList<T*> getAllWidgets() const {
        QMutexLocker locker(&m_mutex);
        return m_pool;
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


    // 获取池中第一个可用的窗口对象
    T* getFirstAvailableWidget() {
        QMutexLocker locker(&m_mutex);
        if (!m_pool.isEmpty()) 
        {
            T* widget = m_pool.takeFirst(); // 使用takeFirst()替代first(),自动移除并返回第一个元素
            m_curAvailableSize--;  // 减少当前大小
            return widget;
        }
        return nullptr;
    }

private:

    static QMutex instanceMutex;
    int m_poolSize;     // 池的最大大小
    int m_curAvailableSize;  // 当前池的可用大小
    QStack<T*> m_pool;  // 池的对象栈
    QMutex m_mutex;     // 池的互斥锁

};

template <typename T>
QMutex widgetPool<T>::instanceMutex;

#endif // WIDGETPOOL_H
