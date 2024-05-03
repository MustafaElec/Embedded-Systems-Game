#include "PinNames.h"
#include "mbed.h"
#include "N5110.h"
#include "Joystick.h"
#include "Game.h"

int main() {
    N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);
    Joystick joystick(PC_0, PC_1);
    mbed::DigitalIn joystickButton(PB_0, PullUp);
    mbed::DigitalOut redLED(PC_6);
    mbed::DigitalOut blueLED(PC_5);
    mbed::PwmOut buzzer(PA_15);

    lcd.init(LPH7366_1);
    joystick.init();

    Game game(lcd, joystick, joystickButton, redLED, blueLED, buzzer);
    game.run();

    return 0;
}