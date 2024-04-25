#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "N5110.h"
#include "Character.h"

class Obstacle {
public:
    Obstacle(int x, int y, int width, int height);
    void draw(N5110& lcd) const; // Mark as const
    bool checkCollision(const Character& character) const; // Mark as const
    void move(int dx);
    void reset(int screenWidth, int screenHeight);
    bool isOffScreen(int screenWidth) const; // Add const here if implementation doesn't modify the object

private:
    int x, y, width, height;
};

#endif
