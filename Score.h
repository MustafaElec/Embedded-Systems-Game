#ifndef SCORE_H
#define SCORE_H

#include "N5110.h"

class Score {
public:
    Score(int screenWidth);
    void draw(N5110& lcd, int health);

private:
    int screenWidth;
};

#endif
