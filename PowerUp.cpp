#include "PowerUp.h"
#include "N5110.h"

PowerUp::PowerUp(int x, int y, int size, PowerUpType type) : x(x), y(y), size(size), type(type) {}

void PowerUp::draw(N5110& lcd) const{
    if (type == INVINCIBILITY) {
        // Draw the invincibility power-up sprite on the LCD
        // You can replace this with your own invincibility sprite drawing code
        lcd.drawRect(x, y, size, size, FILL_BLACK);
    } else if (type == HEALTH) {
        // Draw the heart power-up sprite on the LCD
        // You can replace this with your own heart sprite drawing code
        lcd.drawCircle(x + size / 2, y + size / 2, size / 2, FILL_BLACK);
    }
}

void PowerUp::update(int screenWidth) {
    x -= 2;
    if (x < -size) {
        x = screenWidth;
    }
}

bool PowerUp::checkCollision(const Character& character) {
    // Check collision between the power-up and the character
    // You can replace this with your own collision detection logic
    return (character.getX() < x + size && character.getX() + character.getSize() > x &&
            character.getY() < y + size && character.getY() + character.getSize() > y);
}

PowerUpType PowerUp::getType() const {
    return type;
}