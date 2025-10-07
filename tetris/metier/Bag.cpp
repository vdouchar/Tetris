#include <algorithm>
#include <iostream>

#include "Brick.h"
#include "Random.hpp"

#include "Bag.h"

Bag::Bag(std::vector<Brick> bricksParam) : current(0) {
    this->bricks = bricksParam;
    shuffle();
}

void Bag::shuffle() {
    for(unsigned i = 0; i < bricks.size(); ++i) {
        int randomIndex = random_value<int>(0, i);
        std::swap(bricks[i], bricks[randomIndex]);
    }
}

Bag& Bag::getInstance(std::vector<Brick> bricks) {
    static Bag instance(bricks);
    return instance;
}

Brick Bag::getRandomBrick() {
    Brick brick = bricks[current];
    if (current == bricks.size() - 1) {
        shuffle();
        current = 0;
        nextbrick = bricks[current];
    } else {
        nextbrick = bricks[current+1];
        current++;
    }
    return brick;
}

int Bag::nextBrick(int y, int x) {
    return nextbrick.getAtPos(y,x);
}

std::string Bag::nextBrick() {
    return nextbrick.to_string();
}
