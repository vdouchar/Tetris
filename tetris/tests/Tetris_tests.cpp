#include <catch2/catch_test_macros.hpp>
#include "../metier/Tetris.h"

class TetrisTester {
public:
    static void setLevel(Tetris& tetris, unsigned level) {
        tetris.level = level;
    }

    static unsigned getLevel(const Tetris& tetris) {
        return tetris.level;
    }

    static void incrementLevel(Tetris& tetris) { tetris.level++; }

    static void setScore(Tetris& tetris, int score) {
        tetris.score = score;
    }

    static int getScore(const Tetris& tetris) {
        return tetris.score;
    }

    static void setClearedLines(Tetris& tetris, unsigned clearedLines) {
        tetris.clearedLines = clearedLines;
    }

    static unsigned getClearedLines(const Tetris& tetris) {
        return tetris.clearedLines;
    }

    static void setTotalClearedLines(Tetris& tetris, unsigned totalClearedLines) {
        tetris.totalClearedLines = totalClearedLines;
    }

    static unsigned getTotalClearedLines(const Tetris& tetris) {
        return tetris.totalClearedLines;
    }

    static void setEndTime(Tetris& tetris, std::chrono::steady_clock::time_point endTime) {
        tetris.endTime = endTime;
    }

    static std::chrono::steady_clock::time_point getEndTime(const Tetris& tetris) {
        return tetris.endTime;
    }

    static void setSpeed(Tetris& tetris, double speed) {
        tetris.speed = speed;
    }

    static double getSpeed(const Tetris& tetris) {
        return tetris.speed;
    }

    static std::shared_ptr<Brick> getCurrentBrick(Tetris& tetris) {
        return tetris.currentBrick;
    }

    static Bag& getBag(Tetris& tetris) {
        return tetris.bag;
    }

    static Board& getBoard(Tetris& tetris) {
        return tetris.board;
    }

    static int calculateScore(Tetris& tetris,unsigned lines, unsigned drop) {
        setScore(tetris,0);
        tetris.calculateScore(lines,drop);
        return getScore(tetris);
    }
};

class BoardTester {
public:
    static std::vector<std::vector<int>>& getMatrix(Board& board) { return board.matrix; }
};

class BagTester {
public:
    static void setIndex(Bag& bag,int index) { bag.current = index; }
};

TEST_CASE("Tetris initialization", "[Tetris]") {
    Tetris tetris(false, 1, 20, 10);

    Bag& bag = TetrisTester::getBag(tetris);
    BagTester::setIndex(bag,0);

    SECTION("Initial values") {
        REQUIRE(TetrisTester::getLevel(tetris) == 1);
        REQUIRE(TetrisTester::getScore(tetris) == 0);
        REQUIRE(TetrisTester::getClearedLines(tetris) == 0);
        REQUIRE(TetrisTester::getTotalClearedLines(tetris) == 0);
    }
}

TEST_CASE("Tetris scoring", "[Tetris]") {
    Tetris tetris(false, 1, 20, 10);

    Bag& bag = TetrisTester::getBag(tetris);
    BagTester::setIndex(bag,0);

    // Test scoring for clearing different numbers of lines
    SECTION("Scoring for clearing lines") {
        TetrisTester::calculateScore(tetris, 0, 0);
        REQUIRE(TetrisTester::getScore(tetris) == 0);

        TetrisTester::calculateScore(tetris, 1, 0);
        REQUIRE(TetrisTester::getScore(tetris) == 40 * 1);

        TetrisTester::calculateScore(tetris, 2, 0);
        REQUIRE(TetrisTester::getScore(tetris) == 100 * 2 * 1);

        TetrisTester::calculateScore(tetris, 3, 0);
        REQUIRE(TetrisTester::getScore(tetris) == 300 * 3 * 1);

        TetrisTester::calculateScore(tetris, 4, 0);
        REQUIRE(TetrisTester::getScore(tetris) == 1200 * 4 * 1);

        // Test scoring for dropping without clearing lines
        TetrisTester::calculateScore(tetris, 0, 5);
        REQUIRE(TetrisTester::getScore(tetris) == 5);
    }

    // Test scoring for incrementing level
    SECTION("Scoring for incrementing level") {
        TetrisTester::setClearedLines(tetris, 9);
        TetrisTester::incrementLevel(tetris);
        REQUIRE(TetrisTester::getLevel(tetris) == 2);

        Board& board = TetrisTester::getBoard(tetris);

        for(int i = 0; i<=9; ++i){
            BoardTester::getMatrix(board)[7][i] = 1;
        }

        tetris.drop();
        BagTester::setIndex(bag,0);

        REQUIRE(TetrisTester::getLevel(tetris) == 3);
        REQUIRE(TetrisTester::getClearedLines(tetris) == 0);
        //Cause only one time clearLines has been called in Tetris
        REQUIRE(TetrisTester::getTotalClearedLines(tetris) == 1);
    }
}

TEST_CASE("Tetris game end conditions", "[Tetris]") {
    Tetris tetris(false, 1, 20, 10);

    Bag& bag = TetrisTester::getBag(tetris);
    BagTester::setIndex(bag,0);

    SECTION("Game ends when board is full") {
        Board& board = TetrisTester::getBoard(tetris);

        BoardTester::getMatrix(board)[0][5] = 1;
        //In case of L or J brick
        BoardTester::getMatrix(board)[1][5] = 1;

        board.checkOnSpawn();

        REQUIRE(tetris.endGame());
        REQUIRE_FALSE(tetris.hasWin());
    }

    SECTION("Game ends after a certain time") {
        auto endTime = std::chrono::minutes(-15) + std::chrono::steady_clock::now();

        TetrisTester::setEndTime(tetris,endTime);

        REQUIRE(tetris.endGame());
        REQUIRE(tetris.hasWin());
    }

    SECTION("Game ends after reaching maximum score") {
        TetrisTester::setScore(tetris, 1000000);

        REQUIRE(tetris.endGame());
        REQUIRE(tetris.hasWin());
    }

    SECTION("Game ends after clearing a certain number of lines") {
        TetrisTester::setTotalClearedLines(tetris, 250);

        REQUIRE(tetris.endGame());
        REQUIRE(tetris.hasWin());
    }
}
