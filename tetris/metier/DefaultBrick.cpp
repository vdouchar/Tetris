#include "DefaultBrick.h"

#include <vector>

DefaultBrick::DefaultBrick(int width) {
    if (width % 2 != 0) {
        width -= 1;
    }
    center = width / 2;

    // Initialisation of bricks
    TBrick = Brick({Position(center - 1, 1), Position(center, 1), Position(center + 1, 1), Position(center, 0)}, Position(center, 1), 1);
    CBrick = Brick({Position(center - 1, 0), Position(center - 1, 1), Position(center, 1), Position(center, 0)}, Position(center, 0), 2);
    IBrick = Brick({Position(center - 1, 1), Position(center, 1), Position(center+1, 1), Position(center+2, 1)}, Position(center+1, 1), 3);
    JBrick = Brick({Position(center-1, 0), Position(center-1, 1), Position(center, 1), Position(center + 1, 1)}, Position(center, 1), 4);
    LBrick = Brick({Position(center - 1, 1), Position(center, 1), Position(center + 1, 1), Position(center + 1, 0)}, Position(center, 1), 5);
    SBrick = Brick({Position(center - 1, 1), Position(center, 1), Position(center, 0), Position(center + 1, 0)}, Position(center, 0), 6);
    ZBrick = Brick({Position(center - 1, 0), Position(center, 0), Position(center, 1), Position(center + 1, 1)}, Position(center, 0), 7);

    // Add bricks to default bag
    defaultBag.push_back(TBrick);
    defaultBag.push_back(CBrick);
    defaultBag.push_back(SBrick);
    defaultBag.push_back(LBrick);
    defaultBag.push_back(JBrick);
    defaultBag.push_back(IBrick);
    defaultBag.push_back(ZBrick);
}
