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

void Score::draw(N5110& lcd, int health, int maxHealth, int scoreValue) {
    // Display score at the top left
    char scoreBuffer[10];
    snprintf(scoreBuffer, sizeof(scoreBuffer), "%d", scoreValue);
    lcd.printString(scoreBuffer, 0, 0);

    // Display health as small circles at the top right
    for (int i = 0; i < maxHealth; i++) {
        if (i < health) {
            lcd.drawCircle(screenWidth - 5 - i * 6, 2, 2, FILL_BLACK);
        } else {
            lcd.drawCircle(screenWidth - 5 - i * 6, 2, 2, FILL_WHITE);
        }
    }
}