#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "../metier/Board.h"

class BoardTester {
public:
    static std::vector<std::vector<int>>& getMatrix(Board& board) { return board.matrix; }
    static bool isLineComplete(Board& board, int row) { return board.isLineComplete(row); }
};

TEST_CASE("Board initialization", "[Board]") {
    std::shared_ptr<Brick> brick = std::make_shared<Brick>();
    Board board(true, brick, 20, 10);

    REQUIRE(BoardTester::getMatrix(board).size() == 20);
    REQUIRE(BoardTester::getMatrix(board)[0].size() == 10);

    // Check if board is initialized as empty
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 10; ++j) {
            REQUIRE(BoardTester::getMatrix(board)[i][j] == 0);
        }
    }
}

TEST_CASE("Board collision detection", "[Board]") {
    std::shared_ptr<Brick> brick;

    // Create a brick at the top of the board
    std::vector<Position> positions = {{5, 0}, {6, 0}, {5, 1}, {6, 1}};
    brick = std::make_shared<Brick>(positions, Position(5, 0), 1);

    Board board(true, brick, 20, 10);

    // make a drop
    while (!board.checkCollision(Direction2D::DOWN)) {
        *brick += Direction2D::DOWN;
    }

    // Check if collision with the bottom of the board is detected
    REQUIRE(board.checkCollision(Direction2D::DOWN));

    // Rotate the brick until it collides with the right wall of the board
    while (!board.checkCollisionRotation(false)) {
        brick->rotate(false);
    }

    // Check if collision with the right wall of the board is detected after rotation
    REQUIRE(board.checkCollisionRotation(false));
}

TEST_CASE("Board line clearing", "[Board]") {
    std::shared_ptr<Brick> brick = std::make_shared<Brick>();
    Board board(true, brick, 20, 10);

    // Fill the top row of the board
    for (int j = 0; j < 10; ++j) {
        BoardTester::getMatrix(board)[0][j] = 1;
    }

    // Check if the top row is full
    REQUIRE(BoardTester::isLineComplete(board,0));

    // Clear the top row and move the lines down
    board.clearLines();

    // Check if the top row is empty after clearing
    REQUIRE_FALSE(BoardTester::isLineComplete(board,0));

    SECTION("Clearing and getting down") {
        for (int j = 0; j < 10; ++j) {
            BoardTester::getMatrix(board)[6][j] = 1;
        }
        for (int j = 0; j < 9; ++j) {
            BoardTester::getMatrix(board)[5][j] = 1;
        }
        REQUIRE(BoardTester::isLineComplete(board,6));
        board.clearLines();
        BoardTester::getMatrix(board)[6][9] = 1;
        REQUIRE(BoardTester::isLineComplete(board,6));
    }
}

TEST_CASE("Move at extremities", "[Board]") {
    std::shared_ptr<Brick> brick = std::make_shared<Brick>();
    Board board(true, brick, 20, 10);

    std::vector<Position> positions;
    SECTION("LEFT") {
        positions = {{0, 1}, {0, 2}, {0, 3}, {0, 4}};
        brick = std::make_shared<Brick>(positions, Position(0, 2), 1);

        REQUIRE(board.checkCollision(Direction2D::LEFT));
    }

    SECTION("RIGHT") {
        positions = {{9, 1}, {9, 2}, {9, 3}, {9, 4}};
        brick = std::make_shared<Brick>(positions, Position(9, 2), 1);

        REQUIRE(board.checkCollision(Direction2D::RIGHT));
    }

    SECTION("DOWN") {
        positions = {{19, 1}, {19, 2}, {19, 3}, {19, 4}};
        brick = std::make_shared<Brick>(positions, Position(19, 2), 1);

        REQUIRE(board.checkCollision(Direction2D::DOWN));
    }
}

TEST_CASE("Move to other bricks", "[Board]") {
    std::shared_ptr<Brick> brick = std::make_shared<Brick>();
    Board board(true, brick, 20, 10);

    std::vector<Position> positions = {{7, 6}, {7, 7}, {8, 6}, {8, 7}};
    brick = std::make_shared<Brick>(positions, Position(7, 7), 1);

    BoardTester::getMatrix(board)[6][6] = 1;

    REQUIRE(board.checkCollision(Direction2D::LEFT));

    BoardTester::getMatrix(board)[7][9] = 1;

    REQUIRE(board.checkCollision(Direction2D::RIGHT));
    REQUIRE_FALSE(board.checkCollision(Direction2D::DOWN));
}

TEST_CASE("Rotate at extremities", "[Board]") {
    std::shared_ptr<Brick> brick = std::make_shared<Brick>();
    Board board(true, brick, 20, 10);

    std::vector<Position> positions;
    std::vector<Position> newPositions;
    SECTION("LEFT") {
        positions = {{0, 3}, {0, 4}, {0, 5}, {1, 5}};
        brick = std::make_shared<Brick>(positions, Position(0, 4), 1);

        REQUIRE_FALSE(board.checkCollisionRotation(false));
        newPositions = {{1, 3}, {1, 4}, {1, 5}, {2, 5}};
        //verify the validity of the new positions
        REQUIRE(newPositions == brick->getPositions());


        positions = {{0, 3}, {0, 4}, {0, 5}, {1, 5}};
        brick = std::make_shared<Brick>(positions, Position(0, 4), 1);

        BoardTester::getMatrix(board)[4][1] = 1;

        REQUIRE(board.checkCollisionRotation(false));
    }

    SECTION("RIGHT") {
        positions = {{9, 3}, {9, 4}, {9, 5}, {8, 5}};
        brick = std::make_shared<Brick>(positions, Position(9, 4), 1);

        REQUIRE_FALSE(board.checkCollisionRotation(false));
        newPositions = {{8, 3}, {8, 4}, {8, 5}, {7, 5}};
        REQUIRE(newPositions == brick->getPositions());

        positions = {{9, 3}, {9, 4}, {9, 5}, {8, 5}};
        brick = std::make_shared<Brick>(positions, Position(9, 4), 1);

        BoardTester::getMatrix(board)[4][8] = 1;

        REQUIRE(board.checkCollisionRotation(false));
    }

    SECTION("DOWN") {
        positions = {{3, 18}, {4, 18}, {5, 18}, {5, 19}};
        brick = std::make_shared<Brick>(positions, Position(4, 18), 1);

        positions = {{3, 19}, {4, 19}, {5, 19}, {5, 18}};
        brick = std::make_shared<Brick>(positions, Position(4, 19), 1);

        BoardTester::getMatrix(board)[18][4] = 1;

        REQUIRE(board.checkCollisionRotation(true));
    }
}

TEST_CASE("Rotate at other bricks", "[Board]") {
    std::shared_ptr<Brick> brick = std::make_shared<Brick>();
    Board board(true, brick, 20, 10);

    std::vector<Position> positions;
    std::vector<Position> newPositions;
    SECTION("REVERSE") {
        positions = {{3, 5}, {4, 5}, {5, 5}, {6, 5}};
        brick = std::make_shared<Brick>(positions, Position(4, 5), 1);

        BoardTester::getMatrix(board)[4][4] = 1;
        BoardTester::getMatrix(board)[4][6] = 1;
        BoardTester::getMatrix(board)[3][5] = 1;
        BoardTester::getMatrix(board)[5][5] = 1;

        REQUIRE(board.checkCollisionRotation(true));
    }

    SECTION("NOT REVERSE") {
        positions = {{5, 5}, {6, 5}, {6, 4}, {6, 6}};
        brick = std::make_shared<Brick>(positions, Position(6, 5), 1);

        BoardTester::getMatrix(board)[5][4] = 1;
        BoardTester::getMatrix(board)[5][6] = 1;
        BoardTester::getMatrix(board)[6][4] = 1;
        BoardTester::getMatrix(board)[6][6] = 1;

        REQUIRE(board.checkCollisionRotation(false));
    }
}

TEST_CASE("Rotate at other bricks and close to wall", "[Board]") {
    std::shared_ptr<Brick> brick = std::make_shared<Brick>();
    Board board(true, brick, 20, 10);

    std::vector<Position> positions;
    std::vector<Position> newPositions;
    SECTION("NOT REVERSE") {
        positions = {{0, 3}, {0, 4}, {0, 5}, {1, 5}};
        brick = std::make_shared<Brick>(positions, Position(0, 4), 1);

        BoardTester::getMatrix(board)[4][1] = 1;

        REQUIRE(board.checkCollisionRotation(false));
    }

    SECTION("REVERSE") {
        positions = {{0, 3}, {0, 4}, {0, 5}, {1, 5}};
        brick = std::make_shared<Brick>(positions, Position(0, 4), 1);

        BoardTester::getMatrix(board)[5][2] = 1;

        REQUIRE_FALSE(board.checkCollisionRotation(true));
    }
}

TEST_CASE("Check on spawn", "[Board]") {
    SECTION("Brick positions above the board") {
        std::shared_ptr<Brick> brick = std::make_shared<Brick>();
        Board board(true, brick, 20, 10);

        // Set the brick positions above the board
        std::vector<Position> positions = {{5, -1}, {5, 0}, {5, 1}, {6, 1}};
        brick = std::make_shared<Brick>(positions, Position(5, 0), 1);

        // Call the method to check on spawn
        board.checkOnSpawn();

        // Ensure that the brick is not moved upwards
        REQUIRE(brick->getPositions()[0].getY() == -1);
        REQUIRE(brick->getPositions()[1].getY() == 0);
        REQUIRE(brick->getPositions()[2].getY() == 1);
        REQUIRE(brick->getPositions()[3].getY() == 1);
    }

    SECTION("Brick positions at the top of the board") {
        std::shared_ptr<Brick> brick = std::make_shared<Brick>();
        Board board(true, brick, 20, 10);

        // Set the brick positions at the top row of the board
        std::vector<Position> positions = {{5, 0}, {5, 1}, {5, 2}, {6, 1}};
        brick = std::make_shared<Brick>(positions, Position(5, 0), 1);

        // Call the method to check on spawn
        board.checkOnSpawn();

        // Ensure that the brick is not moved upwards
        REQUIRE(brick->getPositions()[0].getY() == 0);
        REQUIRE(brick->getPositions()[1].getY() == 1);
        REQUIRE(brick->getPositions()[2].getY() == 2);
        REQUIRE(brick->getPositions()[3].getY() == 1);
    }

    SECTION("Brick positions within the board") {
        std::shared_ptr<Brick> brick = std::make_shared<Brick>();
        Board board(true, brick, 20, 10);

        // Set the brick positions within the board
        std::vector<Position> positions = {{5, 5}, {5, 6}, {6, 5}, {6, 6}};
        brick = std::make_shared<Brick>(positions, Position(5, 5), 1);

        // Call the method to check on spawn
        board.checkOnSpawn();

        // Ensure that the brick is not moved upwards
        REQUIRE(brick->getPositions()[0].getY() == 5);
        REQUIRE(brick->getPositions()[1].getY() == 6);
        REQUIRE(brick->getPositions()[2].getY() == 5);
        REQUIRE(brick->getPositions()[3].getY() == 6);
    }

    SECTION("Brick positions colliding with filled cells") {
        std::shared_ptr<Brick> brick = std::make_shared<Brick>();
        Board board(true, brick, 20, 10);

        // Set the brick positions colliding with filled cells in the board
        std::vector<Position> positions = {{5, 1}, {5, 2}, {6, 1}, {6, 2}};
        brick = std::make_shared<Brick>(positions, Position(5, 1), 1);

        // Place filled cells in the board where the brick would collide
        BoardTester::getMatrix(board)[0][5] = 1;
        BoardTester::getMatrix(board)[1][5] = 1;
        BoardTester::getMatrix(board)[0][6] = 1;
        BoardTester::getMatrix(board)[1][6] = 1;

        // Call the method to check on spawn
        board.checkOnSpawn();

        // Ensure that the brick is moved upwards as expected
        REQUIRE(brick->getPositions()[0].getY() == -2);
        REQUIRE(brick->getPositions()[1].getY() == -1);
        REQUIRE(brick->getPositions()[2].getY() == -2);
        REQUIRE(brick->getPositions()[3].getY() == -1);
    }
}

TEST_CASE("Check if the top row is full", "[Board]") {
    SECTION("Top row is not full") {
        std::shared_ptr<Brick> brick = std::make_shared<Brick>();
        std::vector<Position> positions = {{4, 0}, {5, 0}, {6, 0}, {5, 1}};
        brick = std::make_shared<Brick>(positions, Position(5, 1), 1);
        Board board(true, brick, 20, 10);

        // Call the method to check on spawn
        board.checkOnSpawn();

        // Ensure that the top row is not full
        REQUIRE_FALSE(board.isTopFull());
    }

    SECTION("Top row is full with default brick") {
        std::shared_ptr<Brick> brick = std::make_shared<Brick>();
        std::vector<Position> positions = {{4, 0}, {5, 0}, {6, 0}, {5, 1}};
        brick = std::make_shared<Brick>(positions, Position(5, 1), 1);
        Board board(true, brick, 20, 10);

        // Fill the center of the top row with default brick positions
        for (int i = 4; i <= 7; ++i) {
            BoardTester::getMatrix(board)[0][i] = 1;
        }

        // Call the method to check on spawn
        board.checkOnSpawn();

        // Ensure that the top row is considered full
        REQUIRE(board.isTopFull());
    }

    SECTION("Top row is full with custom brick") {
        std::shared_ptr<Brick> brick = std::make_shared<Brick>();
        Board board(true, brick, 20, 10);

        // Set a custom brick position at the center of the top row
        std::vector<Position> positions = {{5, 0}, {6, 0}, {5, 1}, {6, 1}};
        brick = std::make_shared<Brick>(positions, Position(5, 0), 1);

        // Ensure that the brick is at the center of the top row
        REQUIRE_FALSE(BoardTester::getMatrix(board)[0][5] != 0);
        REQUIRE_FALSE(BoardTester::getMatrix(board)[0][6] != 0);
        REQUIRE_FALSE(BoardTester::getMatrix(board)[1][5] != 0);
        REQUIRE_FALSE(BoardTester::getMatrix(board)[1][6] != 0);

        // Ensure that the top row is considered full
        REQUIRE_FALSE(board.isTopFull());
    }

    SECTION("Top row is not full -> spawn possible)") {
        std::shared_ptr<Brick> brick = std::make_shared<Brick>();
        Board board(true, brick, 20, 10);

        // Set a custom brick position at the center of the top row
        std::vector<Position> positions = {{4, 1}, {5, 1}, {6, 1}, {5, 0}};
        brick = std::make_shared<Brick>(positions, Position(5, 1), 1);

        BoardTester::getMatrix(board)[0][6] = 1;

        // Ensure that the top row is considered full
        REQUIRE_FALSE(board.isTopFull());
    }

    SECTION("A Single position avaible)") {
        std::shared_ptr<Brick> brick = std::make_shared<Brick>();
        std::vector<Position> positions = {{4, 0}, {5, 0}, {6, 0}, {5, 1}};
        brick = std::make_shared<Brick>(positions, Position(5, 1), 1);
        Board board(true, brick, 20, 10);

        BoardTester::getMatrix(board)[0][6] = 1;
        BoardTester::getMatrix(board)[0][4] = 1;
        BoardTester::getMatrix(board)[1][6] = 1;
        BoardTester::getMatrix(board)[1][5] = 1;
        BoardTester::getMatrix(board)[1][4] = 1;

        // Call the method to check on spawn
        board.checkOnSpawn();

        // Ensure that the top row is considered full
        REQUIRE_FALSE(board.isTopFull());
    }
}
