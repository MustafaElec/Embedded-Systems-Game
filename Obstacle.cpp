#include "Obstacle.h"

const int Obstacle::POLICECAR_SPRITE[6][16] = {
    { 0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1 },
	{ 1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0 },
	{ 1,1,0,0,1,1,1,0,1,1,1,0,1,1,0,0 },
	{ 0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,0 },
	{ 0,0,0,0,1,1,1,0,1,1,1,0,0,0,0,1 }
};

Obstacle::Obstacle(int x) : x(x), y(rand() % (48 - obstacleHeight)) {}


void Obstacle::draw(N5110& lcd) {
    for (int i = 0; i < obstacleHeight; i++) {
        for (int j = 0; j < obstacleWidth; j++) {
            if (POLICECAR_SPRITE[i][j] == 1) {
                lcd.setPixel(x + j, y + i, true);
            }
        }
    }
}

bool Obstacle::checkCollision(const Character& character) {
    return character.getX() < x + obstacleWidth && character.getX() + character.getWidth() > x &&
           character.getY() < y + obstacleHeight && character.getY() + character.getHeight() > y;
}

void Obstacle::move(int dx) {
    x += dx;
}

bool Obstacle::isOffScreen(int screenWidth) {
    return x < -obstacleWidth;
}

void Obstacle::reset(int screenWidth, int screenHeight) {
    x = screenWidth;
    y = rand() % (screenHeight - obstacleHeight);
}

int Obstacle::getX() const { return x; }
int Obstacle::getY() const { return y; }
int Obstacle::getWidth() const { return obstacleWidth; }
int Obstacle::getHeight() const { return obstacleHeight; }