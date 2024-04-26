#ifndef SPIKE_H
#define SPIKE_H

#include "N5110.h"
#include "Character.h"
#include "mbed.h"

class Spike {
public:
    Spike(int x);
    void draw(N5110& lcd, int screenHeight);
    void update(int screenWidth);
    bool checkCollision(const Character& character) const;
private:
    int x;
    bool isPeeping;
    bool isFull;
    mbed::Timer timer;
    const int peepingDuration = 2000;
    const int fullDuration = 3000;
};

#endif