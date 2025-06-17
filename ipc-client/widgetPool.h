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
    explicit widgetPool(int poolSize, QWidget *parent = nullptr)
        : m_poolSize(poolSize), m_currentSize(0) 
    {
        m_pool.reserve(poolSize);       // 预留池的空间
        // 初始化池中的对象
        for (int i = 0; i < m_poolSize; ++i) {
            T* widget = new T(parent);  // 创建新的窗口对象
            m_pool.append(widget);      // 将对象添加到池中
        }
        m_currentSize = m_poolSize; // 设置当前大小为池的大小
    }  

    // 销毁池中的所有窗口
    ~widgetPool()
    {
        clearPool(); // 清理池中的所有对象
    }

    // 从池中获取一个窗口对象
    T* getWidget()
    {
        QMutexLocker locker(&m_mutex);
        if (!m_pool.isEmpty()) {
            T* widget = m_pool.takeFirst(); // 从池中取出第一个对象
            --m_currentSize;
            return widget; // 返回对象
        }
        return nullptr; // 如果池为空，返回nullptr
    }

    // 将窗口对象放回池中
    void releaseWidget(T* widget)
    {
        if (!widget) return; // 如果传入的widget为空，直接返回
        QMutexLocker locker(&m_mutex);
        if (m_currentSize < m_poolSize) { // 检查池的大小是否超过限制
            m_pool.append(widget); // 将对象放回池中
            ++m_currentSize; // 增加当前大小计数
        } else {
            delete widget; // 如果池已满，删除对象
        }
    }   

    // 获取池的当前大小
    int currentSize() const { return m_currentSize; }

    // 获取池的最大大小
    int poolSize() const { return m_poolSize; }

    
    // 设置池的最大大小
    void setPoolSize(int size) {
        QMutexLocker locker(&m_mutex);
        m_poolSize = size;
        // 如果当前大小超过新大小，则清理多余的对象
        while (m_currentSize > m_poolSize && !m_pool.isEmpty()) {
            delete m_pool.takeLast();
            --m_currentSize;
        }
    }   

    // 清空池中的所有窗口对象
    void clearPool() {
        QMutexLocker locker(&m_mutex);
        qDeleteAll(m_pool);
        m_pool.clear();
        m_currentSize = 0;
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
    bool hasAvailableWidget() const {
        QMutexLocker locker(&m_mutex);
        return !m_pool.isEmpty();
    }

    // 获取池中第一个可用的窗口对象
    T* getFirstAvailableWidget() {
        QMutexLocker locker(&m_mutex);
        if (!m_pool.isEmpty()) {
            return m_pool.first();
        }
        return nullptr;
    }

    // 获取池中最后一个可用的窗口对象
    T* getLastAvailableWidget() {
        QMutexLocker locker(&m_mutex);
        if (!m_pool.isEmpty()) {        
            return m_pool.last();
        }
        return nullptr;
    }
 
private:
    // 对象池的单例模式
    // 禁止复制构造函数和赋值操作符
    widgetPool(const widgetPool&) = delete;
    widgetPool& operator=(const widgetPool&) = delete;


    int m_poolSize;     // 池的最大大小
    int m_currentSize;  // 池的已用空间
    QList<T*> m_pool;   // 池的对象链表
    QMutex m_mutex;     // 池的互斥锁

};

#endif // WIDGETPOOL_H
