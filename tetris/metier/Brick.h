#ifndef BRICK_H
#define BRICK_H

#include <iostream>
#include <vector>
#include <memory>

#include "Position.h"

/*!
 * \brief The BrickTester class provides helper methods for testing the Brick class.
 *
 * This class contains methods that facilitate testing of the Brick class.
 */
class BrickTester;

/**
 * @brief The Brick class represents a geometric Brick in a 2D space.
 *
 * This class represents a Brick composed of positions in a 2D space, with a center and a color.
 */
class Brick {
    std::vector<Position> positions; /**< The positions that make up the Brick. */
    Position center; /**< The center position of the Brick. */
    int color; /**< The color of the Brick. */

public:
    /**
     * @brief Default constructor for the Brick class.
     * Allows to avoid construction of Bricks in defaultBricks
     * with initialization lists
     */
    Brick() = default;

    /**
     * @brief Constructs a Brick object with the given initial positions, center, and color.
     * @param initialPositions The initial positions of the Brick.
     * @param center The center position of the Brick.
     * @param color The color of the Brick.
     */
    Brick(const std::vector<Position>& initialPositions, const Position& center, int color);

    /**
     * @brief Copy constructor for the Brick class.
     * @param Brick The Brick to copy.
     */
    Brick(const Brick& Brick) = default;

    /**
     * @brief Destructor for the Brick class.
     */
    ~Brick() = default;

    /**
     * @brief Gets the color of the Brick.
     * @return The color of the Brick.
     */
    int getColor() const noexcept;

    /**
     * @brief Rotates the Brick.
     * @param rotate to the left or rotate to the right
     */
    void rotate(bool reverse) noexcept;

    /**
     * @brief Gets the positions that make up the Brick.
     * @return A vector of positions representing the Brick.
     */
    std::vector<Position> getPositions() const noexcept;

    /**
     * @brief Overloaded equality operator for comparing two bricks.
     * @param other The other Brick to compare.
     * @return True if the bricks are equal, false otherwise.
     */
    bool operator==(const Brick& other) const noexcept;

    /**
     * @brief Overloaded inequality operator for comparing two bricks.
     * @param other The other Brick to compare.
     * @return True if the bricks are not equal, false otherwise.
     */
    bool operator!=(const Brick& other) const noexcept;

    /**
     * @brief Moves the brick in a specified direction using the '+=' operator.
     *
     * This function overloads the '+=' operator to move the brick in a specified direction.
     *
     * @param direction The direction in which to move the brick.
     */
    void operator+=(const Direction2D& d) noexcept;

    /**
     * @brief Retrieves the color at the specified position of the Brick.
     *
     * @param y The y-coordinate of the position.
     * @param x The x-coordinate of the position.
     * @return The color at the specified position.
     */
    int getAtPos(int y, int x) const noexcept;

    /**
     * @brief Converts the Brick to a string representation.
     * @return A string representation of the Brick.
     */
    std::string to_string() const noexcept;

    /**
     * @brief Gets the character associated with the Brick's color.
     * @param color The color of the Brick.
     * @return The character associated with the color.
     */
    static char getAssociatedChar(int color) noexcept;

    // Declare BrickTester class as a friend for testing purposes
    friend class BrickTester;
};

#endif // BRICK_H
