#ifndef GAME_H
#define GAME_H

#include "Character.h"
#include "Obstacle.h"
#include "Spike.h"
#include "Score.h"
#include "PowerUp.h"
#include "GameOverScreen.h"
#include <vector>
#include "mbed.h"

class N5110;
class Joystick;

class Game {
public:
    Game(N5110& lcd, Joystick& joystick, mbed::DigitalIn& joystickButton);

    void run();
    void updateEntities();
    void drawCountdown();

private:
    N5110& lcd;
    Joystick& joystick;
    mbed::DigitalIn& joystickButton;
    GameOverScreen gameOverScreen;

    const int screenHeight = 48;
    const int screenWidth = 84;
    const int squareSize = 5;
    const int movementSpeed = 4;
    const int gravityEffect = 1;
    int invincibilityPeriod = 2000;

    Character character;
    std::vector<Obstacle> obstacles;
    std::vector<Spike> spikes;
    std::vector<PowerUp> powerUps;
    Score score;

   int health;
    int maxHealth;
    bool gameActive;
    bool isInvincible;
    bool isInvinciblePowerUp;
    mbed::Timer invincibilityTimer;

    static const int obstacleWidth = 16;
    static const int obstacleHeight = 6;

    void initializeGame();
    void updateGameLogic();
    void checkCollisions();
    void draw();
    void triggerInvincibility(int duration);
    void triggerInvincibilityPowerUp(int duration);

};

#endif