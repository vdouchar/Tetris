#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <conio.h>

#include "../metier/Tetris.h"
#include "view/ConsoleTetrisObserver.h"

using namespace std;

std::mutex mtx;
std::condition_variable cv;
bool shouldMoveDown;

void moveDownThread(Tetris& tetris) {
    while (!tetris.endGame()) {
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait_for(lock, std::chrono::seconds(1), [] { return shouldMoveDown; });
            shouldMoveDown = false;
        }

        tetris += Direction2D::DOWN;

    }
}

void handleUserInputThread(Tetris& tetris) {
    while (!tetris.endGame()) {
        if (_kbhit()) {
            char key = _getch();
            switch (key) {
            case 'a':
                tetris += Direction2D::LEFT;
                break;
            case 'd':
                tetris += Direction2D::RIGHT;
                break;
            case 'q':
                tetris += Direction2D::DOWN;
                break;
            case 's':
                tetris.drop();
                break;
            case 'w':
                tetris.rotate(false);
                break;
            case 'r':
                tetris.rotate(true);
                break;
            }
        }
    }
}

int main() {
    Tetris tetris(true);
    ConsoleTetrisObserver cto { &tetris };

    // Create a thread for moving the tetris pieces down
    std::thread downThread(moveDownThread, std::ref(tetris));

    // Create a thread for handling user input
    std::thread userInputThread(handleUserInputThread, std::ref(tetris));

    // Continue running the game until it ends
    while (!tetris.endGame()) {

        // Pause the main thread for a short time based on the game speed
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long>(1000 * tetris.getSpeed())));

        // Set a flag indicating that the pieces should move down
        {
            std::lock_guard<std::mutex> lock(mtx); // Lock the mutex to ensure thread safety
            shouldMoveDown = true; // Set the flag to true
        }
        cv.notify_one(); // Notify the moveDownThread to move the pieces down
    }

    // Wait for the moveDownThread to finish
    downThread.join();
    // Wait for the userInputThread to finish
    userInputThread.join();

    return 0;
}
