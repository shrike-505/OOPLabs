#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstring>
#include <stdexcept>
template <typename T>
class Vector {
public:
    /**
     * Default constructor that initializes an empty Vector with no elements and zero capacity.
     */
    Vector()
    {
        m_pElements = nullptr;
        m_nSize = 0;
        m_nCapacity = 0;
    }
    /**
     * Copy constructor that initializes a Vector from another Vector.
     * @param r The Vector to be copied from.
     */
    Vector(const Vector &r): m_nSize(r.m_nSize), m_nCapacity(r.m_nCapacity)
    {
        if(m_nCapacity > 0){
            m_pElements = new T[m_nCapacity];
            for (int i = 0; i < m_nSize; ++i) {
                m_pElements[i] = r.m_pElements[i];
            }
        } else {
            this->m_pElements = nullptr;
        }
    }
    /**
     * Constructor that initializes a Vector with a specified size.
     * Allocates memory for the elements if size is greater than zero.
     * @param size The initial size and capacity of the Vector.
     */

    Vector(int size) : m_nSize(size), m_nCapacity(size){
        if (size > 0){
            m_pElements = new T[size];
        }
    }

    /**
     * Destructor that releases the memory allocated by the Vector.
     */
    ~Vector(){
        delete [] m_pElements;
    }

    T& operator[](int index){
        return m_pElements[index];
    }

    T& at(int index){
        if (index < 0 || index >= m_nSize){
            throw std::out_of_range("Vector::at");
        }
        return m_pElements[index];
    }

    /**
     * Returns the number of elements in the Vector.
     * @return The number of elements in the Vector.
     */
    int size() const{
        return m_nSize;
    }
    /**
     * Adds an element to the end of the Vector.
     * If the current capacity is reached, the storage is expanded.
     * @param x The element to be added to the Vector.
     */

    void push_back(const T& x){
        if(m_nCapacity == m_nSize){
            inflate();
        }
        m_pElements[m_nSize++] = x;
    }
    void clear(){
        m_nSize = 0;
    }
    bool empty() const{
        return m_nSize == 0;
    }
private:
    /**
     * Increases the capacity of the Vector.
     * If the current capacity is zero, it sets the capacity to one.
     * Otherwise, it doubles the current capacity.
     * Allocates a new storage space with the updated capacity,
     * copies the existing elements to the new storage,
     * deletes the old storage, and updates the capacity.
     */
    void inflate(){
        int newCapacity = (m_nCapacity == 0) ? 1 : 2 * m_nCapacity;
        T *pNewElements = new T[newCapacity];
        for (int i = 0; i < m_nSize; ++i) {
            pNewElements[i] = m_pElements[i]; // 调用拷贝赋值
        }
        delete [] m_pElements;
        m_pElements = pNewElements;
        m_nCapacity = newCapacity;
    }
    T *m_pElements;                // pointer to the dynamically allocated storage
    int m_nSize;                   // the number of elements in the container
    int m_nCapacity;               // the total number of elements that can be held in the
                                    // allocated storage
};

#endif