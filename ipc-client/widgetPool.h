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
    // 获取单例实例
    static widgetPool<T>* getInstance(int poolSize, QWidget *parent = nullptr) {
        return instance;
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
        if (!widget) return;                // 如果传入的widget为空，直接返回
        QMutexLocker locker(&m_mutex);
        if (m_currentSize < m_poolSize) {   // 检查池的大小是否超过限制
            m_pool.append(widget);          // 将对象放回池中
            ++m_currentSize;                // 增加当前大小计数
        } else {
            delete widget; // 如果池已满，删除对象
        }
    }   

    // 获取池的当前大小
    int currentSize() const { return m_currentSize; }

    // 获取池的最大大小
    int poolSize() const { return m_poolSize; }

    
    // 设置池的最大大小
    void setPoolSize(int size) 
    {
        QMutexLocker locker(&m_mutex);
        m_poolSize = size;
        // 如果当前大小小于新大小，则创建新的对象填充池
        while (m_currentSize < m_poolSize) {
            T* widget = new T(); // 创建新的窗口对象
            m_pool.append(widget); // 将对象添加到池中
            ++m_currentSize; // 增加当前大小计数
        }
        // 确保池的大小不超过新大小
        m_pool.resize(m_poolSize); // 调整池的大小到新大小

        // 这将确保池中最多有m_poolSize个对象
        // 如果池的大小超过新大小，则删除多余的对象
        while (m_currentSize > m_poolSize && !m_pool.isEmpty()) {
            delete m_pool.takeLast(); // 删除池中最后一个对象
            --m_currentSize; // 减少当前大小计数
        }
        // 以上操作确保池的大小始终在限制范围内
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
            m_currentSize--;  // 减少当前大小
            return widget;
        }
        return nullptr;
    }

private:
    // 对象池的单例模式
    // 禁止复制构造函数和赋值操作符
    widgetPool(const widgetPool&) = delete;
    widgetPool& operator=(const widgetPool&) = delete;

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

    ~widgetPool() {
        clearPool();
    }

    static widgetPool<T>* instance;
    static QMutex instanceMutex;

    int m_poolSize;     // 池的最大大小
    int m_currentSize;  // 池的已用空间
    QList<T*> m_pool;   // 池的对象链表
    QMutex m_mutex;     // 池的互斥锁

};

// 静态成员初始化
template <typename T>
widgetPool<T>* widgetPool<T>::instance = new widgetPool<T>(16); // 默认池大小为16

template <typename T>
QMutex widgetPool<T>::instanceMutex;

#endif // WIDGETPOOL_H
