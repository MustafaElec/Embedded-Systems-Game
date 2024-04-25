#include "Character.h"
#include <algorithm>
#include <chrono>

using namespace std::chrono;

Character::Character(int x, int y, int size) : x(x), y(y), size(size) {}

void Character::draw(N5110& lcd, bool isInvincible, mbed::Timer& invincibilityTimer) {
    if (!isInvincible || duration_cast<milliseconds>(invincibilityTimer.elapsed_time()).count() % 400 < 200) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                lcd.setPixel(x + i, y + j, true);
            }
        }
    }
}

void Character::move(int dx, int dy, int screenWidth, int screenHeight) {
    x = max(0, min(x + dx, screenWidth - size));
    y = max(0, min(y + dy, screenHeight - size));
}

int Character::getX() const { return x; }
int Character::getY() const { return y; }
int Character::getSize() const { return size; }
