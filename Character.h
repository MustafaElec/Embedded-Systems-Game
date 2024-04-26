#ifndef CHARACTER_H
#define CHARACTER_H

#include "N5110.h"
#include "mbed.h"

class Character {
public:
    Character(int x, int y);

    void draw(N5110& lcd, bool isInvincible, mbed::Timer& invincibilityTimer);
    void move(int dx, int dy, int screenWidth, int screenHeight);
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;

private:
    int x;
    int y;
    static const int SPRITE[13][8];
    static const int SPRITE_WIDTH = 8;
    static const int SPRITE_HEIGHT = 13;
};

#endif