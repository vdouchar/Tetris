#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "../metier/Brick.h"
#include "../metier/Position.h"
#include "../metier/Direction2D.h"

class BrickTester {
public:
    static Position getCenter(Brick& brick) {return brick.center; }
};

TEST_CASE("Brick construction", "[Brick]") {
    std::vector<Position> positions = {{0, 0}, {1, 0}, {0, 1}, {1, 1}};
    Position center(0, 0);
    int color = 1;

    Brick brick(positions, center, color);

    REQUIRE(brick.getPositions() == positions);
    REQUIRE(BrickTester::getCenter(brick) == center);
    REQUIRE(brick.getColor() == color);
}

TEST_CASE("Brick movement", "[Brick]") {
    std::vector<Position> positions = {{0, 0}, {1, 0}, {0, 1}, {1, 1}};
    Position center(0, 0);
    int color = 4;

    Brick brick(positions, center, color);

    // Move the brick right
    brick += Direction2D::RIGHT;
    std::vector<Position> expectedPositionsRight = {{1, 0}, {2, 0}, {1, 1}, {2, 1}};
    REQUIRE(brick.getPositions() == expectedPositionsRight);

    REQUIRE(BrickTester::getCenter(brick) == Position(1,0));

    // Move the brick down
    brick += Direction2D::DOWN;
    std::vector<Position> expectedPositionsDown = {{1, 1}, {2, 1}, {1, 2}, {2, 2}};
    REQUIRE(brick.getPositions() == expectedPositionsDown);

    REQUIRE(brick.getColor() == color);
    REQUIRE(BrickTester::getCenter(brick) == Position(1,1));
}

TEST_CASE("Brick rotation", "[Brick]") {
    std::vector<Position> positions = {{2, 2}, {3, 2}, {2, 3}, {3, 3}};
    Position center(2, 2);
    int color = 1;

    Brick brick(positions, center, color);

    // Rotate the brick clockwise
    brick.rotate(false);
    std::vector<Position> expectedPositionsClockwise = {{2, 2}, {2, 3}, {1, 2}, {1, 3}};
    REQUIRE(brick.getPositions() == expectedPositionsClockwise);

    // Rotate the brick counterclockwise to restore its original positions
    brick.rotate(true);
    REQUIRE(brick.getPositions() == positions);
}

TEST_CASE("Brick movement and rotation", "[Brick]") {
    std::vector<Position> positions = {{0, 0}, {1, 0}, {0, 1}, {1, 1}};
    Position center(0, 0);
    int color = 1;

    Brick brick(positions, center, color);

    // Move the brick right
    brick += Direction2D::RIGHT;
    std::vector<Position> expectedPositionsRight = {{1, 0}, {2, 0}, {1, 1}, {2, 1}};
    REQUIRE(brick.getPositions() == expectedPositionsRight);

    // Move the brick down
    brick += Direction2D::DOWN;
    std::vector<Position> expectedPositionsDown = {{1, 1}, {2, 1}, {1, 2}, {2, 2}};
    REQUIRE(brick.getPositions() == expectedPositionsDown);

    // Rotate the brick clockwise
    brick.rotate(false);
    std::vector<Position> expectedPositionsClockwise = {{1, 1}, {1, 2}, {0, 1}, {0, 2}};
    REQUIRE(brick.getPositions() == expectedPositionsClockwise);
}

TEST_CASE("Brick comparison", "[Brick]") {
    std::vector<Position> positions1 = {{0, 0}, {1, 0}, {0, 1}, {1, 1}};
    Position center1(0, 0);
    int color1 = 1;

    Brick brick1(positions1, center1, color1);

    std::vector<Position> positions2 = {{0, 0}, {1, 0}, {0, 1}, {1, 1}};
    Position center2(0, 0);
    int color2 = 1;

    Brick brick2(positions2, center2, color2);

    std::vector<Position> positions3 = {{0, 0}, {1, 0}, {0, 1}};
    Position center3(0, 0);
    int color3 = 2;

    Brick brick3(positions3, center3, color3);

    REQUIRE(brick1 == brick2); // Bricks with same properties should be equal
    REQUIRE_FALSE(brick1 != brick2);

    REQUIRE_FALSE(brick1 == brick3); // Bricks with different properties should not be equal
    REQUIRE(brick1 != brick3);
}
