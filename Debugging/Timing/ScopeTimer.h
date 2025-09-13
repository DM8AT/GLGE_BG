/**
 * @file ScopeTimer.h
 * @author DM8AT
 * @brief define a superset of a timer specialized to track the execution time of a single scope
 * @version 0.1
 * @date 2025-09-05
 * 
 * @copyright Copyright (c) 2025
 * 
 */

//header guard
#ifndef _GLGE_BG_SCOPE_TIMER_
#define _GLGE_BG_SCOPE_TIMER_

//include simple timers
#include "Timer.h"

//switch between C and C++ to implement a virtual class
#if __cplusplus

//for C++, create a child class of the base timer structure
struct ScopeTimer : public Timer
{
    /**
     * @brief Construct a new Scope Timer
     * 
     * @param name the name of the scope timer to create
     */
    ScopeTimer(const char* name)
     : Timer(), m_name(name)
    {}

    /**
     * @brief Destroy the Scope Timer
     */
    ~ScopeTimer()
    {
        //print the duration of the scope into the console
        printf("%s took %f seconds\n", m_name, getDeltaTime());
    }

protected:

    /**
     * @brief store the name of the timer
     */
    const char* m_name;

};

#else

//for C, define a simple opaque structure
typedef struct s_ScopeTimer{

    //for windows, add a single byte here to make the struct contain something
    uint8_t byte;

} ScopeTimer;

#endif

//start an extern section for C
//just to be sure
#if __cplusplus
extern "C" {
#endif

/**
 * @brief create a new scope timer object
 * 
 * @param name the name of the scope timer object it will print to the console on deletion
 * @return ScopeTimer* a pointer to the new scope timer object
 */
ScopeTimer* scopeTimer_Create(const char* name);

/**
 * @brief delete a scope timer object
 * 
 * This will print the duration of the scope of the timer to the console
 * 
 * @param timer a pointer to the scope timer object to delete
 */
void scopeTimer_Destroy(ScopeTimer* timer);

//the the extern section in C++
#if __cplusplus
}
#endif

#endif