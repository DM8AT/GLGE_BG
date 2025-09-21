/**
 * @file Vector.h
 * @author DM8AT
 * @brief a binding for a C++ vector and a C vector
 * @version 0.1
 * @date 2025-08-31
 * 
 * @copyright Copyright (c) 2025
 * 
 */

//header guard
#ifndef _GLGE_C_VECTOR_
#define _GLGE_C_VECTOR_

/**
 * @brief store the minimum sized assumed of a vector
 */
#define GLGE_C_VECTOR_MIN_SIZE 4

//specific sized integers are always required
#include <stdint.h>

/**
 * @brief define a data type as a vector
 */
typedef struct s_Vector
{
    /**
     * @brief the capacity of the vector in bytes
     */
    uint64_t byteCapacity;
    /**
     * @brief store the size of the vector in bytes
     */
    uint64_t byteSize;
    /**
     * @brief store the raw vector data
     */
    void* ptr;
    /**
     * @brief store the size in bytes of all elements
     */
    uint64_t elementSize;

    //check for C++ to create a direct API
    #ifdef __cplusplus

    /**
     * @brief Construct a new Vector
     * 
     * @param _elementSize the size of each vector element
     */
    s_Vector(uint64_t _elementSize) noexcept;

    /**
     * @brief Construct a new Vector
     * 
     * @param _elementSize the size for each vector element
     * @param _elements the amount of elements to pre-allocate for
     */
    s_Vector(uint64_t _elementSize, uint64_t _elements) noexcept;

    /**
     * @brief Construct a new Vector
     * 
     * @param _elementSize the size of each vector element
     * @param elements the amount of elements in the input data
     * @param data the data to initialize the data vector with
     */
    s_Vector(uint64_t _elementSize, uint64_t elements, void* data) noexcept;

    /**
     * @brief Destroy the Vector
     */
    ~s_Vector() {clear();}

    /**
     * @brief get a specific element of the vector
     * 
     * @param i the index of the vector element
     * @return void* a pointer to the requested element
     */
    inline void* operator[](uint64_t i) const noexcept {return (void*)(((uint8_t*)ptr) + (i * elementSize));}

    /**
     * @brief get the raw vector data
     * 
     * @return void* the raw stored data
     */
    constexpr inline void* data() const noexcept {return ptr;}

    /**
     * @brief change the size of the vector to a specific amount of elements
     * 
     * @param elements the amount of elements the vector should be able to store
     */
    void resize(uint64_t elements) noexcept;

    /**
     * @brief change the capacity of the vector to a specific amount of elements
     * 
     * @param elements the amount of elements that should fit into the capacity
     */
    inline void reserve(uint64_t elements) noexcept;

    /**
     * @brief add a new element to the back of the vector
     * 
     * @param value a pointer to the element to add at the back
     */
    void push_back(void* value) noexcept;

    /**
     * @brief add a new element to the front of the vector
     * 
     * @param value the value to add to the front of the vector
     */
    void push_front(void* value) noexcept;

    /**
     * @brief remove an element from the back of the vector
     */
    void pop_back() noexcept;

    /**
     * @brief remove an element from the front of the vector
     */
    void pop_front() noexcept;

    /**
     * @brief empty the vector's contents
     */
    void clear() noexcept;

    /**
     * @brief erase a specific element from the vector
     * 
     * @param index the index of the element to remove
     */
    void erase(uint64_t index);

    /**
     * @brief erase a specific section from the vector
     * 
     * @param index the index of the element to start erasing at
     * @param n the amount of elements to erase
     */
    void erase(uint64_t index, uint64_t n);

    #endif

} Vector;

//start an extern section for C
//just to be sure
#if __cplusplus
extern "C" {
#endif

/**
 * @brief Construct a new Vector
 * 
 * @param _elementSize the size of each vector element
 */
Vector* vector_Create(uint64_t _elementSize);

/**
 * @brief Construct a new Vector
 * 
 * @param _elementSize the size of each vector element
 * @param _elements the amount of elements to pre-allocate for
 */
Vector* vector_CreatePreallocated(uint64_t _elementSize, uint64_t _elements);

/**
 * @brief Construct a new Vector
 * 
 * @param _elementSize the size of each vector element
 * @param elements the amount of elements in the input data
 * @param data the data to initialize the data vector with
 */
Vector* vector_CreateFrom(uint64_t _elementSize, uint64_t elements, void* data);

/**
 * @brief Destroy the Vector
 * 
 * @param vec a pointer to the vector to perform the operation on
 */
void vector_Destroy(Vector* vec);

/**
 * @brief get a specific element of the vector
 * 
 * @param i the index of the vector element
 * @param vec a pointer to the vector to perform the operation on
 * @return void* a pointer to the requested element
 */
void* vector_Get(uint64_t i, const Vector* vec);

/**
 * @brief get the raw vector data
 * 
 * @param vec a pointer to the vector to perform the operation on
 * @return void* the raw stored data
 */
void* vector_Data(const Vector* vec);

/**
 * @brief change the size of the vector to a specific amount of elements
 * 
 * @param elements the amount of elements the vector should be able to store
 * @param vec a pointer to the vector to perform the operation on
 */
void vector_Resize(uint64_t elements, Vector* vec);

/**
 * @brief change the capacity of the vector to a specific amount of elements
 * 
 * @param elements the amount of elements that should fit into the capacity
 * @param vec a pointer to the vector to perform the operation on
 */
void vector_Reserve(uint64_t elements, Vector* vec);

/**
 * @brief add a new element to the back of the vector
 * 
 * @param value a pointer to the element to add at the back
 * @param vec a pointer to the vector to perform the operation on
 */
void vector_Push_back(void* value, Vector* vec);

/**
 * @brief add a new element to the front of the vector
 * 
 * @param value the value to add to the front of the vector
 * @param vec a pointer to the vector to perform the operation on
 */
void vector_Push_front(void* value, Vector* vec);

/**
 * @brief remove an element from the back of the vector
 * @param vec a pointer to the vector to perform the operation on
 */
void vector_Pop_back(Vector* vec);

/**
 * @brief remove an element from the front of the vector
 * @param vec a pointer to the vector to perform the operation on
 */
void vector_Pop_front(Vector* vec);

/**
 * @brief empty the vector's contents
 * @param vec a pointer to the vector to perform the operation on
 */
void vector_Clear(Vector* vec);

/**
 * @brief erase a single element from the vector
 * 
 * @param index the index of the element to erase
 * @param vec a pointer to the vector to erase the element from
 */
void vector_Erase(uint64_t index, Vector* vec);

/**
 * @brief erase a region of elements from the vector
 * 
 * @param index the index of the start of the region to erase
 * @param n the amount of elements to erase
 * @param vec a pointer to the vector to erase the elements from
 */
void vector_EraseSome(uint64_t index, uint64_t n, Vector* vec);

//the the extern section in C++
#if __cplusplus
}
#endif

#endif