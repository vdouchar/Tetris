#ifndef POSITION_H
#define POSITION_H

#include <utility>
#include <string>
#include <iostream>

#include "Direction2D.h"

/**
 * @brief The Position class represents a 2D position.
 *
 * This class is used to represent a position in a Cartesian coordinate system
 * with x and y coordinates.
 */
class Position {
    std::pair<int, int> p; /**< The coordinates of the position. */

public:
    /**
     * @brief Default constructor for the Shape class.
     * Allows to default Shape
     */
    Position() = default;

    /**
     * @brief Constructs a Position object with the given x and y coordinates.
     * @param x The x-coordinate of the position.
     * @param y The y-coordinate of the position.
     */
    Position(int x, int y);

    /**
     * @brief Gets the x-coordinate of the position.
     * @return The x-coordinate of the position.
     */
    int getX() const noexcept;

    /**
     * @brief Gets the y-coordinate of the position.
     * @return The y-coordinate of the position.
     */
    int getY() const noexcept;

    /**
     * @brief Equality comparison operator.
     * @param other The Position object to compare with.
     * @return True if the positions are equal, false otherwise.
     */
    bool operator==(const Position& other) const noexcept;

    /**
     * @brief Inequality comparison operator.
     * @param other The Position object to compare with.
     * @return True if the positions are not equal, false otherwise.
     */
    bool operator!=(const Position& other) const noexcept;

    /**
     * @brief Converts the position to a string representation.
     * @return A string representation of the position.
     */
    std::string to_string() const noexcept;
};

/**
 * @brief Addition operator to add a Direction2D to a Position.
 * @param pos The Position to add to.
 * @param d The Direction2D to add.
 * @return A new Position resulting from the addition.
 */
Position operator+(const Position& pos, const Direction2D& d) noexcept;

/**
 * @brief Output stream operator to print a Position.
 * @param out The output stream.
 * @param in The Position to print.
 * @return The output stream.
 */
std::ostream& operator<<(std::ostream& out, const Position& in);

#endif // POSITION_H
