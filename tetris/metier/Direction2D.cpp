#include "Direction2D.h"

const Direction2D Direction2D::UP(0, -1);    //inversé à cause de l'orientation du vecteur dans Board
const Direction2D Direction2D::DOWN(0, 1);   //inversé à cause de l'orientation du vecteur dans Board
const Direction2D Direction2D::LEFT(-1, 0);
const Direction2D Direction2D::RIGHT(1, 0);

Direction2D::Direction2D(int x, int y) : pos(std::make_pair(x,y)) {}

bool Direction2D::operator==(const Direction2D& other) const noexcept{
    return pos.first == other.pos.first && pos.second == other.pos.second;
}

int Direction2D::x() const noexcept{
    return pos.first;
}

int Direction2D::y() const noexcept{
    return pos.second;
}
