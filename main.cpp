#include <iostream>
#include <vector>
#include <deque>
#include <tuple>

#define TOP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

int width = 4;
int heigth = 5;

int stepcnt = 0;

class Step {
public:
    Step(int x, int y, Step *mother) : posX(x), posY(y), motherCell(mother) {
        stepcnt++;
    }

    ~Step() {
        stepcnt--;
    }

    int posX, posY;
    Step *motherCell;
};

int directionsX[4] = {0, 1, 0, -1};
int directionsY[4] = {-1, 0, 1, 0};

std::vector<bool> colliders(width + (2 * heigth) + (width * heigth), true);


bool detectCollision(int direction, int x, int y) {
    int topCollider = (2 * heigth + 1) * x + (2 * y);
    switch (direction) {
        case TOP:
            std::cout << "collider id: " << topCollider << "| if \"1\" collider detected: " << colliders[topCollider]
                      << std::endl;
            return colliders[topCollider];
            break;
        case RIGHT:
            std::cout << "collider id: " << topCollider + 2 + (2 * heigth) << "| if \"1\" collider detected: "
                      << colliders[topCollider + 2 + (2 * heigth)] << std::endl;
            return colliders[topCollider + 2 + (2 * heigth)];
            break;
        case DOWN:
            std::cout << "collider id: " << topCollider + 2 << "| if \"1\" collider detected: "
                      << colliders[topCollider + 2] << std::endl;
            return colliders[topCollider + 2];
            break;
        case LEFT:
            std::cout << "collider id: " << topCollider + 1 << "| if \"1\" collider detected: "
                      << colliders[topCollider + 1] << std::endl;
            return colliders[topCollider + 1];
            break;
    }
}

std::deque<std::pair<int, int>> findWay(int startX, int startY, int finishX, int finishY) {
    std::vector<std::vector<Step *>> generations;
    std::vector<Step *> gen;

    Step *correctPath = nullptr;
    std::deque<std::pair<int, int>> res;

    gen.push_back(new Step(startX, startY, nullptr));
    generations.push_back(gen);

    int steps = 0;

    while (!generations.back().empty()) {
        std::cout << "new cycle" << std::endl;
        std::vector<Step *> tempGen;
        for (auto i: generations.back()) {
            for (int j = 0; j < 4; j++) {
                int newPosX = i->posX + directionsX[j];
                int newPosY = i->posY + directionsY[j];

                std::cout << "since the old position was: " << i->posX << "|" << i->posY
                          << " and modif was: "
                          << directionsX[j] << "|" << directionsY[j] << " new position is "
                          << newPosX << "|" << newPosY
                          << std::endl;

                bool visitedByOtherStepThisGeneration = false;
                for (auto j: tempGen) {
                    if (newPosX == j->posX && newPosY == j->posY)
                        visitedByOtherStepThisGeneration = true;
                }
                std::cout << "this gen checked" << std::endl;

                bool visitedByOtherStepOtherGeneration = false;
                for (auto j: generations) {
                    for (auto k: j) {
                        if (newPosX == k->posX &&
                            newPosY == k->posY)
                            visitedByOtherStepOtherGeneration = true;
                    }
                }
                std::cout << "other gen checked" << std::endl;

                if (!detectCollision(j, i->posX, i->posY) && !visitedByOtherStepOtherGeneration &&
                    !visitedByOtherStepThisGeneration) {
                    tempGen.push_back(new Step(newPosX, newPosY, i));
                    std::cout << ">>>>>>>>>coord pushed " << tempGen.back()->posX << "|"
                              << tempGen.back()->posY
                              << std::endl;
                    if (tempGen.back()->posX == finishX && tempGen.back()->posY == finishY) {
                        correctPath = tempGen.back();
                        break;
                    }
                }
                if (correctPath != nullptr) break;
            }
            for (auto g: tempGen) {
                std::cout << g->posX << " | ";
                std::cout << g->posY << std::endl;
            }
        }
        generations.push_back(tempGen);
        if (correctPath != nullptr) break;
    }

    while (correctPath != nullptr) {
        res.push_front(std::make_pair(correctPath->posX, correctPath->posY));
        correctPath = correctPath->motherCell;
    }

    for (auto i: res) {
        std::cout << "X: " << i.first << " Y: " << i.second << std::endl;
    }
    if(res.empty()) std::cout << "no way man!" << std::endl;
    return res;
}


int main() {

    colliders[12] = false;
    colliders[23] = false;
    colliders[34] = false;
    colliders[35] = false;
    colliders[14] = false;
    colliders[25] = false;
    colliders[36] = false;
    colliders[4] = false;
    colliders[16] = false;
    colliders[27] = false;
    colliders[38] = false;
    colliders[17] = false;
    colliders[18] = false;
    colliders[29] = false;
    colliders[30] = false;
    colliders[20] = false;
    colliders[31] = false;
    colliders[42] = false;


    std::cout << "Hello, World!" << std::endl;

    std::deque<std::pair<int, int>> deque;

    deque = findWay(0, 0, 10, 10);


    return 0;
}
