#include <iostream>
#include <vector>
#include <deque>
#include <tuple>

int width = 10;
int length = 100;

int stepcnt = 0;

class Step{
    public:
    Step(int x, int y, Step* mother) : posX(x), posY(y), motherCell(mother) {
        stepcnt++;
    }
    ~Step() {
        stepcnt--;
    }

    int posX, posY;
    Step* motherCell;
};

int directionsX[4] = {0,1, 0, -1};
int directionsY[4] = {-1, 0, 1, 0};

bool colliders[100][10] = {
        {0,0,0,1,0,0,0,0,0,1},
        {0,1,1,0,1,0,1,0,0,1},
        {0,0,1,0,1,0,1,0,0,1},
        {1,0,1,0,1,0,0,0,1,1},
        {0,0,0,0,0,0,1,0,1,0},
        {0,1,0,1,0,0,0,0,0,1},
        {0,0,1,0,0,1,1,1,1,1},
        {1,0,1,1,0,1,0,0,1,0},
        {0,0,1,0,0,0,1,0,1,0},
        {1,0,0,0,1,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,0,1},
        {0,1,1,0,1,0,1,0,0,1},
        {0,0,1,0,1,0,1,0,0,1},
        {1,0,1,0,1,0,0,0,1,1},
        {0,0,0,0,0,0,1,0,1,0},
        {0,1,0,1,0,0,0,0,0,1},
        {0,0,1,0,0,1,1,1,1,1},
        {1,0,1,1,0,1,0,0,1,0},
        {0,0,1,0,0,0,1,0,1,0},
        {1,0,0,0,1,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,0,1},
        {0,1,1,0,1,0,1,0,0,1},
        {0,0,1,0,1,0,1,0,0,1},
        {1,0,1,0,1,0,0,0,1,1},
        {0,0,0,0,0,0,1,0,1,0},
        {0,1,0,1,0,0,0,0,0,1},
        {0,0,1,0,0,1,1,1,1,1},
        {1,0,1,1,0,1,0,0,1,0},
        {0,0,1,0,0,0,1,0,1,0},
        {1,0,0,0,1,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,0,1},
        {0,1,1,0,1,0,1,0,0,1},
        {0,0,1,0,1,0,1,0,0,1},
        {1,0,1,0,1,0,0,0,1,1},
        {0,0,0,0,0,0,1,0,1,0},
        {0,1,0,1,0,0,0,0,0,1},
        {0,0,1,0,0,1,1,1,1,1},
        {1,0,1,1,1,1,0,0,1,0},
        {0,0,1,0,0,0,1,0,1,0},
        {1,0,0,0,1,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,0,1},
        {0,1,1,0,1,0,1,0,0,1},
        {0,0,1,0,1,0,1,0,0,1},
        {1,0,1,0,1,0,0,0,1,1},
        {0,0,0,0,0,0,1,0,1,0},
        {0,1,0,1,0,0,0,0,0,1},
        {0,0,1,0,0,1,1,1,1,1},
        {1,0,1,1,0,1,0,0,1,0},
        {0,0,1,0,0,0,1,0,1,0},
        {1,0,0,0,1,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,0,1},
        {0,1,1,0,1,0,1,0,0,1},
        {0,0,1,0,1,0,1,0,0,1},
        {1,0,1,0,1,0,0,0,1,1},
        {0,0,0,0,0,0,1,0,1,0},
        {0,1,0,1,0,0,0,0,0,1},
        {0,0,1,0,0,1,1,1,1,1},
        {1,0,1,1,0,1,0,0,1,0},
        {0,0,1,0,0,0,1,0,1,0},
        {1,0,0,0,1,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,0,1},
        {0,1,1,0,1,0,1,0,0,1},
        {0,0,1,0,1,0,1,0,0,1},
        {1,0,1,0,1,0,0,0,1,1},
        {0,0,0,0,0,0,1,0,1,0},
        {0,1,0,1,0,0,0,0,0,1},
        {0,0,1,0,0,1,1,1,1,1},
        {1,0,1,1,0,1,0,0,1,0},
        {0,0,1,0,0,0,1,0,1,0},
        {1,0,0,0,1,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,0,1},
        {0,1,1,0,1,0,1,0,0,1},
        {0,0,1,0,1,0,1,0,0,1},
        {1,0,1,0,1,0,0,0,1,1},
        {0,0,0,0,0,0,1,0,1,0},
        {0,1,0,1,0,0,0,0,0,1},
        {0,0,1,0,0,1,1,1,1,1},
        {1,0,1,1,0,1,0,0,1,0},
        {0,0,1,0,0,0,1,0,1,0},
        {1,0,0,0,1,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,0,1},
        {0,1,1,0,1,0,1,0,0,1},
        {0,0,1,0,1,0,1,0,0,1},
        {1,0,1,0,1,0,0,0,1,1},
        {0,0,0,0,0,0,1,0,1,0},
        {0,1,0,1,0,0,0,0,0,1},
        {0,0,1,0,0,1,1,1,1,1},
        {1,0,1,1,1,1,0,0,1,0},
        {0,0,1,0,0,0,1,0,1,0},
        {1,0,0,0,1,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,0,1},
        {0,1,1,0,1,0,1,0,0,1},
        {0,0,0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1,1,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,1,0,1,0,0,0,0,0,1},
        {0,0,1,0,0,1,1,1,1,1},
        {1,0,1,1,0,1,0,0,1,0},
        {0,0,1,0,0,0,1,0,1,0},
        {1,0,0,0,1,0,0,0,0,0}
};

bool detectCollision(int x, int y) {
    if(x >= 0 && x < width && y >= 0 && y < length) {
        return colliders[y][x];
    }
    else return true;
}

bool checkAncestors(Step* step) {
    if(step->motherCell == nullptr) return true;
    else {
        Step* ancestor = step->motherCell;
        while (ancestor != nullptr) {
            if(!(step->posX == ancestor->posX && step->posY == ancestor->posY)) {
                ancestor = ancestor->motherCell;
            } else return false;
        }
    }
    return true;
}

std::deque<std::pair<int, int>> findWay(int startX, int startY, int finishX, int finishY) {
    std::vector<std::vector<Step*>> generations;
    std::vector<Step*> gen;

    Step* correctPath = nullptr;
    std::deque<std::pair<int, int>> res;

    gen.push_back(new Step(startX, startY, nullptr));
    generations.push_back(gen);

    while (true) {
        std::vector<Step*> tempGen;
        for(auto i : generations.back()) {
            for(int j = 0; j < 4; j++) {
                int newPosX = i->posX + directionsX[j];
                int newPosY = i->posY + directionsY[j];

                bool visitedByOtherStepThisGeneration = false;
                for(auto j : tempGen) {
                    if(newPosX == j->posX && newPosY == j->posY) visitedByOtherStepThisGeneration = true;
                }

                if(!detectCollision(newPosX,newPosY) && checkAncestors(i) && !visitedByOtherStepThisGeneration) {
                    tempGen.push_back(new Step(newPosX, newPosY, i));
                    if(stepcnt % 100 == 0) std::cout << stepcnt << std::endl;;
                    if(tempGen.back()->posX == finishX && tempGen.back()->posY == finishY) {
                        correctPath = tempGen.back();
                        break;
                    }
                }
            }
            if(correctPath != nullptr) break;
        }
        generations.push_back(tempGen);
        if(correctPath != nullptr) break;
    }

    while (correctPath != nullptr) {
        res.push_front(std::make_pair(correctPath->posX, correctPath->posY));
        correctPath = correctPath->motherCell;
    }

    for(auto i : generations) {
        for(auto j : i) {
            delete j;
            if(stepcnt % 100 == 0) std::cout << stepcnt << std::endl;;
        }
    }
    return res;
}



int main() {
    std::cout << "Hello, World!" << std::endl;

    std::deque<std::pair<int, int>> deque;

    deque = findWay(0, 0, 9, 99);

    for(auto i : deque) {
        std::cout << "X: " << i.first << " Y: " << i.second << std::endl;
    }

    std::cout << "----------" << detectCollision(9,6);

    return 0;
}

