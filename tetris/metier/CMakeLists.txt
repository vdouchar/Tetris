cmake_minimum_required(VERSION 3.5)

project(Tetris LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-Wall -pedantic-errors")
set(CMAKE_CXX_STANDARD 20)

add_executable(metier
    Direction2D.h
    Position.h
    Brick.h
    Board.h
    Bag.h
    Tetris.h
    DefaultBrick.h
    dp/Observer.h
    dp/Observable.h

    Random.hpp

    dp/Observable.cpp
    Tetris.cpp
    Bag.cpp
    Board.cpp
    Direction2D.cpp
    Position.cpp
    Brick.cpp
    DefaultBrick.cpp
    main_model.cpp
)

include(GNUInstallDirs)
install(TARGETS metier
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
