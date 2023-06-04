#include <stdbool.h>
#ifndef OBJECT_H
#define OBJECT_H
#define NUM_FRUITS 100
#define NUM_WALLS 1000



struct Wall* walls;
struct Fruit* fruits;

bool isWall;
bool isFruit;

typedef struct Snake {
    int x;
    int y;
} Snake;

struct Wall {
    int x;
    int y;
    char shape;
};

struct Fruit {
    int x;
    int y;
    char shape;

};


//void destroyWalls() {
//    free(walls);
//}

//void destroyFruits() {
//    free(fruits);
//}
#endif