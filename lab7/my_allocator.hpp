#ifndef MY_ALLOCATOR_H
#define MY_ALLOCATOR_H

#include <cstdlib>
#include <cstddef>
#include <limits>
#include <new>
#include <type_traits>
#include <utility>

class MemoryPool {
private:
    // 内存块参数
    static const size_t ALIGN = 8;             // 对齐大小
    static const size_t MAX_BYTES = 4096;       // 最大内存块大小
    static const size_t NFREELISTS = MAX_BYTES / ALIGN; // 自由链表数量
    
    // 自由链表节点
    union FreeNode {
        FreeNode* next;  // 指向下一个节点
        char data[1];    // 数据起始位置（用于对齐）
    };
    
    FreeNode* free_lists[NFREELISTS]; // 自由链表数组
    void* chunks = nullptr;           // 大块内存链表头

    // 内存对齐计算（向上取整到ALIGN的倍数）
    static size_t round_up(size_t bytes) {
        return (bytes + ALIGN - 1) & ~(ALIGN - 1);
    }

    // 计算自由链表索引
    static size_t free_list_index(size_t bytes) {
        return (bytes + ALIGN - 1) / ALIGN - 1;
    }

    // 向自由链表添加节点
    void add_to_free_list(size_t index, void* ptr) {
        FreeNode* node = static_cast<FreeNode*>(ptr);
        node->next = free_lists[index];
        free_lists[index] = node;
    }

    // 从自由链表获取节点
    void* get_from_free_list(size_t index) {
        if (free_lists[index]) {
            FreeNode* node = free_lists[index];
            free_lists[index] = node->next;
            return node;
        }
        return nullptr;
    }

    // 重新填充自由链表（分配新的大块内存）
    void* refill(size_t index, size_t block_size) {
        // 根据块大小确定分配数量
        size_t num_blocks = 20; // 默认分配20个块
        if (block_size > 4096) num_blocks = 1;
        else if (block_size > 1024) num_blocks = 10;

        size_t total_bytes = block_size * num_blocks;
        
        // 申请大块内存（额外空间存储链表指针）
        void* chunk = ::operator new(total_bytes + sizeof(void*));
        
        // 将大块内存加入链表（用于析构时统一释放）
        void** p = static_cast<void**>(chunk);
        *p = chunks;
        chunks = chunk;
        
        // 分割大块内存到自由链表
        char* block = static_cast<char*>(chunk) + sizeof(void*);
        for (size_t i = 1; i < num_blocks; ++i) {
            add_to_free_list(index, block + i * block_size);
        }
        
        return block; // 返回第一个块给用户
    }

public:
    MemoryPool() {
        // 初始化自由链表数组
        for (size_t i = 0; i < NFREELISTS; ++i) {
            free_lists[i] = nullptr;
        }
    }

    ~MemoryPool() {
        // 释放所有大块内存
        void* p = chunks;
        while (p) {
            void* next = *(static_cast<void**>(p));
            ::operator delete(p);
            p = next;
        }
    }

    // 获取内存池单例
    static MemoryPool& get_instance() {
        static MemoryPool instance;
        return instance;
    }

    // 分配内存
    void* allocate(size_t n) {
        // 大块内存直接使用全局new
        if (n > MAX_BYTES) {
            return ::operator new(n);
        }
        
        size_t rounded_bytes = round_up(n);
        size_t index = free_list_index(rounded_bytes);
        
        // 尝试从自由链表获取
        if (void* ptr = get_from_free_list(index)) {
            return ptr;
        }
        
        // 自由链表为空，重新填充
        return refill(index, rounded_bytes);
    }

    // 释放内存
    void deallocate(void* ptr, size_t n) {
        // 大块内存直接使用全局delete
        if (n > MAX_BYTES) {
            ::operator delete(ptr);
            return;
        }
        
        // 小块内存回收到自由链表
        size_t rounded_bytes = round_up(n);
        size_t index = free_list_index(rounded_bytes);
        add_to_free_list(index, ptr);
    }
};

// 自定义分配器（符合STL Allocator接口）
template <typename T>
class MyAllocator {
public:
    // 必需的类型定义（STL容器要求）
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    
    // 支持容器移动和比较
    typedef std::true_type propagate_on_container_move_assignment;
    typedef std::true_type is_always_equal;
    
    // 构造函数
    MyAllocator() noexcept = default;
    
    // 模板化拷贝构造函数（支持不同类型的分配器转换）
    template <typename U> 
    MyAllocator(const MyAllocator<U>&) noexcept {}
    
    // 内存分配
    pointer allocate(size_type n) {
        if (n > max_size()) 
            throw std::bad_alloc();
        
        size_type bytes = n * sizeof(T);
        return static_cast<pointer>(MemoryPool::get_instance().allocate(bytes));
    }
    
    // 内存释放
    void deallocate(pointer p, size_type n) noexcept {
        size_type bytes = n * sizeof(T);
        MemoryPool::get_instance().deallocate(p, bytes);
    }
    
    // 对象构造（使用placement new）
    template <typename U, typename... Args>
    void construct(U* p, Args&&... args) {
        ::new ((void*)p) U(std::forward<Args>(args)...);
    }
    
    // 对象析构（显式调用析构函数）
    template <typename U>
    void destroy(U* p) {
        p->~U();
    }
    
    // 地址获取
    pointer address(reference x) const noexcept { return &x; }
    const_pointer address(const_reference x) const noexcept { return &x; }
    
    // 最大分配大小
    size_type max_size() const noexcept {
        return std::numeric_limits<size_type>::max() / sizeof(T);
    }
    
    // 支持rebind（用于容器内部数据结构）
    template <typename U>
    struct rebind {
        typedef MyAllocator<U> other;
    };
};

// 支持分配器比较（所有MyAllocator实例都相等）
template <class T1, class T2>
bool operator==(const MyAllocator<T1>&, const MyAllocator<T2>&) noexcept {
    return true;
}

template <class T1, class T2>
bool operator!=(const MyAllocator<T1>& lhs, const MyAllocator<T2>& rhs) noexcept {
    return !(lhs == rhs);
}

#endif // MY_ALLOCATOR_H