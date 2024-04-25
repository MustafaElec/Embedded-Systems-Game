#include "OptionsMenu.h"
#include "N5110.h"

void OptionsMenu::draw(N5110& lcd) {
    lcd.clear();
    lcd.printString("Options", 0, 0);
    lcd.printString("Option 1", 0, 2);
    lcd.printString("Option 2", 0, 3);
    lcd.printString("Back", 0, 4);
    lcd.refresh();
}

void OptionsMenu::update() {
    // Implement options menu logic here
}