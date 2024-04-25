#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include "N5110.h"

class GameOverScreen {
public:
    void draw(N5110& lcd, int score);
};

#endif