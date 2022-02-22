cmake_minimum_required(VERSION 3.21)
project(lithium_debug)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(X11 REQUIRED x11)




set(SOURCE_FILES main.c)
add_executable(gtk-test ${SOURCE_FILES})
target_link_libraries(gtk-test ${GTK3_LIBRARIES})
target_include_directories(gtk-test PRIVATE ${GTK3_INCLUDE_DIRS})

target_link_libraries(gtk-test  ${X11_LIBRARIES})
target_include_directories(gtk-test PRIVATE ${X11_INCLUDE_DIRS})