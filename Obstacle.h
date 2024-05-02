#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "N5110.h"
#include "Character.h"

class Obstacle {
public:
    Obstacle(int x);
    void draw(N5110& lcd);
    bool checkCollision(const Character& character);
    void move(int dx);
    bool isOffScreen(int screenWidth);
    void reset(int screenWidth, int screenHeight);
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;

private:
    int x, y;
    static const int obstacleWidth = 16;
    static const int obstacleHeight = 6;
    static const int POLICECAR_SPRITE[6][16];
};

#endif