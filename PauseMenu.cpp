#include "PauseMenu.h"
#include "N5110.h"

void PauseMenu::draw(N5110& lcd) {
    lcd.clear();
    lcd.printString("Pause", 0, 0);
    lcd.printString("Resume", 0, 2);
    lcd.printString("Options", 0, 3);
    lcd.printString("Quit", 0, 4);
    lcd.refresh();
}

void PauseMenu::update() {
    // Implement pause menu logic here
}