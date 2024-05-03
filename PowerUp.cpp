#include "PowerUp.h"
#include "N5110.h"

const int PowerUp::HEART_SPRITE[7][7] = {
    { 0,1,1,1,1,1,0 },
    { 1,0,0,1,0,0,1 },
    { 1,0,0,1,0,0,1 },
    { 1,1,0,0,0,1,1 },
    { 0,1,1,0,1,1,0 },
    { 0,0,1,1,1,0,0 },
    { 0,0,0,1,0,0,0 }
};

const int PowerUp::STOPWATCH_SPRITE[7][7] = {
    { 0,1,1,1,1,1,0 },
    { 1,0,0,1,0,0,1 },
    { 1,0,0,1,0,0,1 },
    { 1,0,0,1,1,1,1 },
    { 1,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,1 },
    { 0,1,1,1,1,1,0 }
};

PowerUp::PowerUp(int x, int y, int size, PowerUpType type) : x(x), y(y), size(size), type(type) {}

void PowerUp::draw(N5110& lcd) {
    if (type == INVINCIBILITY) {
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 7; j++) {
                if (STOPWATCH_SPRITE[i][j] == 1) {
                    lcd.setPixel(x + j, y + i, true);
                }
            }
        }
    } else if (type == HEALTH) {
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 7; j++) {
                if (HEART_SPRITE[i][j] == 1) {
                    lcd.setPixel(x + j, y + i, true);
                }
            }
        }
    }
}

void PowerUp::update(int screenWidth) {
    x -= 4;
    if (x < -size) {
        x = 2 * screenWidth;
    }
}

bool PowerUp::checkCollision(const Character& character) {
    return (character.getX() < x + size && character.getX() + character.getWidth() > x &&
            character.getY() < y + size && character.getY() + character.getHeight() > y);
}

PowerUpType PowerUp::getType() {
    return type;
}

void PowerUp::setX(int newX) {
    x = newX;
}

int PowerUp::getX() const { return x; }
int PowerUp::getY() const { return y; }
int PowerUp::getSize() const { return size; }