#include <iostream>
#include "configwindow.h"
#include "ui_configwindow.h"

#include "mainwindow.h"
#include "TetrisController.h"
#include "../metier/Tetris.h"

ConfigWindow::ConfigWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigWindow)
{
    ui->setupUi(this);

    setWindowTitle("Tetris config game");

    // Set initial styles for error labels
    ui->colErr->setStyleSheet("color: red;");
    ui->rowErr->setStyleSheet("color: red;");
    ui->lvlErr->setStyleSheet("color: red;");

    // Hide error labels initially
    ui->colErr->hide();
    ui->rowErr->hide();
    ui->lvlErr->hide();

    // Set Placeholders to edits
    ui->lvlEdit->setPlaceholderText("Min : 1, Max : 20");
    ui->colEdit->setPlaceholderText("Min : 5, Max : 100");
    ui->rowEdit->setPlaceholderText("Min : 5, Max : 100");

    // Set default values for level, rows, and columns inputs
    ui->lvlEdit->setText("1");
    ui->colEdit->setText("10");
    ui->rowEdit->setText("20");
}

ConfigWindow::~ConfigWindow()
{
    // Destructor for ConfigWindow
    std::cout << "destruct configwindow" << std::endl;
    delete ui;
    delete tetris;
    delete ttctrl;
    delete gameWindow;
}

void ConfigWindow::on_submitBtn_clicked()
{
    // Hide error labels initially
    ui->colErr->hide();
    ui->rowErr->hide();
    ui->lvlErr->hide();

    bool startGame = true; // Flag to indicate whether to start the game

    // Variables to store level, rows, and columns input values
    bool lvl = true, row = true, col = true;
    int level = ui->lvlEdit->text().toInt(&lvl);
    int rows = ui->rowEdit->text().toInt(&row);
    int cols = ui->colEdit->text().toInt(&col);

    // Validate level input
    if (!lvl || level < 1 || level > 20) {
        ui->lvlErr->show();
        if(ui->lvlEdit->text().isEmpty() ){
            ui->lvlErr->setText("Aucune entrée");
        } else {
            ui->lvlErr->setText("Entrée incorrecte");
        }
        startGame = false;
    }

    // Validate rows input
    if (!row || rows < 5 || rows > 100) {
        ui->rowErr->show();
        if(ui->rowEdit->text().isEmpty() ){
            ui->rowErr->setText("Aucune entrée");
        } else {
            ui->rowErr->setText("Entrée incorrecte");
        }
        startGame = false;
    }

    // Validate columns input
    if (!col || cols < 5 || cols > 100) {
        ui->colErr->show();
        if(ui->colEdit->text().isEmpty() ){
            ui->colErr->setText("Aucune entrée");
        } else {
            ui->colErr->setText("Entrée incorrecte");
        }
        startGame = false;
    }

    // Additional validation and error messages

    if (lvl && (level < 1 || level > 20)) {
        ui->lvlErr->setText("Le level doit être compris entre 1 et 20");
        startGame = false;
    }

    if (row && (rows < 5 || rows > 100)) {
        ui->rowErr->setText("Le nombre de lignes doit être compris entre 5 et 100");
        startGame = false;
    }

    if (col && (cols < 5 || cols > 100)) {
        ui->colErr->setText("Le nombre de colonnes doit être compris entre 5 et 100");
        startGame = false;
    }

    // Start the game if all inputs are valid
    if (startGame){
        tetris = new Tetris(!ui->fillGrid->isChecked(), level, rows, cols);
        ttctrl = new TetrisController(*tetris);

        gameWindow = new MainWindow(tetris);

        gameWindow->installEventFilter(ttctrl);
        gameWindow->setStyleSheet("background-color: #D3D3D3;");
        gameWindow->show();
        gameWindow->setFocus();

        this->close();

        ttctrl->startGame();

    }
}
