#include "GameOverScreen.h"

void GameOverScreen::draw(N5110& lcd, int score) {
    lcd.clear();
    lcd.printString("Game Over", 0, 2);
    char scoreText[20];
    snprintf(scoreText, sizeof(scoreText), "Score: %d", score);
    lcd.printString(scoreText, 0, 3);
    lcd.refresh();
}