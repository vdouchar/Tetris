cmake_minimum_required(VERSION 3.5)

project(tetris LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-Wall -pedantic-errors")

# ===========================
# Options de build
# ===========================
option(BUILD_CONSOLE "Build console version (requires <conio.h> on Windows)" ON)
option(BUILD_GUI "Build Qt graphical version" ON)
option(BUILD_TESTS "Build unit tests" ON)

# ===========================
# Sous-projets
# ===========================
add_subdirectory(metier)

if(BUILD_CONSOLE)
    message(STATUS "✅ Building console version")
    add_subdirectory(console)
else()
    message(STATUS "⏩ Skipping console version (BUILD_CONSOLE=OFF)")
endif()

if(BUILD_GUI)
    message(STATUS "✅ Building GUI version")
    add_subdirectory(gui)
endif()

if(BUILD_TESTS)
    message(STATUS "✅ Building tests")
    add_subdirectory(tests)
endif()

# ===========================
# Installation
# ===========================
include(GNUInstallDirs)

if(BUILD_CONSOLE)
    install(TARGETS console
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endif()