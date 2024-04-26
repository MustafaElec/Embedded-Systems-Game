#include "Character.h"
#include <algorithm>
#include <chrono>

using namespace std::chrono;

const int Character::SPRITE[13][8] = {
    { 0,1,1,1,1,1,1,1 },
    { 0,1,0,1,0,0,0,1 },
    { 0,1,1,1,1,1,1,1 },
    { 0,0,0,1,0,0,0,1 },
    { 0,0,1,1,1,0,1,1 },
    { 0,1,0,1,0,0,0,1 },
    { 0,1,0,1,1,1,1,1 },
    { 0,1,1,1,1,0,1,0 },
    { 0,0,1,0,1,0,1,0 },
    { 0,0,1,1,1,0,1,0 },
    { 0,1,1,0,1,1,1,0 },
    { 1,0,1,0,1,0,1,0 },
    { 0,1,0,0,1,0,1,0 }
};

Character::Character(int x, int y) : x(x), y(y) {}

void Character::draw(N5110& lcd, bool isInvincible, mbed::Timer& invincibilityTimer) {
    if (!isInvincible || duration_cast<milliseconds>(invincibilityTimer.elapsed_time()).count() % 400 < 200) {
        for (int i = 0; i < SPRITE_HEIGHT; i++) {
            for (int j = 0; j < SPRITE_WIDTH; j++) {
                if (SPRITE[i][j] == 1) {
                    lcd.setPixel(x + j, y + i, true);
                }
            }
        }
    }
}

void Character::move(int dx, int dy, int screenWidth, int screenHeight) {
    x = max(0, min(x + dx, screenWidth - SPRITE_WIDTH));
    y = max(0, min(y + dy, screenHeight - SPRITE_HEIGHT));
}

int Character::getX() const { return x; }
int Character::getY() const { return y; }
int Character::getWidth() const { return SPRITE_WIDTH; }
int Character::getHeight() const { return SPRITE_HEIGHT; }