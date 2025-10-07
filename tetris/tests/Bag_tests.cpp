#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "../metier/Bag.h"
#include "../metier/Brick.h"
#include "../metier/DefaultBrick.h"

class BagTester {
public:
    static std::vector<Brick> getBricks(Bag& bag) { return bag.bricks; }
    static int getIndex(Bag& bag) {return bag.current; }
    static int getSize(Bag& bag) {return bag.bricks.size(); }
};

TEST_CASE("Bag initialization", "[Bag]") {
    DefaultBrick dfBrick(10);
    Bag& bag = Bag::getInstance(dfBrick.defaultBag);
    SECTION("Make sure size stay 7") {
        //index is already 1 beacause at initialization of
        //bag a brick is getted by the tetris class
        //which increment current index in bag
        REQUIRE(BagTester::getIndex(bag) == 0);

        Brick brick = bag.getRandomBrick();

        REQUIRE(BagTester::getIndex(bag) == 1);

        REQUIRE(BagTester::getSize(bag) == 7);
    }

    SECTION("Make sure size stay 7") {
        std::vector<Brick> initializedBricks = BagTester::getBricks(bag);

        //Have initialized 2 defaultBricks and verify if all the elements are contained in the bag
        for(Brick brick: dfBrick.defaultBag){
            REQUIRE(std::find(initializedBricks.begin(), initializedBricks.end(), brick) != initializedBricks.end());
        }
    }
}

TEST_CASE("Unique instance of Bag", "[Bag]") {
    std::vector<Brick> bricks {};
    Bag& bag1 = Bag::getInstance(bricks);
    Bag& bag2 = Bag::getInstance(bricks);

    // Test if bag1 and bag2 are the same instance
    REQUIRE(&bag1 == &bag2);
}

TEST_CASE("Bag tests", "[Bag]") {
    // Create a Bag instance with a vector of bricks
    DefaultBrick dfBrick(10);
    std::vector<Brick> bricks = dfBrick.defaultBag;
    Bag& bag = Bag::getInstance(bricks);

    SECTION("Getting random bricks") {
        // Test that a random brick is retrieved from the bag
        Brick brick = bag.getRandomBrick();

        REQUIRE(BagTester::getIndex(bag) == 2);

        // Ensure that the retrieved brick is in the original vector of bricks
        REQUIRE(std::find(bricks.begin(), bricks.end(), brick) != bricks.end());

        // Test that consecutive calls to getRandomBrick() yield different bricks
        Brick nextBrick = bag.getRandomBrick();
        REQUIRE(brick != nextBrick);
    }
}
