/**
 * @file Vector.cpp
 * @author DM8AT
 * @brief implement the C and C++ vector
 * @version 0.1
 * @date 2025-08-31
 * 
 * @copyright Copyright (c) 2025
 * 
 */

//include the vector
#include "Vector.h"

//memory management stuff
#include <cstring>

#include "../Debugging/Logging/__BG_SimpleDebug.h"

/**
 * @brief a helper function to only re-allocate the data for the vector. THIS FUNCTION IS ONLY FOR THE BACKEND! DON'T USE IT IN FRONTEND STUFF. 
 * 
 * @param vector a pointer to the vector to work on
 * @param byteCapacityNew the new capacity in bytes
 * @param copySizeByte the size in bytes to copy over
 * @param copyOffsetByte the offset of the copy target in bytes
 */
inline static void unsafeVectorResize(s_Vector* vector, uint64_t byteCapacityNew, uint64_t copySizeByte, uint64_t copyOffsetByte)
{
    //allocate the new ram
    uint8_t* new_ptr = new uint8_t[byteCapacityNew];
    //copy over the data
    memmove(new_ptr + copyOffsetByte, vector->ptr, copySizeByte);
    //free the old pointer and replace it with the new one
    delete[] (uint8_t*)vector->ptr;
    vector->ptr = new_ptr;
}

s_Vector::s_Vector(uint64_t _elementSize) noexcept
 : byteCapacity(0), byteSize(0), ptr(nullptr), elementSize(_elementSize)
{
    //allocate the actual data
    ptr = (void*)(new uint8_t[GLGE_C_VECTOR_MIN_SIZE * elementSize]);
    //sanity check
    if (!ptr) {return;}
    //store the new capacity
    byteCapacity = GLGE_C_VECTOR_MIN_SIZE * elementSize;
}

s_Vector::s_Vector(uint64_t _elementSize, uint64_t _elements) noexcept
 : byteCapacity(0), byteSize(0), ptr(nullptr), elementSize(_elementSize)
{
    //allocate the data array
    ptr = (void*)(new uint8_t[_elements * elementSize]);

    //if the pointer is 0, stop
    if (!ptr)  {return;}

    //store the new capacity
    byteCapacity = _elements * elementSize;

    //clear the data
    memset(ptr, 0, byteCapacity);
}


s_Vector::s_Vector(uint64_t _elementSize, uint64_t _elements, void* _data) noexcept
 : byteCapacity(0), byteSize(0), ptr(nullptr), elementSize(_elementSize)
{
    //allocate the data array
    ptr = (void*)(new uint8_t[_elements * elementSize]);

    //if the pointer is 0, stop
    if (!ptr)  {return;}

    //copy the data over
    memcpy(ptr, _data, _elements * elementSize);

    //store the size and capacity
    byteSize = _elements * elementSize;
    byteCapacity = byteSize;
}

void s_Vector::resize(uint64_t elements) noexcept
{
    //if the size is the same, early out
    if (elements == byteSize/elementSize) {return;}

    //store the new size in bytes
    uint64_t byteCapacityNew = elements * elementSize;
    uint64_t byteSizeNew = (byteSize > byteCapacityNew) ? byteCapacityNew : byteSize;
    //call the unsafe re-alloc function
    unsafeVectorResize(this, byteCapacityNew, byteSizeNew, 0);

    //store the new size and capacity
    byteCapacity = byteCapacityNew;
    //this is the difference between resize and reserve: the actual vector size is the capacity
    byteSize = byteCapacity;
}

void s_Vector::reserve(uint64_t elements) noexcept
{
    //if the size is the same, early out
    if (elements == byteSize/elementSize) {return;}

    //store the new size in bytes
    uint64_t byteCapacityNew = elements * elementSize;
    uint64_t byteSizeNew = (byteSize > byteCapacityNew) ? byteCapacityNew : byteSize;
    //call the unsafe re-allocate function
    unsafeVectorResize(this, byteCapacityNew, byteSizeNew, 0);

    //store the new size and capacity
    byteCapacity = byteCapacityNew;
    byteSize = byteSizeNew;
}

void s_Vector::push_back(void* value) noexcept
{
    //check if another element fits into the vector
    if (byteCapacity < (elementSize + byteSize))
    {
        //another element is needed. Resize to fit it. 
        uint64_t newSize = (byteCapacity == 0) ? elementSize : byteCapacity*2;
        //newSize = ((newSize - byteCapacity) > (elementSize * 64)) ? byteCapacity + (elementSize * 16) : newSize;
        reserve(newSize/elementSize);
    }
    //now, the element can be safely copied to the back and increase the used size
    memcpy(((uint8_t*)ptr) + byteSize, value, elementSize);
    byteSize += elementSize;
}

void s_Vector::push_front(void* value) noexcept
{
    //check if another element fits into the vector
    if (byteCapacity < (elementSize + byteSize))
    {
        //another element is needed. Resize to fit it. 
        uint64_t newSize = byteCapacity * 2;
        newSize = ((newSize - byteCapacity) > (elementSize * 16)) ? byteCapacity + (elementSize * 16) : newSize;
        reserve(newSize/elementSize);
    }
    //shift the stored data forward
    memmove(((uint8_t*)ptr) + elementSize, ptr, byteSize);
    //now, the element can be safely copied to the front and increase the used size
    memcpy(((uint8_t*)ptr), value, elementSize);
    byteSize += elementSize;
}

void s_Vector::pop_back() noexcept
{
    //if the byte size is less than the element size, stop
    if (byteSize < elementSize) {return;}
    //simply move back the size
    byteSize -= elementSize;
}

void s_Vector::pop_front() noexcept
{
    //check if there is enough space. If not, stop. 
    if (byteSize < elementSize) {return;}

    //check if data remains in the vector or not
    if (byteSize == elementSize)
    {
        //just set the size to 0
        byteSize = 0;
    }
    else
    {
        //decrease the size
        byteSize -= elementSize;
        //shift the stored data forward
        memmove(ptr, ((uint8_t*)ptr) + elementSize, byteSize);
    }
}

void s_Vector::clear() noexcept
{
    //set the size and capacity to 0
    byteSize = 0;
    byteCapacity = 0;
    //delete the whole data
    delete[] (uint8_t*)ptr;
    ptr = NULL;
}




extern "C" {

Vector* vector_Create(uint64_t _elementSize)
{
    //return a new vector
    return new Vector(_elementSize);
}

Vector* vector_CreatePreallocated(uint64_t _elementSize, uint64_t _elements)
{
    //return a new vector
    return new Vector(_elementSize, _elements);
}

Vector* vector_CreateFrom(uint64_t _elementSize, uint64_t elements, void* data)
{
    //return a new vector
    return new Vector(_elementSize, elements, data);
}

void vector_Destroy(Vector* vec)
{
    //destroy the vector
    delete vec;
}

void* vector_Get(uint64_t i, const Vector* vec) {return (*vec)[i];}

void* vector_Data(const Vector* vec) {return vec->data();}

void vector_Resize(uint64_t elements, Vector* vec) {vec->resize(elements);}

void vector_Reserve(uint64_t elements, Vector* vec) {vec->reserve(elements);}

void vector_Push_back(void* value, Vector* vec) {vec->push_back(value);}

void vector_Push_front(void* value, Vector* vec) {vec->push_front(value);}

void vector_Pop_back(Vector* vec) {vec->pop_back();}

void vector_Pop_front(Vector* vec) {vec->pop_front();}

void vector_Clear(Vector* vec) {vec->clear();}

}