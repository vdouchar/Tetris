#ifndef DIRECTION2D_H
#define DIRECTION2D_H

#include <utility>

/**
 * @brief The Direction2D class represents 2D directions.
 *
 * This class is used to represent 2D directions (UP, DOWN, LEFT, RIGHT)
 * in a Cartesian coordinate system.
 */
class Direction2D {
    const std::pair<int,int> pos; /**< The coordinates of the direction. */
public:

    /**
     * @brief Pre-defined constant for the UP direction.
     */
    static const Direction2D UP;

    /**
     * @brief Pre-defined constant for the DOWN direction.
     */
    static const Direction2D DOWN;

    /**
     * @brief Pre-defined constant for the LEFT direction.
     */
    static const Direction2D LEFT;

    /**
     * @brief Pre-defined constant for the RIGHT direction.
     */
    static const Direction2D RIGHT;

    /**
     * @brief Constructs a Direction2D object with the given x and y coordinates.
     * @param x The x-coordinate of the direction.
     * @param y The y-coordinate of the direction.
     */
    Direction2D(int x, int y);

    /**
     * @brief Equality comparison operator.
     * @param other The Direction2D object to compare with.
     * @return True if the Directions are equal, false otherwise.
     */
    bool operator==(const Direction2D& other) const noexcept;

    /**
     * @brief Gets the x-coordinate of the direction.
     * @return The x-coordinate of the direction.
     */
    int x() const noexcept;

    /**
     * @brief Gets the y-coordinate of the direction.
     * @return The y-coordinate of the direction.
     */
    int y() const noexcept;
};

#endif // DIRECTION2D_H
