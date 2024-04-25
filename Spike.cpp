#include "Spike.h"
#include <chrono>

using namespace std::chrono;

Spike::Spike(int x) : x(x), isPeeping(true), isFull(false), timer() {
    timer.start();
}

void Spike::draw(N5110& lcd, int screenHeight) const {
    if (isPeeping) {
        lcd.setPixel(x, screenHeight - 1, true);
    } else if (isFull) {
        for (int y = 0; y < screenHeight; y++) {
            lcd.setPixel(x, y, true);
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
    return isFull && character.getX() < x + 3 && character.getX() + character.getSize() > x;
}
