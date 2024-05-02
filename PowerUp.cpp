#include "PowerUp.h"
#include "N5110.h"

PowerUp::PowerUp(int x, PowerUpType type) : x(x), y(rand() % (48 - 5)), size(5), type(type) {}

void PowerUp::draw(N5110& lcd) {
    if (type == INVINCIBILITY) {
        // Draw the invincibility power-up sprite on the LCD
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 7; j++) {
                if (STOPWATCH_SPRITE[i][j] == 1) {
                    lcd.setPixel(x + j, y + i, true);
                }
            }
        }
    } else if (type == HEALTH) {
        // Draw the heart power-up sprite on the LCD
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 7; j++) {
                if (HEART_SPRITE[i][j] == 1) {
                    lcd.setPixel(x + j, y + i, true);
                }
            }
        }
    }
}

void PowerUp::update(int screenWidth) {
    x -= 2;
    if (x < -size) {
        x = 2 * screenWidth + rand() % 20; //double the distance between powerups as a minimum
        y = rand() % (48 - size);
    }
}

bool PowerUp::checkCollision(const Character& character) {
    // Check collision between the power-up and the character
    return (character.getX() < x + size && character.getX() + character.getWidth() > x &&
            character.getY() < y + size && character.getY() + character.getHeight() > y);
}

PowerUpType PowerUp::getType()  {
    return type;
}

void PowerUp::setX(int newX) {
    x = newX;
}