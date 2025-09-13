/**
 * @file ScopeTimer.cpp
 * @author DM8AT
 * @brief implement the C binding for a scope timer
 * @version 0.1
 * @date 2025-09-05
 * 
 * @copyright Copyright (c) 2025
 * 
 */

//include scope timers
#include "ScopeTimer.h"

ScopeTimer* scopeTimer_Create(const char* name) {return new ScopeTimer(name);}

void scopeTimer_Destroy(ScopeTimer* timer) {delete timer;}
