#include "ConsoleTetrisObserver.h"
#include "../../metier//Tetris.h"

#include <iostream>

ConsoleTetrisObserver::ConsoleTetrisObserver(Tetris* subject) :
    subject_ { subject }
{
    subject_->registerObserver(this);
}

ConsoleTetrisObserver::~ConsoleTetrisObserver(){
    subject_->unregisterObserver(this);
}

void ConsoleTetrisObserver::update(){
    if(!subject_->endGame()){
        std::cout << *subject_ << std::endl;
    }else{
        subject_->hasWin() ?
            std::cout << "\nCongrats, you have won the game !" << std::endl :
            std::cout << "\nUnfortunately, you have losed the game !" << std::endl;
    }
}
