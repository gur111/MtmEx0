cmake_minimum_required(VERSION 3.15)
project(MtmEx0 C)

set(${CMAKE_CXX_FLAGS} 11)

add_executable(mtm_tot
        part1/part1.c)

add_executable(mtm_buggy
        part2/mtm_buggy.c)

target_link_libraries(mtm_tot m)