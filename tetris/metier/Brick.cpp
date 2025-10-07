#include <algorithm>

#include "Brick.h"
#include "Position.h"

Brick::Brick(const std::vector<Position>& initialPositions, const Position& center, int color)
    : positions(initialPositions), center(center), color(color) {}

std::vector<Position> Brick::getPositions() const noexcept{
    return positions;
}

void Brick::rotate(bool reverse) noexcept{
    // If the Brick is a CBrick, do not rotate
    //Positions are known because of initialization in dfBricks
    if (positions.size() == 4 &&
        positions[0].getX() == center.getX() - 1 && positions[0].getY() == center.getY() &&
        positions[1].getX() == center.getX() - 1 && positions[1].getY() == center.getY() + 1 &&
        positions[2].getX() == center.getX() && positions[2].getY() == center.getY() + 1 &&
        positions[3].getX() == center.getX() && positions[3].getY() == center.getY())
    {
        return;
    }

    std::vector<Position> newPositions;
    for (Position& pos : positions) {
        if(pos != center){
            int x = pos.getX();
            int y = pos.getY();

            int newX = reverse ? center.getX() + (y - center.getY()) : center.getX() - (y - center.getY());
            int newY = reverse ? center.getY() - (x - center.getX()) : center.getY() + (x - center.getX());

            newPositions.push_back(Position(newX,newY));
        }else{
            newPositions.push_back(center);
        }
    }
    positions = newPositions;
}

int Brick::getColor() const noexcept{
    return color;
}

bool Brick::operator==(const Brick& other) const noexcept{
    return (positions == other.positions) && (center == other.center) && (color == other.color);
}

bool Brick::operator!=(const Brick& other) const noexcept{
    return !(*this == other);
}

void Brick::operator+=(const Direction2D& direction) noexcept {
    for (Position& position : positions) {
        position = position + direction;
    }
    center = center + direction;
}

std::string Brick::to_string() const noexcept{

    auto findMinMaxXY = [&]() {
        int minX = positions[0].getX();
        int minY = positions[0].getY();
        int maxX = positions[0].getX();
        int maxY = positions[0].getY();

        for (const Position& pos : positions) {
            minX = std::min(minX, pos.getX());
            minY = std::min(minY, pos.getY());
            maxX = std::max(maxX, pos.getX());
            maxY = std::max(maxY, pos.getY());
        }

        return std::make_tuple(minX, minY, maxX, maxY);
    };

    int minX, minY, maxX, maxY;
    std::tie(minX, minY, maxX, maxY) = findMinMaxXY();

    // Construction de la représentation textuelle de la forme
    std::string result;
    for (int y = minY; y <= maxY; ++y) {
        for (int x = minX; x <= maxX; ++x) {
            Position currentPos(x, y);
            if (std::find(positions.begin(), positions.end(), currentPos) != positions.end()) {
                // La position fait partie de la forme
                result += getAssociatedChar(color);
            } else {
                // La position n'est pas dans la forme
                result += ' ';
            }
        }
        result += '\n';  // Nouvelle ligne après chaque ligne de la forme
    }

    return result;
}

int Brick::getAtPos(int y, int x) const noexcept {
    // Trouvez la position minimale de la brique par rapport au jeu
    int minX = positions[0].getX();
    int minY = positions[0].getY();
    for (const Position& pos : positions) {
        minX = std::min(minX, pos.getX());
        minY = std::min(minY, pos.getY());
    }

    // Translatez les coordonnées (y, x) du jeu pour correspondre à la position de la brique
    int translatedX = x + minX;
    int translatedY = y + minY;

    // Vérifiez si la position correspond à une partie de la brique
    for (const Position& pos : positions) {
        if (pos.getX() == translatedX && pos.getY() == translatedY) {
            return this->color; // La position est occupée par la brique
        }
    }
    // La position n'est pas occupée par la brique
    return 0;
}

char Brick::getAssociatedChar(int color) noexcept{
    switch (color) {
    case 0:
        return ' ';
    case 1:
        return '@';
    case 2:
        return '$';
    case 3:
        return '=';
    case 4:
        return '%';
    case 5:
        return '~';
    case 6:
        return '&';
    case 7:
        return '-';
    default:
        //bug if displayed
        return '?';
    }
}
