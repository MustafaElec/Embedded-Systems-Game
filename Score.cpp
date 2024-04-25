#include "Score.h"

Score::Score(int screenWidth) : screenWidth(screenWidth) {}

void Score::draw(N5110& lcd, int health) {
    for (int i = 0; i < health; i++) {
        for (int x = screenWidth - 15 + (i * 5); x < screenWidth - 10 + (i * 5); x++) {
            lcd.setPixel(x, 1, true);
        }
    }
}
