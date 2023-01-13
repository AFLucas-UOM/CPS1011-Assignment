cmake_minimum_required(VERSION 3.23)
project(Project_C_Task2)

set(CMAKE_C_STANDARD 11)

set(SOURCE_PROJ2 main.c) # testing only
add_executable(main ${SOURCE_PROJ2}) #testing only

set(SOURCE_PROJ2 MixedStack.c)
add_executable(MixedStack ${SOURCE_PROJ2})

