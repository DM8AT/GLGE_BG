/**
 * @file CommonDefines.h
 * @author DM8AT
 * @brief define some commons defines for GLGE
 * @version 0.1
 * @date 2025-09-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

//header guard
#ifndef _GLGE_BG_DEFINES_COMMON_
#define _GLGE_BG_DEFINES_COMMON_

//for C++, define a noexception qualifier
#if __cplusplus
#define GLGE_NOEXCEPT noexcept
#else
#define GLGE_NOEXCEPT
#endif

//for C++, define a constexpression qualifier
#if __cplusplus
#define GLGE_CONSTEXPR constexpr
#else
#define GLGE_CONSTEXPR
#endif

//convert a value to a string
#define GLGE_TO_STRING(value) #value

//convert a define to a string
#define GLGE_DEFINE_TO_STRING(define) GLGE_TO_STRING(define)

#endif