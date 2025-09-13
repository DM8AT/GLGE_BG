cmake_minimum_required(VERSION 3.10)

set(GLGE_BG_VERSION 1.0.0)

project(GLGE_BG LANGUAGES CXX VERSION ${GLGE_BG_VERSION})

set(SRC CBinding/Vector.cpp
        CBinding/Mutex.cpp
        CBinding/Thread.cpp
        CBinding/String.cpp
        
        SystemInfo/SystemInfo.cpp

        Debugging/Logging/Logger.cpp

        Debugging/Timing/Timer.cpp
        Debugging/Timing/ScopeTimer.cpp
        )

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_library(GLGE_BG ${SRC})

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(GLGE_BG PUBLIC GLGE_BG_DEBUG=1)
endif()

set_target_properties(GLGE_BG PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON VERSION ${GLGE_BG_VERSION} SOVERSION 1)

target_include_directories(GLGE_BG PRIVATE GLGEBg)
target_include_directories(GLGE_BG PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})