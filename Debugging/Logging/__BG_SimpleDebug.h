/**
 * @file __BG_SimpleDebug.h
 * @author DM8AT
 * @brief some background defines for debugging functionality
 * @version 0.1
 * @date 2025-09-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

//header guard
#ifndef _GLGE_BG_SIMPLE_DEBUG_
#define _GLGE_BG_SIMPLE_DEBUG_

//only available for C++
#if __cplusplus

//include io stuff
#include <iostream>

//include assertions
#include <assert.h>

//simple message
#define GLGE_MESSAGE(message) std::cout << message << "\n"

//simple marking
#define GLGE_MARKER(message) std::cout << message << " at " << (__extension__ __PRETTY_FUNCTION__) << "\n"

//simple abort method
#define GLGE_ABORT(message) GLGE_MARKER(message); abort()

//simple assertion method
#define GLGE_ASSERT(message, condition) if (condition) {GLGE_ABORT(message);}

//simple debug message
#if GLGE_BG_DEBUG
#define GLGE_DEBUG_MESSAGE(message) std::cout << message << "\n"
#else
#define GLGE_DEBUG_MESSAGE(message)
#endif

//simple debug marking
#if GLGE_BG_DEBUG
#define GLGE_DEBUG_MARKER(message) std::cout << message << " at " << __ASSERT_FUNCTION << "\n"
#else
#define GLGE_DEBUG_MARKER(message)
#endif

#if GLGE_BG_DEBUG
#define GLGE_DEBUG_ABORT(message) GLGE_DEBUG_MARKER(message); abort()
#else
#define GLGE_DEBUG_ABORT(message)
#endif

//simple assertion method
#if GLGE_BG_DEBUG
#define GLGE_DEBUG_ASSERT(message, condition) if (condition) {GLGE_DEBUG_ABORT(message);}
#else
#define GLGE_DEBUG_ASSERT(message, condition)
#endif

#else

#define GLGE_DEBUG_MESSAGE(message)

#define GLGE_DEBUG_MARKER(message)

#define GLGE_DEBUG_ABORT(message)

#define GLGE_DEBUG_ASSERT(message, condition)

#define GLGE_MESSAGE(message)

#define GLGE_MARKER(message)

#define GLGE_ABORT(message)

#define GLGE_ASSERT(message, condition)

#endif

#endif