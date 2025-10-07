#ifndef GAMEBOARDWIDGET_H
#define GAMEBOARDWIDGET_H

#include <QWidget>
#include <QGridLayout>

#include "../../metier/Tetris.h"

/**
 * @brief The GameBoardWidget class represents a widget for displaying the Tetris game board.
 *
 * This class inherits from QWidget and provides functionality to update and display the game board.
 */
class GameBoardWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructs a GameBoardWidget object with the given parameters.
     * @param qhboxlayout The horizontal layout to contain the board widget.
     * @param rows The number of rows in the game board.
     * @param columns The number of columns in the game board.
     * @param parent The parent widget.
     */
    explicit GameBoardWidget(QHBoxLayout * qhboxlayout, int rows, int columns,QWidget *parent = nullptr);

    /**
     * @brief Destructor for the GameBoardWidget class.
     */
    ~GameBoardWidget();

    /**
     * @brief Updates the game board with the current state of the Tetris game.
     * @param tetris Pointer to the Tetris game instance.
     */
    void updateBoard(Tetris * tetris);

private:
    QGridLayout *gridLayout; /**< The grid layout for arranging case widgets. */
    int numRows; /**< The number of rows in the game board. */
    int numCols; /**< The number of columns in the game board. */
};

#endif // GAMEBOARDWIDGET_H
