/**
 * @file Thread.h
 * @author DM8AT
 * @brief define an interface between a thread and C
 * @version 0.1
 * @date 2025-09-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */

//header guard
#ifndef _GLGE_C_THREAD_
#define _GLGE_C_THREAD_

//check for C++ to include threads
#if __cplusplus
#include <thread>
#endif

/**
 * @brief store a wrapper around a C++ thread object for C
 */
typedef struct s_Thread {

    //check for C++ to define the thread internal's 
    #if __cplusplus

    /**
     * @brief store the actual thread
     */
    std::thread thread;

    /**
     * @brief Construct a new Thread
     * 
     * @param func a function pointer to the function to execute in the other thread
     * @param data a pointer to the data to pass to the function
     */
    s_Thread(void (*func)(void*), void* data) : thread(std::thread(func, data)) {}

    /**
     * @brief Destroy the Thread
     * 
     * If the thread isn't joined, this joins the thread
     */
    ~s_Thread() {if (thread.joinable()) {thread.join();}}

    /**
     * @brief join the thread back to the calling thread
     */
    inline void join() {thread.join();}

    /**
     * @brief detach the thread from the calling thread
     */
    inline void detach() {thread.detach();}

    /**
     * @brief get if the thread can be joined
     * 
     * @return true : the thread can be joined | 
     * @return false : the thread cannot be joined
     */
    inline bool joinable() {return thread.joinable();}

    /**
     * @brief swap the threads that are being executed
     * 
     * @param other a pointer to the other thread to swap with
     */
    inline void swap(s_Thread* other) {thread.swap(other->thread);}

    /**
     * @brief get an ESTIMATION on the amount of present hardware threads
     * 
     * @return unsigned int the amount of possible hardware threads
     */
    static inline unsigned int hardware_concurrency() {return std::thread::hardware_concurrency();}

    #endif

} Thread;

//start an extern section for C
//just to be sure
#if __cplusplus
extern "C" {
#endif

/**
 * @brief create a thread that executes the given function with the given parameters
 * 
 * @param func the function to execute on the different thread
 * @param data the data given to the function
 * @return Thread* a pointer to the thread that stores the function
 */
Thread* thread_Create(void (*func)(void*), void* data);

/**
 * @brief destroy a thread
 * 
 * If the thread isn't joined jet, join it
 * 
 * @param thread a pointer to the thread to destroy
 */
void thread_Destroy(Thread* thread);

/**
 * @brief join a thread back to the calling thread
 * 
 * @param thread the thread to join back
 */
void thread_Join(Thread* thread);

/**
 * @brief detach a thread from any other thread
 * 
 * @param thread the thread to detach
 */
void thread_Detach(Thread* thread);

/**
 * @brief check if a thread can be joined
 * 
 * @param thread a pointer to the thread to check
 * @return true : the thread can be joined
 * @return false : the thread cannot be joined
 */
bool thread_joinable(Thread* thread);

/**
 * @brief swap two threads
 * 
 * @param thread the first thread to swap
 * @param other the thread to swap with
 */
void thread_Swap(Thread* thread, Thread* other);

/**
 * @brief get an ESTIMATION on the amount of CPU threads
 * 
 * @return unsigned int the amount of possible hardware threads
 */
unsigned int thread_Hardware_concurrency();

//the the extern section in C++
#if __cplusplus
}
#endif

#endif