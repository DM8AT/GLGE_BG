# About

This library is a binding between some features of the C++ STD library and C. It is designed to simplify development for libraries that target C and C++ at the same time by providing useful features similar to the STD library, but with an interface for C and C++ at the same time. 

# Function list
Currently implemented are: 
| Class name | Fully implemented | First Version | Last update in |
|------------|-------------------|---------------|----------------|
| Mutex      | :white_check_mark:| 1.0.0         | 1.0.0          |
| String     | :white_check_mark:| 1.0.0         | 1.0.0          |
| Thread     | :white_check_mark:| 1.0.0         | 1.0.0          |
| Vector     | :white_check_mark:| 1.0.0         | 1.0.0          |
| Logger     | :white_check_mark:| 1.0.0         | 1.0.0          |
| Timer      | :white_check_mark:| 1.0.0         | 1.0.0          |
| Scope Timer| :white_check_mark:| 1.0.0         | 1.0.0          |

# Compiling the library
## Building the library
To compile the library, simply go to the directory to compile to (`bin` in the example) and run cmake with the path to the root of the project (the folder you cloned to). Then, simply run `cmake --build` to build the project and library. 

## Implementing the library into your CMake project
To add the library to a CMake project, simply use the `add_subdirectory` command with the path to the library's directory. Them, link against the library target called `GLGE_BG` and compile your CMake project like normal. 

# Current OS support
The library contains some operating dependant code. Currently, it is tested under linux (debian based system) and Windows. For MacOS, there is currently no implementation available. 