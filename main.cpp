#include "mbed.h"
#include "N5110.h"
#include "Joystick.h"
#include "Game.h"

int main() {
    N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);
    Joystick joystick(PC_0, PC_1);
    mbed::DigitalIn joystickButton(PB_0, PullUp);

    lcd.init(LPH7366_1);
    joystick.init();

    Game game(lcd, joystick, joystickButton);
    game.run();

    return 0;
}