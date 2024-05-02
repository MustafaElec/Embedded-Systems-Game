#include "Character.h"
#include <algorithm>
#include <chrono>

using namespace std::chrono;

const int Character::RUNNING_SPRITE_1[11][6] = {
    { 0,1,1,1,1,1 },
    { 0,1,1,0,1,1 },
    { 0,1,0,0,0,1 },
    { 0,0,1,1,1,0 },
    { 1,1,0,1,0,0 },
    { 1,1,1,1,0,0 },
    { 1,1,1,1,1,0 },
    { 1,1,0,1,0,0 },
    { 0,0,0,1,1,1 },
    { 0,0,1,0,0,0 },
    { 0,1,0,0,0,0 }
};

const int Character::RUNNING_SPRITE_2[11][6] = {
    { 0,1,1,1,1,1 },
    { 0,1,1,0,1,1 },
    { 0,1,0,0,0,1 },
    { 0,0,1,1,1,0 },
    { 1,1,0,1,0,0 },
    { 1,1,1,1,0,0 },
    { 1,1,1,1,1,0 },
    { 1,0,0,1,0,0 },
    { 0,1,1,1,0,0 },
    { 0,0,0,0,1,0 },
    { 0,0,0,0,0,1 }
};

const int Character::FLYING_SPRITE[11][9] = {
    { 0,0,0,0,1,1,1,1,1 },
    { 0,0,0,0,1,1,0,1,1 },
    { 0,0,0,0,1,0,0,0,1 },
    { 0,0,0,0,0,1,1,1,0 },
    { 0,0,0,1,1,0,1,0,0 },
    { 0,0,0,1,1,1,1,0,0 },
    { 0,0,1,1,1,1,1,1,0 },
    { 0,1,0,1,1,0,1,0,0 },
    { 1,0,0,1,0,0,1,1,1 },
    { 0,0,1,0,0,1,0,0,0 },
    { 0,1,0,0,0,0,0,0,0 }
};


const int Character::GOTHIT_SPRITE[11][7] = {
    { 1,1,1,1,1,0,1 },
    { 1,1,0,1,1,0,1 },
    { 1,0,0,0,1,0,1 },
    { 1,0,1,0,1,0,1 },
    { 0,1,1,1,0,0,0 },
    { 0,0,1,0,0,0,1 },
    { 1,0,1,0,1,0,0 },
    { 0,1,1,1,0,0,0 },
    { 0,0,1,0,0,0,0 },
    { 0,1,1,1,0,0,0 },
    { 1,0,0,0,1,0,0 }
};

Character::Character(int x, int y) : x(x), y(y), hitState(false) {}

void Character::draw(N5110& lcd, bool isAboveGround) {
    const int* sprite;
    int spriteWidth;
    int spriteHeight = 11;

    if (hitState) {
        auto elapsed_ms = duration_cast<milliseconds>(hitTimer.elapsed_time()).count();
        if (elapsed_ms < 500) {
            sprite = &GOTHIT_SPRITE[0][0];
            spriteWidth = 7;
        } else {
            hitState = false;
            hitTimer.stop();
            hitTimer.reset();
        }
    }

    if (!hitState) {
        if (isAboveGround) {
            sprite = &FLYING_SPRITE[0][0];
            spriteWidth = 9;
        } else {
            static int frame = 0;
            frame = (frame + 1) % 20; // Alternate every 20 frames

            if (frame < 10) {
                sprite = &RUNNING_SPRITE_1[0][0];
            } else {
                sprite = &RUNNING_SPRITE_2[0][0];
            }
            spriteWidth = 6;
        }
    }

    // Draw the sprite pixels
    for (int i = 0; i < spriteHeight; i++) {
        for (int j = 0; j < spriteWidth; j++) {
            if (sprite[i * spriteWidth + j] == 1) {
                lcd.setPixel(x + j, y + i, true);
            }
        }
    }
}

void Character::move(int dx, int dy, int screenWidth, int screenHeight) {
    x = max(0, min(x + dx, screenWidth - 9));
    y = max(0, min(y + dy, screenHeight - 11));
}

int Character::getX() const { return x; }
int Character::getY() const { return y; }
int Character::getWidth() const { return 9; }
int Character::getHeight() const { return 11; }

bool Character::isHit() const {
    return hitState;
}

void Character::setHit(bool hit) {
    hitState = hit;
    if (hit) {
        hitTimer.start();
    }
}