#ifndef CHARACTER_H
#define CHARACTER_H

#include "N5110.h"
#include "mbed.h"

class Character {
public:
    Character(int x, int y);

    void draw(N5110& lcd, bool isAboveGround);
    void setHit(bool isHit);
    void move(int dx, int dy, int screenWidth, int screenHeight);
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    bool isHit() const;

private:
    int x;
    int y;
    static const int RUNNING_SPRITE_1[11][6];
    static const int RUNNING_SPRITE_2[11][6];
    static const int FLYING_SPRITE[11][9];
    static const int GOTHIT_SPRITE[11][7];
    bool hitState;
    mbed::Timer hitTimer;
};

#endif