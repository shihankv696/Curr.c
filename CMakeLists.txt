cmake_minimum_required(VERSION 3.10)

project(Curr.c)

find_package(fmt CONFIG REQUIRED)

add_executable(Curr Curr.c)

target_link_libraries(Curr PRIVATE fmt::fmt)
