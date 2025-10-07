#include <iostream>

#include "Board.h"

#include "Position.h"
#include "Brick.h"
#include "Direction2D.h"
#include "Random.hpp"

int minMaxXY(bool min, bool x, std::vector<Position>& positions) {
    if (x) {
        int row = positions[0].getX();
        if (min) {
            for (const Position& posX : positions) {
                if (row > posX.getX()) {
                    row = posX.getX();
                }
            }
            return row;
        } else {
            for (const Position& posX : positions) {
                if (row < posX.getX()) {
                    row = posX.getX();
                }
            }
            return row;
        }
    } else {
        int column = positions[0].getY();
        if (min) {
            for (const Position& posY : positions) {
                if (column > posY.getY()) {
                    column = posY.getY();
                }
            }
            return column;
        } else {
            for (const Position& posY : positions) {
                if (column < posY.getY()) {
                    column = posY.getY();
                }
            }
            return column;
        }
    }
}

Board::Board(bool empty, std::shared_ptr<Brick>& brick, int rows, int columns) : matrix(rows, std::vector<int>(columns, 0)), brick(brick) {
    this->rows = rows;
    this->columns = columns;
    if (!empty){
        for (int i = rows * 3 / 4; i < rows; ++i){
            for (int j = 0; j < columns; ++j){
                //75% chance the position is filled in the board
                int probability = random_value<int>(1,4);
                if(probability != 2){
                    matrix[i][j] = random_value<int>(1,7);
                }else{
                    matrix[i][j] = 0;
                }
            }
        }
    }
}

bool Board::checkCollision(const Direction2D& direction) {
    std::shared_ptr<Brick> otherBrick = std::make_shared<Brick>(Brick(*brick));
    *otherBrick += direction;
    std::vector<Position> positions = otherBrick->getPositions();

    for (const Position& position : positions) {
        if(checkOutOfBounds(position.getX(),position.getY())){
            if (position.getY() == rows){
                fixOnMatrix();
            }
            return true; // collision detected
        }
    }

    for (const Position& pos : positions) {
        if (matrix[pos.getY()][pos.getX()] != 0) {
            if (direction == Direction2D::DOWN){
                fixOnMatrix();
            }
            return true;  // collision detected
        }
    }

    return false;  // No collision detected
}

bool Board::checkCollisionRotation(bool reverse) {
    std::shared_ptr<Brick> otherBrick = std::make_shared<Brick>(Brick(*brick));
    otherBrick->rotate(reverse);
    std::vector<Position> positions = otherBrick->getPositions();
    for (Position position : positions) {
        if (position.getX() < 0) {
            int decal = minMaxXY(true, true, positions);
            unsigned nbDecal = 0;

            while (decal != -1) {
                decal++;
                *otherBrick += Direction2D::RIGHT;
                nbDecal++;
            }

            if (checkCollision(Direction2D::RIGHT, otherBrick)) {
                return true; // Collision detected with move
            }

            for (unsigned i = 0; i <= nbDecal; i++) {
                *brick += Direction2D::RIGHT;
            }

            return false; // No collision detected + move
        }
        if (position.getX() > columns - 1) {
            int decal = minMaxXY(false, true, positions);
            unsigned nbDecal = 0;

            while (decal != columns) {
                decal--;
                *otherBrick += Direction2D::LEFT;
                nbDecal++;
            }

            if (checkCollision(Direction2D::LEFT, otherBrick)) {
                return true; // Collision detected with move
            }


            for (unsigned i = 0; i <= nbDecal; i++) {
                *brick += Direction2D::LEFT;
            }

            return false; // No collision detected + move
        }
        if (position.getY() > rows - 1) {
            int decal = minMaxXY(false, false, positions);
            unsigned nbDecal = 0;

            while (decal != rows) {
                decal--;
                *otherBrick += Direction2D::UP;
                nbDecal++;
            }

            if (checkCollision(Direction2D::UP, otherBrick)) {
                return true; // Collision detected with move
            }


            for (unsigned i = 0; i <= nbDecal; i++) {
                *brick += Direction2D::UP;
            }
            return false; // No collision detected + move
        }
        if (position.getY() >= 0) {
            if (matrix[position.getY()][position.getX()] != 0) {
                return true;
            }
        }
    }
    return false; // No collision detected
}

void Board::checkOnSpawn(){
    //Allows to push the brick at a higher position
    //where it can spawn
    bool movedUp = true;
    while (movedUp) {
        movedUp = false;
        for (Position& pos : brick->getPositions()) {
            if (pos.getY() < 0) {
                continue;
            }
            if (matrix[pos.getY()][pos.getX()] != 0) {
                *brick += Direction2D::UP;
                movedUp = true;
                break; // Sortir de la boucle interne après chaque déplacement vers le haut
            }
        }
    }
}

bool Board::isTopFull() const{
    //If any y position of the brick is 0 or more,
    //we can place the brick and the top isnt full
    for (Position pos : brick->getPositions()){
        if (pos.getY() >= 0){
            return false;
        }
    }
    return true;
}

unsigned Board::clearLines() {
    unsigned clearedLines = 0;
    for (int i = rows - 1; i >= 0; --i) {
        while (isLineComplete(i)) {
            clearedLines++;
            clearLine(i);
            moveLinesDown(i);
        }
    }
    return clearedLines;
}

void Board::fixOnMatrix() {
    for (Position pos : brick->getPositions()) {
        if (pos.getY() >= 0){
            matrix[pos.getY()][pos.getX()] = brick->getColor();
        }
    }
}

int Board::get(int y, int x) const noexcept {
    if (matrix[y][x]== 0){
        for (Position pos : brick->getPositions()) {
            if (pos.getY() == y && pos.getX() == x){
                return brick->getColor();
            }
        }
    }
    return matrix[y][x];
}

int Board::getRows() const noexcept {
    return rows;
}

int Board::getColumns() const noexcept {
    return columns;
}

std::string Board::to_string() const {
    std::string result;

    // Display of board with bricks
    for (int i = 0; i < rows; ++i) {
        result += "*";
        for (int j = 0; j < columns; ++j) {
            bool isBrickPosition = false;

            // Verify if the position is occupied
            for (const Position& pos : brick->getPositions()) {
                if (pos.getX() == j && pos.getY() == i) {
                    char associatedChar = brick->getAssociatedChar(brick->getColor());
                    result += std::string(1, associatedChar);
                    isBrickPosition = true;
                    break;
                }
            }

            if (!isBrickPosition) {
                char matrixChar = brick->getAssociatedChar(matrix[i][j]);
                result += std::string(1, matrixChar);
            }
            result += " ";
        }
        result += "*\n";
    }

    result += "* ";
    for (int i = 0; i < columns; ++i) {
        result += "* ";
    }
    result += "\n";
    return result;
}

bool Board::isLineComplete(int row) const {
    for (int j = 0; j < columns; ++j) {
        if (matrix[row][j] == 0) {
            return false;  // The line is not complete
        }
    }
    return true;  // The line is complete
}

void Board::clearLine(int row) {
    for (int j = 0; j < columns; ++j) {
        matrix[row][j] = 0;  // Erase the ligne
    }
}

void Board::moveLinesDown(int clearedRow) {
    for (int i = clearedRow - 1; i >= 0; --i) {
        for (int j = 0; j < columns; ++j) {
            matrix[i + 1][j] = matrix[i][j];  // Drop rows
        }
    }
}

bool Board::checkCollision(const Direction2D& direction, std::shared_ptr<Brick> other) const {
    *other += direction;
    std::vector<Position> positions = other->getPositions();

    for (const Position& position : positions) {
        if(checkOutOfBounds(position.getX(),position.getY())){
            return true; // collision detected
        }
    }

    return checkCollision(other);
}

bool Board::checkCollision(std::shared_ptr<Brick> other) const {
    std::vector<Position> positions = other->getPositions();

    for (const Position& pos : positions) {
        if (matrix[pos.getY()][pos.getX()] != 0) {
            return true;  // Collision detected with another brick
        }
    }

    return false;  // No collision detected
}

bool Board::checkOutOfBounds(int x, int y) const noexcept {
    return x < 0 || y < 0 || x > columns - 1 || y > rows - 1;
}

std::ostream& operator<<(std::ostream& out, const Board& board) {
    out << board.to_string();
    return out;
}
