#ifndef TETRIS_H
#define TETRIS_H

#include <chrono>
#include <thread>

#include "DefaultBrick.h"
#include "Bag.h"
#include "Board.h"

#include "dp/Observable.h"

/*!
 * \brief The TetrisTester class provides helper methods for testing the Tetris class.
 *
 * This class contains methods that facilitate testing of the Tetris class.
 */
class TetrisTester;

/**
 * @brief The Tetris class represents a Tetris game instance.
 *
 * This class manages the state of the Tetris game, including the current brick, the game board,
 * the level, the score, and other game-related functionalities.
 */
class Tetris : public Observable {
private:
    DefaultBrick dfBrick;/**< The default bricks and bag used in the game. */
    Bag& bag; /**< Reference to the bag of bricks for generating random bricks. */
    std::shared_ptr<Brick> currentBrick; /**< Shared Pointer to the current active brick. */
    Board board; /**< The game board where bricks are placed. */
    unsigned level; /**< The current game level. */
    int score; /**< The player's current score. */
    unsigned clearedLines = 0; /**< The number of lines cleared in the current game session. */
    unsigned totalClearedLines = 0; /**< The total number of lines cleared across all game sessions. */
    std::chrono::steady_clock::time_point endTime; /**< Time point when the game ended or paused. */
    double speed; /**< The current speed of the game. */

    /**
     * @brief Calculates the score based on the number of cleared lines and drop count.
     * @param lines The number of lines cleared.
     * @param drop The drop count.
     */
    void calculateScore(unsigned lines,unsigned drop = 0) noexcept;

    /**
     * @brief Increments the game level based on the number of cleared lines.
     */
    void incrementLevel() noexcept;

    /**
     * @brief Sets the game speed based on the current level.
     */
    void setSpeed() noexcept;

public:
    /**
     * @brief Constructs a Tetris game instance.
     * @param empty Flag indicating whether to start with an empty board.
     * @param level Initial game level.
     * @param rows Number of rows on the game board.
     * @param columns Number of columns on the game board.
     * @param Bricks Vector of predefined Bricks for the Bag.
     */
    Tetris(bool empty,int level = 1, int rows = 20, int columns = 10);

    /**
     * @brief Drops the current Brick to the lowest possible position.
     */
    void drop() noexcept;

    /**
     * @brief Rotates the current Brick.
     * @param reverse Flag indicating whether to perform a reverse rotation.
     */
    void rotate(bool reverse) noexcept;

    /**
     * @brief Checks if the game has ended.
     * @return True if the game has ended, false otherwise.
     */
    bool endGame() const noexcept;

    /**
     * @brief hasWin Checks if the game is win or lose
     * @return  True if is it win, false otherwise
     */
    bool hasWin() const noexcept;

    /**
     * @brief Gets a reference to the game speed.
     * @return Reference to the game speed.
     */
    double getSpeed() const noexcept;

    /**
     * @brief Retrieves the number of rows in the Tetris game board.
     *
     * @return The number of rows in the game board.
     */
    int getRows() const noexcept;

    /**
     * @brief Retrieves the number of columns in the Tetris game board.
     *
     * @return The number of columns in the game board.
     */
    int getColumns() const noexcept;

    /**
     * @brief Retrieves the current score in the Tetris game.
     *
     * @return The current score in the game.
     */
    int getScore() const noexcept;

    /**
     * @brief Retrieves the current level of the Tetris game.
     *
     * @return The current level of the game.
     */
    int getLevel() const noexcept;

    /**
     * @brief Retrieves the total number of lines cleared across all game sessions.
     *
     * @return The total number of lines cleared.
     */
    int getTotalClearedLines() const noexcept;

    /**
     * @brief Retrieves the color at the specified position on the game board.
     *
     * @param y The y-coordinate of the position.
     * @param x The x-coordinate of the position.
     * @return The color at the specified position on the board.
     */
    int getOnBoard(int y, int x) const noexcept;

    /**
     * @brief Retrieves the color of the next shape at the specified position.
     *
     * @param y The y-coordinate of the position.
     * @param x The x-coordinate of the position.
     * @return The color of the next shape at the specified position.
     */
    int getNextShape(int y, int x) const noexcept;

    /**
     * @brief Converts the Tetris game state to a string for display.
     * @return String representation of the Tetris game state.
     */
    std::string to_string() const noexcept;

    /**
     * @brief Overloads the += operator to move the current brick by a specified direction.
     * @param d The direction to move the brick.
     */
    void operator+=(const Direction2D& d) noexcept;

    // Declare TetrisTester class as a friend for testing purposes
    friend class TetrisTester;
};

std::ostream& operator<<(std::ostream& out, const Tetris& tetris);


#endif // TETRIS_H
