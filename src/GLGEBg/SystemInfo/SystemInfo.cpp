/**
 * @file SystemInfo.cpp
 * @author DM8AT
 * @brief implement the backend to quarry information about the system the application is running on
 * @version 0.1
 * @date 2025-09-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

//include the system info header
#include "SystemInfo.h"

//define the linux backend
#if __linux

//include the file management stuff
#include <fstream>
#include <string>

//include debug stuff
#include "../Debugging/Logging/__BG_SimpleDebug.h"

static uint64_t __linux_util_getProcElement(const char* file, const char* name, const char* format)
{
    //open the memory info
    std::ifstream f(file);

    //check if the file was opend
    GLGE_ASSERT("Failed to open the file \"" << file << "\" for a linux device.", !f.is_open());

    //store the current line
    std::string curr;
    //loop while the line does not contain the total memory qualifier
    while (getline(f, curr) && (curr.find(name) == std::string::npos)) {}

    //don't forget to close the file when it's no longer needed
    f.close();

    //store the memory
    uint64_t memKb = 0;
    sscanf(curr.c_str(), format, &memKb);

    return memKb * 1024;
}

#endif

//define the windows backend
#if defined(__WIN32__) || defined(_WIN32) || defined(__CYGWIN32__)

//include the windows API
#include <windows.h>

static inline MEMORYSTATUSEX __windows_GetMemoryStatus()
{
    //prepare the quarry of the data
    MEMORYSTATUSEX ret;
    ret.dwLength = sizeof(ret);

    //quarry the memory status
    GlobalMemoryStatusEx(&ret);

    //return the status
    return ret;
}

//for process related stuff
#include <psapi.h>

static inline uint64_t __windows_GetOwnMemUsage()
{
    //get the own process
    HANDLE self = GetCurrentProcess();
    //store the memory info
    PROCESS_MEMORY_COUNTERS_EX mem = { 0 };
    mem.cb = sizeof(mem);
    //get the memory info using the winapi
    GetProcessMemoryInfo(self, (PROCESS_MEMORY_COUNTERS*)&mem, sizeof(mem));

    return mem.PagefileUsage;
}

#endif

uint64_t glge_GetMaxMemoryCount() {
    #if __linux
    return __linux_util_getProcElement("/proc/meminfo", "MemTotal", "MemTotal: %lu");
    #elif defined(__WIN32__) || defined(_WIN32) || defined(__CYGWIN32__)
    return __windows_GetMemoryStatus().ullTotalPhys;
    #else
    return 0;
    #endif
}

uint64_t glge_GetCurrentMemoryUsage() {
    #if (__linux) || (defined(__WIN32__) || defined(_WIN32) || defined(__CYGWIN32__))
    return glge_GetMaxMemoryCount() - glge_GetFreeMemory();
    #else
    return 0;
    #endif
}

uint64_t glge_GetFreeMemory() {
    #if __linux
    return __linux_util_getProcElement("/proc/meminfo", "MemAvailable", "MemAvailable: %lu");
    #elif defined(__WIN32__) || defined(_WIN32) || defined(__CYGWIN32__)
    return __windows_GetMemoryStatus().ullAvailPhys;
    #else
    return 0;
    #endif
}

uint64_t glge_GetMemoryOwnUsage() {
    #if __linux
    return __linux_util_getProcElement("/proc/self/status", "VmSize", "VmSize: %lu");
    #elif defined(__WIN32__) || defined(_WIN32) || defined(__CYGWIN32__)
    return __windows_GetOwnMemUsage();
    #else
    return 0;
    #endif
}