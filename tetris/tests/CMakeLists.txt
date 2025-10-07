cmake_minimum_required(VERSION 3.5)

project(Tetris LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-Wall -pedantic-errors")
set(CMAKE_CXX_STANDARD 20)

add_executable(tests
                Brick_tests.cpp
                Bag_tests.cpp
                Board_tests.cpp
                Tetris_tests.cpp

                ../metier/Brick.cpp
                ../metier/Position.cpp
                ../metier/Bag.cpp
                ../metier/DefaultBrick.cpp
                ../metier/Direction2D.cpp
                ../metier/Board.cpp
                ../metier/Tetris.cpp
                ../metier/dp/Observable.cpp
            )

target_include_directories(tests PRIVATE ../model)

Include(FetchContent)


FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.3.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)
#list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

target_link_libraries(tests Catch2::Catch2WithMain)
