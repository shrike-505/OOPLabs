#include "my_allocator.hpp"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <chrono>

#define INT 1
#define CLASS 4

// 根据编译时定义选择分配器
#ifdef USE_STD_ALLOCATOR
    #define MyAllocatorType std::allocator
#else
    #define MyAllocatorType MyAllocator
#endif

// 时间测量辅助宏
#define START_TIMER(name) auto name##_start = std::chrono::high_resolution_clock::now();
#define STOP_TIMER(name) auto name##_end = std::chrono::high_resolution_clock::now(); \
    auto name##_duration = std::chrono::duration_cast<std::chrono::microseconds>(name##_end - name##_start); \
    std::cout << #name << " time: " << name##_duration.count() << " μs" << std::endl;

class vecWrapper {
public:
    vecWrapper() : m_pVec(nullptr), m_type(INT) {}
    virtual ~vecWrapper() = default;
    
public:
    void setPointer(int type, void *pVec) { 
        m_type = type; 
        m_pVec = pVec; 
    }
    
    virtual void visit(int index) = 0;
    virtual int size() = 0;
    virtual void resize(int size) = 0;
    virtual bool checkElement(int index, void *value) = 0;
    virtual void setElement(int index, void *value) = 0;
    
protected: 
    int m_type;
    void *m_pVec;
};

template<class T>
class vecWrapperT : public vecWrapper {
public:
    vecWrapperT(int type, std::vector<T, MyAllocatorType<T>> *pVec) {
        m_type = type;
        m_pVec = pVec;
    }
    
    virtual ~vecWrapperT() {
        if (m_pVec) {
            delete static_cast<std::vector<T, MyAllocatorType<T>>*>(m_pVec);
        }
    }
    
public:
    virtual void visit(int index) override {
        auto* vec = static_cast<std::vector<T, MyAllocatorType<T>>*>(m_pVec);
        T temp = (*vec)[index];
        (void)temp; // 避免未使用变量警告
    }
    
    virtual int size() override {
        auto* vec = static_cast<std::vector<T, MyAllocatorType<T>>*>(m_pVec);
        return vec->size();
    }
    
    virtual void resize(int size) override {
        auto* vec = static_cast<std::vector<T, MyAllocatorType<T>>*>(m_pVec);
        vec->resize(size);
    }
    
    virtual bool checkElement(int index, void *pValue) override {
        auto* vec = static_cast<std::vector<T, MyAllocatorType<T>>*>(m_pVec);
        T temp = (*vec)[index];
        return temp == (*static_cast<T*>(pValue));
    }

    virtual void setElement(int index, void *value) override {
        auto* vec = static_cast<std::vector<T, MyAllocatorType<T>>*>(m_pVec);
        (*vec)[index] = *static_cast<T*>(value);
    }
};

class myObject {
public:
    myObject() : m_X(0), m_Y(0) {}
    myObject(int t1, int t2) : m_X(t1), m_Y(t2) {}
    myObject(const myObject &rhs) = default;
    
    bool operator == (const myObject &rhs) const {
        return (rhs.m_X == m_X) && (rhs.m_Y == m_Y);
    }
    
protected:
    int m_X;
    int m_Y;
};

const int TESTSIZE = 10000;

int main() {
    #ifdef USE_STD_ALLOCATOR
        std::cout << "Using std::allocator" << std::endl;
    #else
        std::cout << "Using custom MyAllocator" << std::endl;
    #endif
    
    START_TIMER(total)
    
    std::cout << "Creating " << TESTSIZE << " vectors..." << std::endl;
    
    // 分配包装器数组
    vecWrapper **testVec = new vecWrapper*[TESTSIZE]();

    // 1. 创建整数向量
    START_TIMER(create_int_vectors)
    for (int i = 0; i < TESTSIZE - 4; i++) {
        int tSize = rand() % 100 + 1;
        testVec[i] = new vecWrapperT<int>(
            INT, 
            new std::vector<int, MyAllocatorType<int>>(tSize)
        );
    }
    STOP_TIMER(create_int_vectors)

    // 2. 创建对象向量
    START_TIMER(create_object_vectors)
    for (int i = 0; i < 4; i++) {
        int tSize = rand() % 10000 + 1;
        testVec[TESTSIZE - 4 + i] = new vecWrapperT<myObject>(
            CLASS, 
            new std::vector<myObject, MyAllocatorType<myObject>>(tSize)
        );
    }
    STOP_TIMER(create_object_vectors)

    // 3. 调整大小测试
    std::cout << "Resizing 100 random vectors..." << std::endl;
    START_TIMER(resize_vectors)
    for (int i = 0; i < 100; i++) {
        int tIndex = rand() % TESTSIZE;
        int tSize = rand() % 1000 + 1;
        testVec[tIndex]->resize(tSize);
    }
    STOP_TIMER(resize_vectors)

    // 4. 赋值测试 - 整数向量
    std::cout << "Testing integer vector assignment..." << std::endl;
    START_TIMER(int_assignment)
    int tIndex = rand() % (TESTSIZE - 4);
    int tIntValue = 10;
    int elementIndex = testVec[tIndex]->size() / 2;
    if (elementIndex >= 0) {
        testVec[tIndex]->setElement(elementIndex, &tIntValue);
        if (!testVec[tIndex]->checkElement(elementIndex, &tIntValue)) {
            std::cout << "incorrect assignment in vector " << tIndex << std::endl;
        }
    }
    STOP_TIMER(int_assignment)

    // 5. 赋值测试 - 对象向量
    std::cout << "Testing object vector assignment..." << std::endl;
    START_TIMER(object_assignment)
    tIndex = TESTSIZE - 4 + 3;
    elementIndex = testVec[tIndex]->size() / 2;
    if (elementIndex >= 0) {
        myObject tObj(11, 15);
        testVec[tIndex]->setElement(elementIndex, &tObj);
        
        if (!testVec[tIndex]->checkElement(elementIndex, &tObj)) {
            std::cout << "incorrect assignment in vector " << tIndex << std::endl;
        }
    }
    STOP_TIMER(object_assignment)

    // 6. 清理测试
    std::cout << "Cleaning up resources..." << std::endl;
    START_TIMER(cleanup)
    for (int i = 0; i < TESTSIZE; i++) {
        delete testVec[i];
    }
    delete [] testVec;
    STOP_TIMER(cleanup)

    // 总计时结束
    STOP_TIMER(total)
    std::cout << "All tests completed successfully!" << std::endl;
    
    return 0;
}