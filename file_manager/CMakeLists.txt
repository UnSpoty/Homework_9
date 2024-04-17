cmake_minimum_required(VERSION 3.0)
project(Ncurses_test)

find_package(Curses REQUIRED)
include_directories(${NCURSES_INCLUDE_DIR})
link_directories(${NCURSES_LIBRARY})

add_executable(Ncurses_tested main.c file_utils.c)
target_link_libraries(Ncurses_tested ${NCURSES_LIBRARIES})