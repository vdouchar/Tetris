#include <chrono>
#include <thread>

#include "Tetris.h"

#include "Direction2D.h"

Tetris::Tetris(bool empty, int level, int rows, int columns) :
    dfBrick(columns),
    bag(Bag::getInstance(dfBrick.defaultBag)),
    currentBrick(std::make_shared<Brick>(bag.getRandomBrick())),
    board(empty,currentBrick,rows,columns)
{
    this->level = level;
    score = 0;
    setSpeed();
    endTime = std::chrono::steady_clock::now() + std::chrono::minutes(15);
}

void Tetris::drop() noexcept {
    unsigned dropCount = 0;
    while(!board.checkCollision(Direction2D::DOWN)){
        dropCount++;
        *currentBrick += Direction2D::DOWN;
        notifyObservers();
    }
    calculateScore(board.clearLines(),dropCount);
    currentBrick = std::make_shared<Brick>(bag.getRandomBrick());
    board.checkOnSpawn();
    notifyObservers();
}

void Tetris::rotate(bool reverse) noexcept {
    if (!board.checkCollisionRotation(reverse)){
        currentBrick->rotate(reverse);
    }
    notifyObservers();
}

bool Tetris::endGame() const noexcept{
    return board.isTopFull() || totalClearedLines >= 250 || score >= 1000000 || std::chrono::steady_clock::now() > endTime;
}

bool Tetris::hasWin() const noexcept{
    //This method is called when the game is ended
    // if the board is top full the game is lost,
    // else the game is win
    return !board.isTopFull();
}

double Tetris::getSpeed() const noexcept{
    return speed;
}

std::string Tetris::to_string() const noexcept {
    std::string scoreStr = std::to_string(score);
    std::string lvlStr = std::to_string(level);
    return "Score : " + scoreStr + "\n" + "level : " + lvlStr + "\n" + board.to_string() + bag.nextBrick();
}

void Tetris::calculateScore(unsigned lines, unsigned drop) noexcept {
    clearedLines += lines;
    totalClearedLines += lines;
    switch (lines){
        case 0:
            score += drop;
            break;
        case 1:
            score += (40*lines+drop) * level;
            break;
        case 2:
            score += (100*lines+drop) * level;
            break;
        case 3:
            score += (300*lines+drop) * level;
            break;
        case 4:
            score += (1200*lines+drop) * level;
            break;
        default:
            //Not possible
            break;
    }
    incrementLevel();
}

void Tetris::incrementLevel() noexcept{
    if (level < 20){
        if (clearedLines >= 10){
            clearedLines = clearedLines % 10;
            level++;
            setSpeed();
        }
    }
}

void Tetris::setSpeed() noexcept{
    switch (level) {
    case 1:
        speed = static_cast<double>(60) / 60;
        break;
    case 2:
        speed = static_cast<double>(53) / 60;
        break;
    case 3:
        speed = static_cast<double>(49) / 60;
        break;
    case 4:
        speed = static_cast<double>(45) / 60;
        break;
    case 5:
        speed = static_cast<double>(41) / 60;
        break;
    case 6:
        speed = static_cast<double>(37) / 60;
        break;
    case 7:
        speed = static_cast<double>(33) / 60;
        break;
    case 8:
        speed = static_cast<double>(28) / 60;
        break;
    case 9:
        speed = static_cast<double>(23) / 60;
        break;
    case 10:
        speed = static_cast<double>(18) / 60;
        break;
    case 11:
        speed = static_cast<double>(13) / 60;
        break;
    case 12:
        speed = static_cast<double>(8) / 60;
        break;
    case 13:
        speed = static_cast<double>(9) / 60;
        break;
    case 14:
        speed = static_cast<double>(8) / 60;
        break;
    case 15:
        speed = static_cast<double>(7) / 60;
        break;
    case 16:
        speed = static_cast<double>(6) / 60;
        break;
    case 17:
        speed = static_cast<double>(5) / 60;
        break;
    case 18:
        speed = static_cast<double>(4) / 60;
        break;
    case 19:
        speed = static_cast<double>(3) / 60;
        break;
    case 20:
        speed = static_cast<double>(2) / 60;
        break;
    default:
        //not possible
        break;
    }
}

int Tetris::getRows() const noexcept {
    return board.getRows();
}

int Tetris::getColumns() const noexcept {
    return board.getColumns();
}

int Tetris::getScore() const noexcept  {
    return score;
}

int Tetris::getLevel() const noexcept {
    return level;
}

int Tetris::getTotalClearedLines() const noexcept {
    return totalClearedLines;
}

int Tetris::getOnBoard(int y, int x) const noexcept {
    return board.get(y,x);
}

int Tetris::getNextShape(int y, int x) const noexcept {
    return bag.nextBrick(y,x);
}

void Tetris::operator+=(const Direction2D& d) noexcept {
    if(d == Direction2D::DOWN){
        if (!board.checkCollision(d)) {
            *currentBrick += d;
        } else {
            calculateScore(board.clearLines());
            currentBrick = std::make_shared<Brick>(bag.getRandomBrick());
            board.checkOnSpawn();
        }
        notifyObservers();
    }else{
        if (!board.checkCollision(d)) {
            *currentBrick += d;
        }
        notifyObservers();
    }
}

std::ostream& operator<<(std::ostream& out, const Tetris& tetris) {
    out << tetris.to_string();
    return out;
}
