# 🕹️ Tetris Game in C++

Welcome to the **Tetris Game** project! This is a personal project developed in **C++** featuring two distinct gameplay modes: a modern **graphical interface (GUI)** and a classic **console experience**.

The project focuses on a **clean, maintainable structure** using the **Model-View Architecture** to ensure high modularity and easy future extensions.

---

## ✨ Key Features

| Feature                  | Description                                                                 |
|---------------------------|-----------------------------------------------------------------------------|
| Dual Interface            | Play in a classic text-based **Console Version** or a full **Graphical Version (GUI)**. |
| Qt Powered GUI            | The graphical version is built using the **Qt Framework** for a modern visual experience. |
| Modular Design (Model-View)| Separation of game logic (**Model**) from presentation (**View**) for reusable and maintainable code. |
| Standard Build            | Uses **CMake** for configuration, compatible across multiple operating systems. |

---

## 💻 Tech Stack & Architecture

**Development Environment:**
- **Language:** C++ (C++20 standard)  
- **GUI Framework:** Qt (Widgets and Graphics)  
- **Build System:** CMake (`CMakeLists.txt`)  
- **Compiler:** MinGW 6.5.3  
- **IDE:** Qt Creator  

**Architecture (Model-View):**
- **Model (Core Logic):** Handles Tetris mechanics: piece generation, movement, rotation, collision detection, and scoring. Fully UI-agnostic.  
- **View (Presentation):** Manages display logic for both interfaces. The GUI uses Qt widgets; the Console version uses terminal output.  
- **Controller (Input/Update):** Handles keyboard input and relays instructions to the Model, triggering updates in the View.

---

## 📥 Getting Started & Installation

You can play the game by either **downloading the executable** or **building from source**.

### Option A: Download Executable (Recommended)
- No compilation required. Ready to run.
- Go to the [Releases Page](https://github.com/vdouchar/Tetris/releases).  
- Download the ZIP for your OS (`Tetris_v1.0_Windows.zip`).  
- Unzip and run the main executable (`Tetris.exe`).

### Option B: Build from Source (For macOS/Linux Users or Developers)
- Requires Qt Creator or a C++ compiler and CMake.  

```bash
git clone https://github.com/vdouchar/Tetris.git
cd tetris
```
- Open the project folder in Qt Creator and run the build process. 
- Alternatively, use CMake to configure and build for your platform. 

## 👨‍💻 Author

Vincent Douchar - [@vdouchar](https://github.com/vdouchar)
