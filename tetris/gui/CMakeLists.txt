cmake_minimum_required(VERSION 3.5)

project(tetris LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-Wall -pedantic-errors")
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# ===========================
# Ajout de l'exécutable GUI
# ===========================
add_executable(gui
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
    ../console/view/ConsoleTetrisObserver.h

    ../metier/Random.hpp

    ../metier/dp/Observable.cpp
    ../console/view/ConsoleTetrisObserver.cpp
    ../metier/Tetris.cpp
    ../metier/Bag.cpp
    ../metier/Board.cpp
    ../metier/Direction2D.cpp
    ../metier/Position.cpp
    ../metier/Brick.cpp
    ../metier/DefaultBrick.cpp

    mainwindow.h
    mainwindow.cpp
    mainwindow.ui
    widget/CaseWidget.h
    widget/CaseWidget.cpp
    widget/GameBoardWidget.h
    widget/GameBoardWidget.cpp
    colors/Color.h
    colors/Color.cpp
    widget/GameInfoWidget.h
    widget/GameInfoWidget.cpp
    TetrisController.h
    TetrisController.cpp
    configwindow.h configwindow.cpp configwindow.ui
)

# ===========================
# Ajouter tous les dossiers contenant des headers
# ===========================
target_include_directories(gui PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}       # dossier gui/
    ${CMAKE_CURRENT_SOURCE_DIR}/widget
    ${CMAKE_CURRENT_SOURCE_DIR}/colors
    ${CMAKE_CURRENT_SOURCE_DIR}/../metier
    ${CMAKE_CURRENT_SOURCE_DIR}/../console/view
)

# ===========================
# Qt
# ===========================
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
target_link_libraries(gui PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# ===========================
# Installation
# ===========================
include(GNUInstallDirs)
install(TARGETS gui
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
