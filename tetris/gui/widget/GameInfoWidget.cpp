#include "GameInfoWidget.h"
#include "CaseWidget.h"

#include "../colors/Color.h"

GameInfoWidget::GameInfoWidget(QHBoxLayout *layout, int score, int level, int lines, QWidget *parent)
    : QWidget(parent)
{
    // Create a QVBoxLayout to organize widgets vertically
    QVBoxLayout *vBoxLayout = new QVBoxLayout(this);

    // Create three labels to display the score, level, and number of lines
    scoreLabel = new QLabel("Score: \n" + QString::number(score));
    levelLabel = new QLabel("Level: \n" + QString::number(level));
    linesLabel = new QLabel("Lines: \n" + QString::number(lines));

    // Define a CSS style sheet for all labels
    QString labelStyleSheet =
        "QLabel { border: 2px solid black;"
        " border-radius: 10px;"
        " font-weight: bold;"
        " padding: 5px; }";

    // Apply the CSS style sheet to each label
    scoreLabel->setStyleSheet(labelStyleSheet);
    levelLabel->setStyleSheet(labelStyleSheet);
    linesLabel->setStyleSheet(labelStyleSheet);

    // Center the text in each label
    scoreLabel->setAlignment(Qt::AlignCenter);
    levelLabel->setAlignment(Qt::AlignCenter);
    linesLabel->setAlignment(Qt::AlignCenter);

    // Define the number of rows and columns for the grid
    numRows = 3;
    numCols = 4;

    // Create a QGridLayout to organize widgets in the grid
    nextShapeLayout = new QGridLayout();
    nextShapeLayout->setSpacing(0); // Remove spacing between widgets in the grid
    nextShapeLayout->setContentsMargins(0, 0, 0, 0); // Remove margins around the grid

    // Create a widget to contain the grid
    QWidget *gridWidget = new QWidget();
    gridWidget->setLayout(nextShapeLayout); // Assign the QGridLayout to the grid widget

    // Create a QVBoxLayout to organize the main widgets of the window
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(gridWidget); // Add the grid widget to the main QVBoxLayout
    mainLayout->setContentsMargins(0, 0, 0, 0); // Remove margins around the main QVBoxLayout
    mainLayout->setSpacing(0); // Remove spacing between widgets in the main QVBoxLayout

    // Calculate the size of each cell in the grid based on the parent size
    int refCellSize;
    QSize parentSize = parentWidget()->size();
    (numRows >= numCols ? refCellSize = parentSize.height() / numRows : refCellSize = parentSize.width() / numCols);

    // Create and configure CaseWidget widgets for each cell in the grid
    for(int i = 0; i < numRows; ++i) {
        for(int j = 0; j < numCols; ++j) {
            CaseWidget *caseWidget = new CaseWidget();

            // Set the fixed size of each CaseWidget
            caseWidget->setFixedSize(refCellSize / 4, refCellSize / 4);

            // Add the CaseWidget to the grid
            nextShapeLayout->addWidget(caseWidget, i, j);

            // Set the default color for the CaseWidget
            caseWidget->setColor(Color::getColor(0));
        }
    }

    // Add the labels and the grid widget to the main QVBoxLayout
    vBoxLayout->addWidget(scoreLabel);
    vBoxLayout->addWidget(levelLabel);
    vBoxLayout->addWidget(linesLabel);
    vBoxLayout->addWidget(gridWidget);

    // Add the GameInfoWidget widget to the provided QHBoxLayout
    layout->addWidget(this);
}

void GameInfoWidget::updateInfo(Tetris * tetris) {
    // Update the text of the labels with the current score, level, and total cleared lines
    scoreLabel->setText("Score: \n" + QString::number(tetris->getScore()));
    levelLabel->setText("Level: \n" + QString::number(tetris->getLevel()));
    linesLabel->setText("Lines: \n" + QString::number(tetris->getTotalClearedLines()));


    // Update the color of CaseWidget widgets in the grid based on the next shape of the Tetris game
    for (int y = 0; y < numRows; ++y) {
        for (int x = 0; x < numCols; ++x) {
            CaseWidget *caseWidget = nullptr;

            // Get the widget at the specified position in the grid layout
            QWidget *widget = nextShapeLayout->itemAtPosition(y, x)->widget();

            // Check if the widget exists and is of type CaseWidget
            if (widget) {
                caseWidget = qobject_cast<CaseWidget*>(widget);
            }

            // If the widget is a CaseWidget, update its color based on the next shape in the Tetris game
            if (caseWidget) {
                caseWidget->setColor(Color::getColor(tetris->getNextShape(y, x)));
            }
        }
    }
}

GameInfoWidget::~GameInfoWidget() {
    //Game info destroyed at the end of the program
    std::cout << "Destruct info" << std::endl;
}
