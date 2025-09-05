/**
 * @file SystemInfo.h
 * @author DM8AT
 * @brief define a unified API to quarry information about the system the program is running on
 * @version 0.1
 * @date 2025-09-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

//header guard
#ifndef _GLGE_BG_SYSTEM_INFO_
#define _GLGE_BG_SYSTEM_INFO_

//specific sized integer types are needed
#include <stdint.h>

//start an extern section for C
//just to be sure
#if __cplusplus
extern "C" {
#endif

/**
 * @brief get the total amount of hardware available RAM in bytes
 * 
 * @return uint64_t the amount of hardware RAM in bytes
 */
uint64_t glge_GetMaxMemoryCount();

/**
 * @brief get how much RAM is currently being used
 * 
 * @return uint64_t the amount of used RAM in bytes
 */
uint64_t glge_GetCurrentMemoryUsage();

/**
 * @brief get the amount of free RAM
 * 
 * @return uint64_t the amount of free RAM in bytes
 */
uint64_t glge_GetFreeMemory();

/**
 * @brief get how much RAM this program needs
 * 
 * @return uint64_t the memory usage of the program in bytes
 */
uint64_t glge_GetOwnMemoryUsage();

//the the extern section in C++
#if __cplusplus
}
#endif

#endif