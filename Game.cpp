#include "Game.h"
#include "GameOverScreen.h"
#include "Joystick.h"
#include <chrono>

using namespace std::chrono;

Game::Game(N5110& lcd, Joystick& joystick, mbed::DigitalIn& joystickButton)
    : lcd(lcd), joystick(joystick), joystickButton(joystickButton), character(0, screenHeight - 13), score(screenWidth) {
    initializeGame();
    maxHealth = Score::MAX_HEALTH;
}

void Game::run() {
    drawCountdown();

    while (true) {
        if (gameActive) {
            updateGameLogic();
            draw();
        } else {
            gameOverScreen.draw(lcd, score.getScore());
            lcd.refresh();
            
            // Wait for joystick button press to restart the game
            while (true) {
                if (joystickButton.read() == 0) {
                    while (joystickButton.read() == 0); // Wait for button release
                    initializeGame();
                    drawCountdown();
                    break;
                }
                ThisThread::sleep_for(50ms);
            }
        }
        ThisThread::sleep_for(50ms);
    }
}

void Game::initializeGame() {
    health = 3;
    gameActive = true;
    isInvincible = false;
    invincibilityTimer.stop();
    invincibilityTimer.reset();

    obstacles.clear();
    for (int i = 0; i < 3; i++) {
        obstacles.push_back(Obstacle(screenWidth + i * 50));
    }

    powerUps.clear();
    powerUps.push_back(PowerUp(screenWidth, INVINCIBILITY));
    powerUps.push_back(PowerUp(screenWidth + 100, HEALTH));
    spikes.clear();

    for (int i = 0; i < 3; i++) {
        spikes.push_back(Spike(rand() % screenWidth));
    }

    score.resetScore();
}

void Game::updateGameLogic() {
    static int powerUpCounter = 0;
    static int obstacleCounter = 0;
    static int frameCounter = 0;

    frameCounter++;
    if (frameCounter % 5 == 0) {
        score.increaseScore(1);
    }

    if (isInvinciblePowerUp) {
        auto elapsed_ms = duration_cast<milliseconds>(invincibilityTimer.elapsed_time()).count();
        if (elapsed_ms >= invincibilityPeriod) {
            isInvinciblePowerUp = false;
            invincibilityTimer.stop();
        }
    }

    obstacleCounter++;
    if (obstacleCounter >= 1000) {
        obstacles.push_back(Obstacle(screenWidth));
        obstacleCounter = 0;
    }

    powerUpCounter++;
    if (powerUpCounter >= 2000) {
        powerUps.push_back(PowerUp(screenWidth));
        powerUpCounter = 0;
    }

    updateEntities();
    checkCollisions();
}

void Game::updateEntities() {
    for (auto& powerUp : powerUps) {
        powerUp.update(screenWidth);
        if (powerUp.checkCollision(character)) {
            if (powerUp.getType() == INVINCIBILITY) {
                triggerInvincibilityPowerUp(5000);
            } else if (powerUp.getType() == HEALTH) {
                if (health < maxHealth) {
                    health++;
                    powerUp.setX(screenWidth);
                }
            }
        }
    }

    for (auto& obstacle : obstacles) {
        obstacle.move(-2);
        if (obstacle.isOffScreen(screenWidth)) {
            obstacle.reset(screenWidth, screenHeight);
        }
    }

    for (auto& spike : spikes) {
        spike.update(screenWidth);
    }

    int dx = 0, dy = gravityEffect;
    if (joystick.get_direction() == N) dy -= movementSpeed;
    else if (joystick.get_direction() == S) dy += movementSpeed;
    if (joystick.get_direction() == W) dx -= movementSpeed;
    else if (joystick.get_direction() == E) dx += movementSpeed;

    character.move(dx, dy, screenWidth, screenHeight);

     bool isAboveGround = (character.getY() < screenHeight - character.getHeight() - 1);
     character.draw(lcd, isAboveGround);
}


void Game::checkCollisions() {
    if (isInvincible) return;

    bool isHit = false;

    for (auto& obstacle : obstacles) {
        if (obstacle.checkCollision(character)) {
            isHit = true;
            break;
        }
    }

    for (auto& spike : spikes) {
        if (spike.checkCollision(character)) {
            isHit = true;
            break;
        }
    }

    if (isHit) {
        health--;
        character.setHit(true);
        triggerInvincibility(2000);
        if (health <= 0) {
            gameActive = false;
        }
    }
}

void Game::triggerInvincibility(int duration) {
    if (!isInvincible) {
        isInvincible = true;
        invincibilityTimer.reset();
        invincibilityTimer.start();
        invincibilityPeriod = duration;
    }
}

void Game::triggerInvincibilityPowerUp(int duration) {
    if (!isInvinciblePowerUp) {
        isInvinciblePowerUp = true;
        invincibilityTimer.reset();
        invincibilityTimer.start();
        invincibilityPeriod = duration;
    }
}

void Game::drawCountdown() {
    lcd.clear();
    lcd.printString("Ready?", 0, 0);

    for (int i = 3; i > 0; i--) {
        lcd.clear();
        lcd.printString("Ready?", 0, 0);
        char countdownStr[2];
        snprintf(countdownStr, sizeof(countdownStr), "%d", i);
        lcd.printString(countdownStr, 3, 3);
        lcd.refresh();
        ThisThread::sleep_for(1s);
    }
}

void Game::draw() {
    lcd.clear();
    character.draw(lcd, character.getY() < screenHeight - character.getHeight() - 1);

    for (auto& obstacle : obstacles) {
        obstacle.draw(lcd);
    }

    for (auto& powerUp : powerUps) {
        powerUp.draw(lcd);
    }

    for (auto& spike : spikes) {
        spike.draw(lcd, screenHeight);
    }

    score.drawWithHearts(lcd, health, maxHealth, score.getScore(), isInvinciblePowerUp, character.isHit(), invincibilityTimer);
    lcd.refresh();
}