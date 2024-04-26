#include "Obstacle.h"


Obstacle::Obstacle(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}

void Obstacle::draw(N5110& lcd) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            lcd.setPixel(x + i, y + j, true);
        }
    }
}

bool Obstacle::checkCollision(const Character& character) {
    return character.getX() < x + width && character.getX() + character.getWidth() > x &&
           character.getY() < y + height && character.getY() + character.getHeight() > y;
}

void Obstacle::move(int dx) {
    x += dx;
}

bool Obstacle::isOffScreen(int screenWidth) {
    return x < -width;
}

void Obstacle::reset(int screenWidth, int screenHeight) {
    x = screenWidth;
    y = rand() % (screenHeight - height);
}

int Obstacle::getX() const { return x; }
int Obstacle::getY() const { return y; }
int Obstacle::getWidth() const { return width; }
int Obstacle::getHeight() const { return height; }