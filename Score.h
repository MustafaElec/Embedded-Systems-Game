#ifndef SCORE_H
#define SCORE_H

#include "N5110.h"

class Score {
public:
    explicit Score(int width);
    void increaseScore(int increment);
    int getScore() const;
    void resetScore();
    void drawWithHearts(N5110& lcd, int health, int maxHealth, int scoreValue, bool isInvinciblePowerUp, bool isHit, mbed::Timer& invincibilityTimer);
    static const int MAX_HEALTH = 5;

private:
    int scoreValue;
    int screenWidth;
};

#endif