/**
 * @file Timer.h
 * @author DM8AT
 * @brief define an interface for a simple timer
 * @version 0.1
 * @date 2025-09-05
 * 
 * @copyright Copyright (c) 2025
 * 
 */

//header guard
#ifndef _GLGE_BG_TIMER_
#define _GLGE_BG_TIMER_

//include timing stuff for C++
#if __cplusplus
#include <chrono>
#endif

/**
 * @brief store a simple timer
 */
typedef struct s_Timer {

    //check for C++ to define the timer
    #if __cplusplus

    /**
     * @brief Construct a new Timer
     */
    s_Timer() = default;

    /**
     * @brief Destroy the Timer
     */
    ~s_Timer() {}

    /**
     * @brief re-start the timing of the timer
     */
    inline void restart() noexcept {m_start = std::chrono::system_clock::now();}

    /**
     * @brief Get the difference in time in seconds since the start (construction / explicit start) from the timer to the current time point
     * 
     * @return double the difference in seconds
     */
    inline double getDeltaTime() noexcept {return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - m_start).count() / 1000000000.;}

protected:

    /**
     * @brief store the start time point
     */
    std::chrono::system_clock::time_point m_start = std::chrono::system_clock::now();

    #endif

} Timer;

//start an extern section for C
//just to be sure
#if __cplusplus
extern "C" {
#endif

/**
 * @brief create a new timer object
 * 
 * @return Timer* a pointer to the new timer object
 */
Timer* timer_Create();

/**
 * @brief destroy a timer object
 * 
 * @param timer a pointer to the timer object to destroy
 */
void timer_Destroy(Timer* timer);

/**
 * @brief re-start the counting of a timer
 * 
 * @param timer a pointer to the timer object to re-start
 */
void timer_Restart(Timer* timer);

/**
 * @brief get the time difference between the calling time point and the start time point of a timer object
 * 
 * @param timer a pointer to the timer to quarry the start time from
 * @return double the difference in time in seconds
 */
double timer_GetDeltaTime(Timer* timer);

//the the extern section in C++
#if __cplusplus
}
#endif

#endif