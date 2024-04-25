#ifndef CHARACTER_H
#define CHARACTER_H

#include "N5110.h"
#include "mbed.h"

class Character {
public:
    Character(int x, int y, int size);

    void draw(N5110& lcd, bool isInvincible, mbed::Timer& invincibilityTimer);
    void move(int dx, int dy, int screenWidth, int screenHeight);
    int getX() const;
    int getY() const;
    int getSize() const;

private:
    int x;
    int y;
    int size;
};

#endif
