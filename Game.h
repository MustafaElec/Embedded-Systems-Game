#ifndef GAME_H
#define GAME_H

#include "N5110.h"
#include "Joystick.h"
#include "Character.h"
#include "Obstacle.h"
#include "Spike.h"
#include "Score.h"
#include "PowerUp.h"
#include "GameOverScreen.h"
#include <vector>
#include "mbed.h"

class Game {
public:
    Game(N5110& lcd, Joystick& joystick, mbed::DigitalIn& joystickButton, mbed::DigitalOut& redLED, mbed::DigitalOut& blueLED, mbed::PwmOut& buzzer);
    void run();
    void updateEntities();

private:
    N5110& lcd;
    Joystick& joystick;
    mbed::DigitalIn& joystickButton;
    mbed::DigitalOut& redLED;
    mbed::DigitalOut& blueLED;
    mbed::PwmOut& buzzer;
    GameOverScreen gameOverScreen;

    static const int screenHeight = 48;
    static const int screenWidth = 84;
    static const int obstacleWidth = 16;
    static const int obstacleHeight = 6;
    static const int movementSpeed = 4;
    static const int gravityEffect = 1;
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

    void initializeGame();
    void updateGameLogic();
    void checkCollisions();
    void draw();
    void drawCountdown();
    void drawMainMenu();
    void playHitSound();
    void playCountdownBeep();
    void playFinalCountdownBeep();
    void playGameOverSound();
    void triggerInvincibility(int duration);
    void triggerInvincibilityPowerUp(int duration);
};

#endif