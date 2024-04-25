#include "GameOverScreen.h"
#include "N5110.h"

void GameOverScreen::draw(N5110& lcd) {
    lcd.clear();
    lcd.printString("Game Over", 15, 2);
    lcd.refresh();
}

void GameOverScreen::update() {
    // Implement game over screen logic here
}