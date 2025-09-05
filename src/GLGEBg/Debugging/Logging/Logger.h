/**
 * @file Logger.h
 * @author DM8AT
 * @brief define an interface for a simple logger class
 * @version 0.1
 * @date 2025-09-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */

//header guard
#ifndef _GLGE_BG_LOGGER_
#define _GLGE_BG_LOGGER_

//the vector and string types are needed
#include "../../CBinding/Vector.h"
#include "../../CBinding/String.h"

//a mutex is required for multiple threads to commit to the same log at the same time
//or for one thread to print the log while another writes to it
#include "../../CBinding/Mutex.h"

//start an extern section for C
//just to be sure
#if __cplusplus
extern "C" {
#endif

/**
 * @brief the default print function for a logger
 * 
 * @param str a pointer to the string to print
 */
void logger_defaultPrint(String* str);

//the the extern section in C++
#if __cplusplus
}
#endif

/**
 * @brief store the actual logger
 * 
 * Loggers are virtual. The virtual element is implemented using function pointers. 
 */
typedef struct s_Logger {

    //store a vector of string pointer that can be printed
    Vector toPrint;
    //store the mutex to sync thread access
    Mutex mutex;
    //a boolean to say if the logger should auto-call the print function if an element is added
    bool autoPrint;

    //a function that is used to print all lines of the log to some place
    void (*print_func)(String* str);

    //implement a C++ interface
    #if __cplusplus

    /**
     * @brief Construct a new Logger
     * 
     * @param _autoPrint true : all log events will print instantly | false : logging events will be queued up and then be printed at a single point
     * @param func a function pointer to the function to use for printing
     */
    s_Logger(bool _autoPrint = false, void (*func)(String*) = logger_defaultPrint)
     : toPrint(sizeof(String*)), mutex(), autoPrint(_autoPrint), print_func(func)
    {}

    /**
     * @brief Destroy the Logger
     */
    ~s_Logger() {}

    /**
     * @brief log a single constant string
     * 
     * @param string the string to log
     */
    void log(const char* string);

    /**
     * @brief log a C-Compatibility string
     * 
     * @param string the string to lock
     */
    inline void log(const String& string) {log(string.c_str());}

    /**
     * @brief print and clear all data logged in the logger
     */
    void printAll();

    #endif

} Logger;

//start an extern section for C
//just to be sure
#if __cplusplus
extern "C" {
#endif

/**
 * @brief construct a new logger
 * 
 * @return Logger the new logger
 */
Logger* logger_Create();

/**
 * @brief construct a new logger that sets the auto print object
 * 
 * @param autoPrint true : all log events will print instantly | false : logging events will be queued up and then be printed at a single point
 * @return Logger the new logger
 */
Logger* logger_CreateAutoPrint(bool autoPrint);

/**
 * @brief construct a new logger that overloads the print function
 * 
 * @param autoPrint true : all log events will print instantly | false : logging events will be queued up and then be printed at a single point
 * @param func a function pointer to the function to use for printing
 * @return Logger the new logger
 */
Logger* logger_CreateAndOverload(bool autoPrint, void (*func)(String*));

/**
 * @brief destroy a logger object
 * 
 * @param logger the logger to delete
 */
void logger_Destroy(Logger* logger);

/**
 * @brief log a new message
 * 
 * @param cstr the c string to log
 * @param logger a pointer to the logger to log to
 */
void logger_log(const char* cstr, Logger* logger);

/**
 * @brief log a new message
 * 
 * @param str the string to log
 * @param logger a pointer to the logger to log to
 */
void logger_logString(const String* str, Logger* logger);

/**
 * @brief print all the log data
 * 
 * @param logger the logger to print from
 */
void logger_printAll(Logger* logger);

//the the extern section in C++
#if __cplusplus
}
#endif

#endif