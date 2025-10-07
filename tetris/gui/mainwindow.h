#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../metier/dp/Observer.h"
#include "../metier/Tetris.h"
#include "widget/GameBoardWidget.h"
#include "widget/GameInfoWidget.h"

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class represents the main window of the Tetris game.
 *
 * This class inherits from QMainWindow and implements the Observer interface to update the game state.
 */
class MainWindow : public QMainWindow, Observer
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a MainWindow object with the given parameters.
     * @param subject Pointer to the Tetris game instance.
     * @param parent Pointer to the parent widget.
     */
    explicit MainWindow(Tetris* subject,QWidget *parent = nullptr);

    /**
     * @brief Virtual destructor for MainWindow.
     */
    virtual ~MainWindow() override;

    /**
     * @brief Implementation of the update method to display Tetris game state.
     */
    void update() override;

    void onGameOver();

private:
    Ui::MainWindow *ui; /**< Pointer to the UI components of the MainWindow. */
    Tetris* subject_; /**< Pointer to the Tetris game instance. */
    GameBoardWidget *gameBoardWidget; /**< Pointer to the game board widget. */
    GameInfoWidget *gameInfoWidget; /**< Pointer to the game info widget. */
    bool gameOverMessageBoxDisplayed = false;
};

#endif // MAINWINDOW_H
