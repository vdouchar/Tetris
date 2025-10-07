#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widget/GameBoardWidget.h"

#include <QMessageBox>

MainWindow::MainWindow(Tetris* subject,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    subject_ { subject }
{
    ui->setupUi(this);

    subject_->registerObserver(this);

    setWindowTitle("Tetris");

    // Create the game board
    gameBoardWidget = new GameBoardWidget(ui->horizontalLayout,subject_->getRows(),subject_->getColumns(),this);
    // Create the game info widget
    gameInfoWidget = new GameInfoWidget(ui->horizontalLayout,subject_->getScore(),subject_->getLevel(),subject_->getTotalClearedLines(),this);

    setCentralWidget(ui->horizontalLayoutWidget);
}

MainWindow::~MainWindow()
{
    std::cout << "destruct mainwindow" << std::endl;
    delete ui;
    delete gameBoardWidget;
    delete gameInfoWidget;
}

void MainWindow::update(){
    // Update the game board and game info widget with the latest Tetris game state
    gameBoardWidget->updateBoard(subject_);
    gameInfoWidget->updateInfo(subject_);

    if (subject_->endGame() && !gameOverMessageBoxDisplayed){
        gameOverMessageBoxDisplayed = true;
        std::string mess = "Malheureusement, vous avez perdu !";

        if(subject_ ->hasWin()) {
            mess = "Bravo, vous avez gagné !";
        }

        QMessageBox::information(this, "Game Over",QString(mess.c_str()));
    }
}
