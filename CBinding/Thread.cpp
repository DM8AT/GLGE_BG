/**
 * @file Thread.cpp
 * @author DM8AT
 * @brief implement the thread functionality for the C overload
 * @version 0.1
 * @date 2025-09-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */

//include the thread header
#include "Thread.h"

Thread* thread_Create(void (*func)(void*), void* data) {return new Thread(func, data);}

void thread_Destroy(Thread* thread) {delete thread;}

void thread_Join(Thread* thread) {thread->join();}

void thread_Detach(Thread* thread) {thread->detach();}

bool thread_Joinable(Thread* thread) {return thread->joinable();}

void thread_Swap(Thread* thread, Thread* other) {thread->swap(other);}

unsigned int thread_Hardware_concurrency() {return Thread::hardware_concurrency();}
