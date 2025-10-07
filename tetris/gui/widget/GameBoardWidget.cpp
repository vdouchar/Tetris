#include "GameBoardWidget.h"
#include "CaseWidget.h"

#include "../colors/Color.h"

GameBoardWidget::GameBoardWidget(QHBoxLayout *qhboxlayout, int rows, int columns, QWidget *parent) : QWidget(parent) {
    numRows = rows;
    numCols = columns;

    // Initialize the grid layout for the game board
    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    // Create a widget to contain the grid layout
    QWidget *gridWidget = new QWidget(this);
    gridWidget->setLayout(gridLayout);

    // Create the main layout for the GameBoardWidget and add the gridWidget to it
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(gridWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Center the game board within its parent widget
    mainLayout->setAlignment(Qt::AlignCenter);

    // Calculate the reference cell size based on the parent widget's size and the number of rows and columns
    int refCellSize;
    QSize parentSize = parentWidget()->size();
    (numRows >= numCols ? refCellSize = parentSize.height() / (numRows) : refCellSize = parentSize.width() / (numCols));

    // Create the game board by adding CaseWidget widgets to the grid layout
    for(int y = 0; y < numRows; ++y) {
        for(int x = 0; x < numCols; ++x) {
            CaseWidget *caseWidget = new CaseWidget();

            caseWidget->setFixedSize(refCellSize, refCellSize);
            gridLayout->addWidget(caseWidget, y, x);

            caseWidget->setColor(Color::getColor(0)); // Set the default color of the CaseWidget
        }
    }

    // Add the GameBoardWidget to the provided QHBoxLayout
    qhboxlayout->addWidget(this);
    qhboxlayout->setContentsMargins(0, 0, 0, 0);
    qhboxlayout->setSpacing(0);
    qhboxlayout->setAlignment(Qt::AlignCenter);
}

void GameBoardWidget::updateBoard(Tetris *tetris) {
    // Update the colors of CaseWidget widgets on the game board based on Tetris game state
    for (int y = 0; y < numRows; ++y) {
        for (int x = 0; x < numCols; ++x) {
            CaseWidget *caseWidget = nullptr;

            // Retrieve the CaseWidget widget at position (y, x) in the grid layout
            QWidget *widget = gridLayout->itemAtPosition(y, x)->widget();

            if (widget) {
                // If the widget exists, attempt to cast it to a CaseWidget pointer
                caseWidget = qobject_cast<CaseWidget*>(widget);
            }

            if (caseWidget) {
                // If the CaseWidget pointer is valid, update its color based on Tetris game state
                caseWidget->setColor(Color::getColor(tetris->getOnBoard(y, x)));
            }

        }
    }
}

GameBoardWidget::~GameBoardWidget() {
    //GameBoardWidget destroyed at the end of the program
    std::cout << "Destruct game board" << std::endl;
}
