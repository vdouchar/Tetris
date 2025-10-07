cmake_minimum_required(VERSION 3.5)

project(tetris LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-Wall -pedantic-errors")

add_executable(console
    main.cpp
    ../metier/Direction2D.h
    ../metier/Position.h
    ../metier/Brick.h
    ../metier/Board.h
    ../metier/Bag.h
    ../metier/Tetris.h
    ../metier/DefaultBrick.h
    ../metier/dp/Observer.h
    ../metier/dp/Observable.h
    view/ConsoleTetrisObserver.h

    ../metier/Random.hpp

    ../metier/dp/Observable.cpp
    view/ConsoleTetrisObserver.cpp
    ../metier/Tetris.cpp
    ../metier/Bag.cpp
    ../metier/Board.cpp
    ../metier/Direction2D.cpp
    ../metier/Position.cpp
    ../metier/Brick.cpp
    ../metier/DefaultBrick.cpp
)

include(GNUInstallDirs)
install(TARGETS console
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
