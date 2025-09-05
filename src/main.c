/**
 * @file main.c
 * @author DM8AT
 * @brief an example file for the background library of GLGE
 * @version 0.1
 * @date 2025-09-05
 * 
 * @copyright Copyright (c) 2025
 * 
 */

//include the background library
#include "GLGEBg/GLGEBg.h"
//for printing stuff
#include <stdio.h>

/**
 * @brief an example function on what debug statements in time critical code might look like
 * 
 * @param logger a pointer to a logger to log the time critical stuff to. Printing is slow, so it should be avoided in time critical operations. 
 */
void timeCriticalStuff(Logger* logger)
{
    //create a scope timer to track the duration of the scope
    ScopeTimer* sTimer = scopeTimer_Create("Time Critical Scope");

    //during logging, the order of the submitted arguments stays the same
    //but the time point of printing may differ in regards to other print operations
    logger_log("Starting time critical stuff", logger);

    //the example here for time critical stuff is adding and printing elements from a vector
    Vector* vec = vector_Create(sizeof(uint16_t));

    //add a lot of elements
    vector_Reserve(UINT16_MAX, vec);
    uint64_t cap = vec->byteCapacity / vec->elementSize;
    for (uint64_t i = 0; i < cap; ++i)
    {
        //just add the element's id
        vector_Push_back(&i, vec);
    }

    //make sure to clean up
    vector_Destroy(vec);

    //log that the time critical stuff is done
    logger_log("Done with timing stuff", logger);

    //make sure to destroy all objects from the library that where created. 
    //This calls the C++ destructor and prints the results of the scope timer. 
    scopeTimer_Destroy(sTimer);
}

/**
 * @brief a function to print a string in a beautiful way
 * 
 * @param str the string to print (it's actually an std::string from C++)
 */
void beautyPrint(String* str)
{
    //use a totally beautiful printing function
    printf("[INFO] %s\n", string_C_Str(str));
}

int main(void)
{
    //create a new logger
    Logger* log = logger_CreateAndOverload(false, beautyPrint);

    //get some information about the memory of the computer the program is running on
    printf("=====================\nRAM info:\nTotal RAM size: %lu bytes\nUsed RAM: %lu bytes\nFree RAM: %lu bytes\nUsed by this process: %lu bytes\n=====================\n", 
           glge_GetMaxMemoryCount(), glge_GetCurrentMemoryUsage(), glge_GetFreeMemory(), glge_GetOwnMemoryUsage());

    //execute your very time critical code
    timeCriticalStuff(log);

    //print all logging info afterwards
    logger_printAll(log);

    //make really sure to clean up
    logger_Destroy(log);
}