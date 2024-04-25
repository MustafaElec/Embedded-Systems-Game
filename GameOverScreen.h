#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include "Screen.h"

class GameOverScreen : public Screen {
public:
    void draw(N5110& lcd);
    void update();
};

#endif