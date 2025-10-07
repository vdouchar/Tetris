#include "TetrisController.h"
#include <QKeyEvent>
#include <QDebug>
#include <chrono>
#include <QApplication>

TetrisController::TetrisController(Tetris& tetris) : tetris_(tetris) {}

void TetrisController::startGame() {
    // Start the game loop in a separate thread
    gameThread_ = std::thread(&TetrisController::gameLoop, this);
    gameThread_.detach();
}

bool TetrisController::eventFilter(QObject *object, QEvent *event) {
    // Listen for key press events and control the Tetris game accordingly
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (!tetris_.endGame()) {
            switch (keyEvent->key()) {
            case Qt::Key_A:
            case Qt::Key_Left:
                tetris_ += Direction2D::LEFT;
                break;
            case Qt::Key_D:
            case Qt::Key_Right:
                tetris_ += Direction2D::RIGHT;
                break;
            case Qt::Key_Q:
            case Qt::Key_Down:
                tetris_ += Direction2D::DOWN;
                break;
            case Qt::Key_S:
            case Qt::Key_Space:
                tetris_.drop();
                break;
            case Qt::Key_W:
            case Qt::Key_Up:
                tetris_.rotate(false);
                break;
            case Qt::Key_R:
                tetris_.rotate(true);
                break;
            default:
                break;
            }
        }
    }
    return QObject::eventFilter(object, event);
}

void TetrisController::gameLoop() {
    // Game loop that continuously moves the Tetris pieces down until the game ends
    while (!tetris_.endGame()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long>(1000 * tetris_.getSpeed())));
        tetris_ += Direction2D::DOWN;
    }
}

TetrisController::~TetrisController()
{
    std::cout << "destruct TetrisController" << std::endl;
}
