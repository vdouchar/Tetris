#ifndef TETRISCONTROLLER_H
#define TETRISCONTROLLER_H

#include <QObject>
#include <thread>
#include "../metier/Tetris.h"

/**
 * @brief The TetrisController class controls the Tetris game flow.
 *
 * This class manages the game loop and event handling.
 */
class TetrisController : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Constructs a TetrisController object with the given Tetris game instance.
     * @param tetris Reference to the Tetris game instance.
     */
    TetrisController(Tetris& tetris);

    /**
     * @brief Destructor for TetrisController.
     */
    ~TetrisController();

    /**
     * @brief Starts the Tetris game.
     */
    void startGame();

protected:
    /**
     * @brief Event filter to handle events.
     * @param object The object that received the event.
     * @param event The event to handle.
     * @return True if the event was handled, false otherwise.
     */
    bool eventFilter(QObject *object, QEvent *event) override;

private:
    Tetris& tetris_; /**< Reference to the Tetris game instance. */
    std::thread gameThread_; /**< Thread for running the game loop. */

    /**
     * @brief Game loop method (to add on thread).
     */
    void gameLoop();
};

#endif // TETRISCONTROLLER_H
