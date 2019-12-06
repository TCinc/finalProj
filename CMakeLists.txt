cmake_minimum_required(VERSION 3.9)

# Set the title of your project and language
project(Snake2 C)

# Set the compiler you will be using
set(CMAKE_C_STANDARD 11)

# Turn on helpful compiler warnings
set(CMAKE_C_FLAGS -Wall)

# Settings for use of curses.h
find_package(curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
set(CMAKE_CXX_FLAGS -lncurses)

# Set the source directory and tell cmake what your
# source files are
set(SDIR ../)

set(SOURCE_FILES
        #${SDIR}snakefuncts.c
        ${SDIR}main.c)

# Tell cmake the name of your executable and what source files to
# build from
add_executable(Snake2 ${SOURCE_FILES})

# For curses.h
target_link_libraries(Snake2 ${CURSES_LIBRARIES})