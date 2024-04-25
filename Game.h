#ifndef GAME_H
#define GAME_H

#include "Character.h"
#include "Obstacle.h"
#include "Spike.h"
#include "Score.h"
#include <vector>
#include "mbed.h"

class N5110;
class Joystick;

class Game {
public:
    Game(N5110& lcd, Joystick& joystick, mbed::DigitalIn& joystickButton);

    void run();

private:
    N5110& lcd;
    Joystick& joystick;
    mbed::DigitalIn& joystickButton;

    const int screenHeight = 48;
    const int screenWidth = 84;
    const int squareSize = 5;
    const int movementSpeed = 4;
    const int gravityEffect = 1;
    const int invincibilityPeriod = 2000;

    Character character;
    std::vector<Obstacle> obstacles;
    std::vector<Spike> spikes;
    Score score;

    int health = 3;
    bool gameActive = true;
    bool isInvincible = false;
    mbed::Timer invincibilityTimer;

    void initializeGame();
    void updateGameLogic();
    void checkCollisions();
    void draw();
    void triggerInvincibility();
};

#endif
