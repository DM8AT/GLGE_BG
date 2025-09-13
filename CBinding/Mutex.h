/**
 * @file Mutex.h
 * @author DM8AT
 * @brief a C binding for a C++ mutex
 * @version 0.1
 * @date 2025-08-31
 * 
 * @copyright Copyright (c) 2025
 * 
 */

//header guard
#ifndef _GLGE_C_MUTEX_
#define _GLGE_C_MUTEX_

//include the mutex from the default library for C++
#if __cplusplus
#include <mutex>
#endif
//booleans are required
#include <stdbool.h>

/**
 * @brief store a mutex. A mutex is a structure used for thread synchronisation. 
 */
typedef struct s_Mutex {

    //if this is C++, add a mutex in here
    #if __cplusplus
    std::mutex mutex;

    //add the interface for the mutex

    /**
     * @brief Construct a new Mutex
     */
    inline s_Mutex() = default;

    /**
     * @brief Destroy the Mutex
     */
    ~s_Mutex() {}

    /**
     * @brief lock the mutex
     */
    inline void lock()  {mutex.lock();}

    /**
     * @brief unlock the mutex
     */
    inline void unlock() {mutex.unlock();}

    /**
     * @brief try to lock the mutex
     * 
     * @return true : the mutex was locked
     * @return false : failed to lock the mutex -> it is locked
     */
    inline bool try_lock() {return mutex.try_lock();}

    #else

    //for windows, add a single byte here to make the struct contain something
    uint8_t byte;

    #endif

    //for C, this is an opaque structure

} Mutex;

//start an extern section for C
//just to be sure
#if __cplusplus
extern "C" {
#endif

/**
 * @brief create a new mutex
 * 
 * @return Mutex* a pointer to the new mutex
 */
Mutex* mutex_Create();

/**
 * @brief destroy a mutex
 * 
 * @param mut a pointer to the mutex to perform the operation on
 */
void mutex_Destroy(Mutex* mut);

/**
 * @brief lock a mutex or wait till it is possible
 * 
 * @param mut a pointer to the mutex to perform the operation on
 */
void mutex_Lock(Mutex* mut);

/**
 * @brief unlock a mutex. Only works if it is locked
 * 
 * @param mut a pointer to the mutex to perform the operation on
 */
void mutex_Unlock(Mutex* mut);

/**
 * @brief try to lock a mutex
 * 
 * @param mut a pointer to the mutex to perform the operation on
 * @return true : the mutex was locked
 * @return false : failed to lock the mutex -> it is locked
 */
bool mutex_Try_lock(Mutex* mut);

//the the extern section in C++
#if __cplusplus
}
#endif

#endif