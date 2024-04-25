#include "Obstacle.h"
#include <cstdlib>

Obstacle::Obstacle(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}

void Obstacle::draw(N5110& lcd) const { // Marked as const
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            lcd.setPixel(x + i, y + j, true);
        }
    }
}

bool Obstacle::checkCollision(const Character& character) const { // Marked as const
    return character.getX() < x + width && character.getX() + character.getSize() > x &&
           character.getY() < y + height && character.getY() + character.getSize() > y;
}

void Obstacle::move(int dx) {
    x += dx;
}

void Obstacle::reset(int screenWidth, int screenHeight) {
    x = screenWidth;
    y = rand() % (screenHeight - height);
}

bool Obstacle::isOffScreen(int screenWidth) const { // New method to check if the obstacle is off screen
    return x + width < 0;
}
