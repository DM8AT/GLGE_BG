cmake_minimum_required(VERSION 3.10)

project(MAIN LANGUAGES C CXX)

add_subdirectory(src/GLGEBg)

add_executable(MAIN src/main.c)

target_link_libraries(MAIN PUBLIC GLGE_BG)