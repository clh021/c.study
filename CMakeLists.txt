cmake_minimum_required(VERSION 3.21)
project(lithium_debug)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(X11 REQUIRED x11)
pkg_check_modules(XCB REQUIRED xcb)

pkg_check_modules(X11XCB REQUIRED x11-xcb)

# import
find_package(X11)

set(LIBS
        ${GTK3_LIBRARIES}
        ${X11_LIBRARIES}
        ${XCB_LIBRARIES}
        ${X11XCB_LIBRARIES}
        )
message(STATUS "LIBS: ${LIBS}")

set(INCLUDE_DIRS
        ${GTK3_INCLUDE_DIRS}
        ${X11_INCLUDE_DIRS}
        ${XCB_INCLUDE_DIRS}
        ${X11XCB_INCLUDE_DIRS}
        )
# console.log()
message(STATUS "INCLUDE_DIRS: ${INCLUDE_DIRS}")

# let SOURCE_FILES = "main.c"
set(SOURCE_FILES main.c)
add_executable(gtk-test ${SOURCE_FILES})
target_link_libraries(gtk-test ${LIBS})
target_include_directories(gtk-test PRIVATE ${INCLUDE_DIRS})