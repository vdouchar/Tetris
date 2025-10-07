#ifndef DEFAULTBRICK_H
#define DEFAULTBRICK_H

#include "Brick.h"

#include <vector>

/**
 * @brief The defaultBrick class represents all default bricks of the game
 *
 * This class is used to represent all default bricks of the game
 * with the absolute positions on the board
 */
class DefaultBrick {
public:
    /**
     * @brief Constructs a DefaultBrick object with the given width.
     * @param width The width of the game board.
     */
    DefaultBrick(int width);

    Brick TBrick; /**< The T-shaped Brick. */
    Brick CBrick; /**< The C-shaped Brick. */
    Brick SBrick; /**< The S-shaped Brick. */
    Brick LBrick; /**< The L-shaped Brick. */
    Brick JBrick; /**< The J-shaped Brick. */
    Brick IBrick; /**< The I-shaped Brick. */
    Brick ZBrick; /**< The Z-shaped Brick. */
    std::vector<Brick> defaultBag; /**< The bag containing all default bricks. */

private:
    int center; /**< The center position of the board. */
};

#endif // DEFAULTBRICK_H
