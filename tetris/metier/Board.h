#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

#include "Brick.h"

/*!
 * \brief The BoardTester class provides helper methods for testing the Board class.
 *
 * This class contains methods that facilitate testing of the Board class.
 */
class BoardTester;

/**
 * @brief The Board class represents the Tetris game board.
 *
 * This class manages the Tetris game board, including collision detection, line clearing, and matrix manipulation.
 */
class Board {
    int rows; /**< The number of rows in the board. */
    int columns; /**< The number of columns in the board. */
    std::vector<std::vector<int> > matrix; /**< The matrix representing the board. */
    std::shared_ptr<Brick>& brick; /**< A reference to the current Tetris Brick on the board. */

public:
    /**
     * @brief Constructs a Board object.
     * @param empty Flag indicating whether to initialize the board as empty.
     * @param Brick A reference to the current Tetris Brick on the board.
     * @param rows The number of rows in the board (default is 20).
     * @param columns The number of columns in the board (default is 10).
     */
    Board(bool empty, std::shared_ptr<Brick>& brick, int rows = 20, int columns = 10);

    /**
     * @brief Checks for collision with the given direction.
     * @param direction The direction to check for collision.
     * @return True if there is a collision, false otherwise.
     */
    bool checkCollision(const Direction2D& direction);

    /**
     * @brief Checks for collision after rotation.
     * @param reverse Flag indicating whether to rotate in reverse.
     * @return True if there is a collision, false otherwise.
     */
    bool checkCollisionRotation(bool reverse);

    /**
     * @brief Checks if the current Brick is at the top of the board during spawn.
     *
     * If the current Brick is partially or fully above the top row of the board,
     * it moves the Brick down until it's no longer above the top row.
     */
    void checkOnSpawn();

    /**
     * @brief Checks if the top row of the board is full.
     * @return True if the top row is full, false otherwise.
     */
    bool isTopFull() const;

    /**
     * @brief Clears complete lines from the board and returns the number of lines cleared.
     * @return The number of lines cleared.
     */
    unsigned clearLines();

    /**
     * @brief Retrieves the color at the specified coordinates on the game board.
     *
     * @param y The y-coordinate of the position.
     * @param x The x-coordinate of the position.
     * @return The color at the specified position.
     */
    int get(int y, int x) const noexcept;

    /**
     * @brief Gets the number of rows in the game board.
     *
     * @return The number of rows in the game board.
     */
    int getRows() const noexcept;

    /**
     * @brief Gets the number of columns in the game board.
     *
     * @return The number of columns in the game board.
     */
    int getColumns() const noexcept;

    /**
     * @brief Gets the string representation of the board.
     * @return The string representation of the board.
     */
    std::string to_string() const;

private:
    /**
     * @brief Fixes the current Brick on the board.
     */
    void fixOnMatrix();

    /**
     * @brief Checks if a line is complete.
     * @param row The row index to check.
     * @return True if the line is complete, false otherwise.
     */
    bool isLineComplete(int row) const;

    /**
     * @brief Clears a complete line from the board.
     * @param row The row index to clear.
     */
    void clearLine(int row);

    /**
     * @brief Moves down the lines above the cleared row.
     * @param clearedRow The index of the cleared row.
     */
    void moveLinesDown(int clearedRow);

    /**
     * @brief Checks for collision with another Brick.
     * @param direction The direction to check for collision.
     * @param other The other Tetris Brick.
     * @return True if there is a collision, false otherwise.
     */
    bool checkCollision(const Direction2D& direction,std::shared_ptr<Brick> other) const;

    /**
     * @brief Checks for collision with another Brick.
     * @param other The other Tetris Brick.
     * @return True if there is a collision, false otherwise.
     */
    bool checkCollision(std::shared_ptr<Brick> other) const;

    /**
     * @brief Checks if the given coordinates are out of bounds of the game board.
     * @param x The x-coordinate to check.
     * @param y The y-coordinate to check.
     * @return True if the coordinates are out of bounds, false otherwise.
     */
    bool checkOutOfBounds(int x, int y) const noexcept;

    // Declare BoardTester class as a friend for testing purposes
    friend class BoardTester;
};

/**
 * @brief Overloaded stream insertion operator to output the board.
 * @param out The output stream.
 * @param board The Board object to output.
 * @return The output stream.
 */
std::ostream& operator<<(std::ostream& out, const Board& board);

#endif // BOARD_H
