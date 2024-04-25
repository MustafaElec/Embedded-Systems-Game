#include "MainMenu.h"
#include "N5110.h"

void MainMenu::draw(N5110& lcd) {
    lcd.clear();
    lcd.printString("Main Menu", 0, 0);
    lcd.printString("Start Game", 0, 2);
    lcd.printString("Options", 0, 3);
    lcd.printString("Exit", 0, 4);
    lcd.refresh();
}

void MainMenu::update() {
    // Implement main menu logic here
}