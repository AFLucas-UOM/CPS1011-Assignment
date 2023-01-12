cmake_minimum_required(VERSION 3.23)
project(Project_C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_PROJ main.c) # testing only
add_executable(main ${SOURCE_PROJ}) #testing only

set(SOURCE_PROJ PROJ_task1q3_menu.c)
add_executable(Menu ${SOURCE_PROJ})
