/**
 * @file Mutex.cpp
 * @author DM8AT
 * @brief implement the C binding for the mutex structure
 * @version 0.1
 * @date 2025-08-31
 * 
 * @copyright Copyright (c) 2025
 * 
 */

//include the mutex
#include "Mutex.h"

extern "C" {

Mutex* mutex_Create() {return new Mutex;}

void mutex_Destroy(Mutex* mut) {delete mut;}

void mutex_Lock(Mutex* mut) {mut->lock();}

void mutex_Unlock(Mutex* mut) {mut->unlock();}

bool mutex_Try_lock(Mutex* mut) {return mut->try_lock();}

}