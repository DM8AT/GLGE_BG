/**
 * @file Logger.cpp
 * @author DM8AT
 * @brief implement the functionality for the semi-abstract logger class
 * @version 0.1
 * @date 2025-09-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */

//include the logger class
#include "Logger.h"

//include printing stuff
#include <iostream>

void logger_defaultPrint(String* str)
{
    //simply print the string to the console
    //make sure it is printed. This is a log, so there could
    //be a termination before the next normal flush
    std::cout << str->c_str() << "\n" << std::flush;
}

void s_Logger::log(const char* string)
{
    //check if direct logging is enabled
    //this switches between direct print and delayed printing
    if (autoPrint)
    {
        //create a temporary string
        String str(string);
        //direct message logging
        (*print_func)(&str);
    }
    else
    {
        //lock the mutex. Important to be thread safe...
        mutex.lock();
        //add the element
        String* str = new String(string);
        toPrint.push_back(&str);
        //make sure to unlock the mutex
        mutex.unlock();
    }
}

void s_Logger::printAll()
{
    //speed check - if the print queue is empty, stop
    if (toPrint.byteSize == 0) {return;}
    //make sure to lock the mutex. No new stuff may be added while it is printing
    mutex.lock();
    //print all elements
    uint64_t elCount = toPrint.byteSize/toPrint.elementSize;
    for (uint64_t i = 0; i < elCount; ++i)
    {
        String* str = *((String**)toPrint[i]);
        (*print_func)(str);
        delete str;
    }
    //clear the whole vector
    toPrint.clear();
    //unlock the mutex
    mutex.unlock();
}


Logger* logger_Create() {return new Logger();}

Logger* logger_CreateAutoPrint(bool autoPrint) {return new Logger(autoPrint);}

Logger* logger_CreateAndOverload(bool autoPrint, void (*func)(String*)) {return new Logger(autoPrint, func);}

void logger_Destroy(Logger* logger) {delete logger;}

void logger_log(const char* cstr, Logger* logger) {logger->log(cstr);}

void logger_logString(const String* str, Logger* logger) {logger->log(*str);}

void logger_printAll(Logger* logger) {logger->printAll();}
