#include "Position.h"

Position::Position(int x, int y) : p(std::make_pair(x, y)) {}

int Position::getX() const noexcept {
    return p.first;
}

int Position::getY() const noexcept {
    return p.second;
}

bool Position::operator==(const Position& other) const noexcept {
    return p.first == other.p.first && p.second == other.p.second;
}

bool Position::operator!=(const Position& other) const noexcept {
    return !(*this == other);
}

std::string Position::to_string() const noexcept {
    return "La position {" + std::to_string(p.first) + ", " + std::to_string(p.second) + "}";
}

Position operator+(const Position& pos, const Direction2D& d) noexcept {
    return {pos.getX() + d.x(), pos.getY() + d.y()};
}

std::ostream& operator<<(std::ostream& out, const Position& in) {
    out << in.to_string();
    return out;
}
