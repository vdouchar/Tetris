Tetris Game in C++

Welcome to the Tetris Game project! This is a personal project created in C++ using the Qt framework, CMake, and the MinGW 6.5.3 compiler. The project offers two modes of gameplay: a console-based version and a graphical interface powered by Qt. It is organized with a Model-View architecture for a clean separation of concerns and modularity.

Project Overview

This Tetris project was developed with the following key elements:

    - Programming Language: C++
    - IDE: Qt Creator
    - Compiler: MinGW 6.5.3
    - Build System: CMake (using CMakeLists.txt for configuration)
    - Framework: Qt for the graphical user interface
    - Architecture: Model-View for a modular and maintainable structure
    
    Features :
        - Console Version: Play Tetris directly from the console, providing a lightweight, text-based experience.
        - Graphical Version: Enjoy a full graphical version of the game built with Qt components for an enhanced Tetris experience.
        - Modular Design: The project is organized with a Model-View architecture to separate game logic (model) from the user interface (view).
        
Project Structure

The project consists of the following main components:

    Model: Manages the core logic of Tetris, including piece generation, movement, collision detection, and scoring. The model is independent of any UI framework, making it reusable for both console and graphical interfaces.

    View: Contains both the console-based and graphical-based views for the game. The console view directly interacts with the terminal, while the graphical view uses Qt widgets and components to render the game interface.

    Controller (optional): May handle the communication between the model and view, especially useful in the graphical version for capturing user inputs and updating the display.

By Douchar Vincent.