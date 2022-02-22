cmake_minimum_required(VERSION 3.21)
project(lithium_debug C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(main.c)


find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})
