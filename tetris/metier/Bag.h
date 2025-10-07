#ifndef BAG_H
#define BAG_H

#include <vector>
#include <memory>
#include <string>

#include "Brick.h"

/*!
 * \brief The BagTester class provides helper methods for testing the Bag class.
 *
 * This class contains methods that facilitate testing of the Bag class.
 */
class BagTester;

/**
 * @brief The Bag class represents a bag of Tetris Bricks.
 *
 * This class manages a bag containing Tetris Bricks and provides methods to get random Bricks.
 */
class Bag {
private:
    std::vector<Brick> bricks; /**< The vector of Tetris Bricks stored in the bag. */
    unsigned current; /**< The index of the current brick being drawn from the bag. */
    Brick nextbrick; /**< The next Tetris Brick to be drawn from the bag. */

    /**
     * @brief Constructs a Bag object with the given vector of Bricks.
     * @param BricksParam The vector of Tetris Bricks to initialize the bag with.
     */
    Bag(std::vector<Brick> bricksParam);

    /**
     * @brief Shuffles the Bricks in the bag.
     */
    void shuffle();

public:

    /**
     * @brief Gets the singleton instance of the Bag class.
     * @param Bricks The vector of Tetris Bricks to initialize the bag with (default is the defaultBag).
     * @return The singleton instance of the Bag class.
     */
    static Bag& getInstance(std::vector<Brick> bricks);

    /**
     * @brief Gets a random Tetris Brick from the bag.
     * @return A random Tetris Brick.
     */
    Brick getRandomBrick();

    /**
     * @brief Gets the string representation of the next Tetris Brick in the bag.
     * @return The string representation of the next Tetris Brick.
     */
    std::string nextBrick();

    /**
     * @brief Gets the Color of the next Tetris Brick at the specified position in a 3X4 matrix.
     *
     * This function returns the Color of the next Tetris Brick that would be drawn from the bag
     * if it were to be placed at the specified position in the game board.
     *
     * @param y The y-coordinate of the position.
     * @param x The x-coordinate of the position.
     * @return The Color of the next Tetris Brick.
     */
    int nextBrick(int y, int x);

    // Declare BagTester class as a friend for testing purposes
    friend class BagTester;
};

#endif // BAG_H
