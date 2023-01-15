cmake_minimum_required(VERSION 3.23)
project(MixedStack)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES MixedStack.c test_driver.c)
add_library(MixedStack SHARED ${SOURCE_FILES})
add_executable(test_driver ${SOURCE_FILES})
target_link_libraries(test_driver MixedStack)
