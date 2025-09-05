/**
 * @file Timer.cpp
 * @author DM8AT
 * @brief 
 * @version 0.1
 * @date 2025-09-05
 * 
 * @copyright Copyright (c) 2025
 * 
 */

//include the timer
#include "Timer.h"

Timer* timer_Create() {return new Timer();}

void timer_Destroy(Timer* timer) {delete timer;}

void timer_Restart(Timer* timer) {timer->restart();}

double timer_GetDeltaTime(Timer* timer) {return timer->getDeltaTime();}