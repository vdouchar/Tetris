#ifndef GAMEINFOWIDGET_H
#define GAMEINFOWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QGridLayout>

#include "../../metier/Tetris.h"

/**
 * @brief The GameInfoWidget class represents a widget for displaying game information.
 *
 * This class inherits from QWidget and provides functionality to display score, level, lines, and the next shape.
 */
class GameInfoWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructs a GameInfoWidget object with the given parameters.
     * @param layout The horizontal layout to contain the info widget.
     * @param score The initial score value.
     * @param level The initial level value.
     * @param lines The initial lines cleared value.
     * @param parent The parent widget.
     */
    explicit GameInfoWidget(QHBoxLayout *layout, int score, int level, int lines, QWidget *parent = nullptr);

    /**
     * @brief Destructor for the GameInfoWidget class.
     */
    ~GameInfoWidget();

    /**
     * @brief Updates the game information with the current state of the Tetris game.
     * @param tetris Pointer to the Tetris game instance.
     */
    void updateInfo(Tetris * tetris);

private:
    QLabel *scoreLabel; /**< Label for displaying the score. */
    QLabel *levelLabel; /**< Label for displaying the level. */
    QLabel *linesLabel; /**< Label for displaying the number of lines cleared. */
    QGridLayout *nextShapeLayout; /**< Grid layout for displaying the next shape. */
    int numRows; /**< The number of rows in the game info widget. */
    int numCols; /**< The number of columns in the game info widget. */
};

#endif // GAMEINFOWIDGET_H
