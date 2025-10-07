#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QDialog>

#include "mainwindow.h"
#include "../metier/Tetris.h"
#include "TetrisController.h"

namespace Ui {
class ConfigWindow;
}

/**
 * @brief The ConfigWindow class represents a dialog window for configuring the Tetris game.
 *
 * This class inherits from QDialog and provides functionality for configuring the game settings.
 */
class ConfigWindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a ConfigWindow object with the given parameters.
     * @param parent The parent widget.
     */
    explicit ConfigWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the ConfigWindow class.
     */
    ~ConfigWindow();

private slots:
    /**
     * @brief Slot function called when the submit button is clicked.
     */
    void on_submitBtn_clicked();

private:
    Ui::ConfigWindow *ui; /**< Pointer to the UI components of the ConfigWindow. */
    Tetris* tetris; /**< Pointer to the Tetris game instance. */
    TetrisController* ttctrl; /**< Pointer to the Tetris controller instance. */
    MainWindow* gameWindow; /**< Pointer to the main game window. */
};

#endif // CONFIGWINDOW_H
