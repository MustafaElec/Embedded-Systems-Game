#include "Spike.h"
#include "N5110.h"
#include "mbed.h"
#include <chrono>

using namespace std::chrono;

const int Spike::SPIKE_SPRITE[48][3] = {
    { 0,0,1 }, { 0,1,0 }, { 1,0,0 }, { 0,1,0 }, { 0,0,1 }, { 0,1,0 },
    { 1,0,0 }, { 0,1,0 }, { 0,0,1 }, { 0,1,0 }, { 1,0,0 }, { 0,1,0 },
    { 0,0,1 }, { 0,1,0 }, { 1,0,0 }, { 0,1,0 }, { 0,0,1 }, { 0,1,0 },
    { 1,0,0 }, { 0,1,0 }, { 0,0,1 }, { 0,1,0 }, { 1,0,0 }, { 0,1,0 },
    { 0,0,1 }, { 0,1,0 }, { 1,0,0 }, { 0,1,0 }, { 0,0,1 }, { 0,1,0 },
    { 1,0,0 }, { 0,1,0 }, { 0,0,1 }, { 0,1,0 }, { 1,0,0 }, { 0,1,0 },
    { 0,0,1 }, { 0,1,0 }, { 1,0,0 }, { 0,1,0 }, { 0,0,1 }, { 0,1,0 },
    { 1,0,0 }, { 0,1,0 }, { 0,0,1 }, { 0,1,0 }, { 1,0,0 }, { 0,1,0 }
};

Spike::Spike(int x) : x(x), isPeeping(true), isFull(false), timer() {
    timer.start();
}

void Spike::draw(N5110& lcd, int screenHeight) {
    if (isPeeping) {
        // Draw hollow rectangles at the bottom and top
        for (int i = 0; i < 3; i++) { // Width of the rectangle
            lcd.setPixel(x + i, 0, true); // Top rectangle
            lcd.setPixel(x + i, screenHeight - 1, true); // Bottom rectangle
        }
    } else if (isFull) {
        for (int y = 0; y < screenHeight; y++) {
            for (int i = 0; i < 3; i++) {
                if (SPIKE_SPRITE[y][i] == 1) {
                    lcd.setPixel(x + i, y, true);
                }
            }
        }
    }
}

void Spike::update(int screenWidth) {
    int elapsed = duration_cast<milliseconds>(timer.elapsed_time()).count();

    if (isPeeping && elapsed >= peepingDuration) {
        isPeeping = false;
        isFull = true;
        timer.reset();
        timer.start();
    } else if (isFull && elapsed >= fullDuration) {
        isFull = false;
        isPeeping = true;
        x = rand() % screenWidth;
        timer.reset();
        timer.start();
    }
}

bool Spike::checkCollision(const Character& character) const {
    if (isFull) {
        for (int y = 0; y < 48; y++) {
            for (int i = 0; i < 3; i++) {
                if (SPIKE_SPRITE[y][i] == 1 &&
                    character.getX() < x + i + 1 && character.getX() + character.getWidth() > x + i &&
                    character.getY() < y + 1 && character.getY() + character.getHeight() > y) {
                    return true;
                }
            }
        }
    }
    return false;
}


