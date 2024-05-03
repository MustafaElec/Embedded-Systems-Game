#include "Score.h"

Score::Score(int width) : screenWidth(width), scoreValue(0) {}

void Score::increaseScore(int increment) {
    scoreValue += increment;
}

int Score::getScore() const {
    return scoreValue;
}

void Score::resetScore() {
    scoreValue = 0;
}

const int HEART_SPRITE[5][5] = {
    { 0, 1, 0, 1, 0 },
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 },
    { 0, 1, 1, 1, 0 },
    { 0, 0, 1, 0, 0 }
};

const int PADLOCK_SPRITE[6][5] = {
    { 0,1,1,1,0 },
    { 0,1,0,1,0 },
    { 1,1,1,1,1 },
    { 1,0,0,0,1 },
    { 1,0,1,0,1 },
    { 1,1,1,1,1 }
};

void Score::drawWithHearts(N5110& lcd, int health, int maxHealth, int scoreValue, bool isInvinciblePowerUp, bool isHit, mbed::Timer& invincibilityTimer) {
    // Display score at the top left
    char scoreBuffer[10];
    snprintf(scoreBuffer, sizeof(scoreBuffer), "%d", scoreValue);
    lcd.printString(scoreBuffer, 0, 0);

    // Display health as hearts at the top right
    for (int i = 0; i < maxHealth; i++) {
        int x = screenWidth - 5 - i * 6;
        int y = 0;

        if (i < health) {
            if (isInvinciblePowerUp && !isHit) {
                // Draw the padlock sprite
                for (int row = 0; row < 6; row++) {
                    for (int col = 0; col < 5; col++) {
                        if (PADLOCK_SPRITE[row][col] == 1) {
                            lcd.setPixel(x + col, y + row, true);
                        }
                    }
                }
            } else {
                // Draw filled heart sprite
                for (int row = 0; row < 5; row++) {
                    for (int col = 0; col < 5; col++) {
                        if (HEART_SPRITE[row][col] == 1) {
                            lcd.setPixel(x + col, y + row, true);
                        }
                    }
                }
            }
        } else {
            lcd.drawRect(x, y, 5, 5, FILL_WHITE);
        }
    }
}