#include "Game.h"
#include "GameOverScreen.h"
#include "Joystick.h"
#include <chrono>

using namespace std::chrono;

Game::Game(N5110& lcd, Joystick& joystick, mbed::DigitalIn& joystickButton)
    : lcd(lcd), joystick(joystick), joystickButton(joystickButton), character(screenWidth / 2, screenHeight / 2, squareSize), score(screenWidth) {
    initializeGame();
    maxHealth = Score::MAX_HEALTH;
}

void Game::run() {
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
                    break;
                }
                ThisThread::sleep_for(50ms);
            }
        }
        ThisThread::sleep_for(50ms);
    }
}

void PowerUp::setX(int newX) {
    x = newX;
}

void Game::initializeGame() {
    health = 3;
    gameActive = true;
    isInvincible = false;
    invincibilityTimer.stop();
    invincibilityTimer.reset();

    obstacles.clear();
    for (int i = 0; i < 3; i++) {
        obstacles.push_back(Obstacle(rand() % screenWidth, rand() % screenHeight, 15, 5));
    }

    spikes.clear();
    for (int i = 0; i < 3; i++) {
        spikes.push_back(Spike(rand() % screenWidth));
    }

    powerUps.clear();
    powerUps.push_back(PowerUp(84, rand() % 48, 3, INVINCIBILITY));
    powerUps.push_back(PowerUp(84, rand() % 48, 3, HEALTH));

    score.resetScore();
}



void Game::updateGameLogic() {

    static int powerUpCounter = 0;
    static int frameCounter = 0;

    frameCounter++;
    if (frameCounter % 5 == 0) {
        score.increaseScore(1);
    }

    if (isInvincible) {
        auto elapsed_ms = duration_cast<milliseconds>(invincibilityTimer.elapsed_time()).count();
        if (elapsed_ms >= invincibilityPeriod) {
            isInvincible = false;
            invincibilityTimer.stop();
        }
    }

    if (powerUpCounter >= 1000) {
        powerUps.push_back(PowerUp(84, rand() % 48, 3));
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
                triggerInvincibility(5000);
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
        if (spike.checkCollision(character)) {
            triggerInvincibility(2000);
        }
    }

    int dx = 0, dy = gravityEffect;
    if (joystick.get_direction() == N) dy -= movementSpeed;
    else if (joystick.get_direction() == S) dy += movementSpeed;
    if (joystick.get_direction() == W) dx -= movementSpeed;
    else if (joystick.get_direction() == E) dx += movementSpeed;

    character.move(dx, dy, screenWidth, screenHeight);
}

void Game::checkCollisions() {
    if (isInvincible) return;

    for (const auto& obstacle : obstacles) {
        if (obstacle.checkCollision(character)) {
            health--;
            triggerInvincibility(2000);
            if (health <= 0) {
                gameActive = false;
                break;
            }
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

void Game::draw() {
    lcd.clear();
    if (!isInvincible || duration_cast<milliseconds>(invincibilityTimer.elapsed_time()).count() % 400 < 200) {
        character.draw(lcd, isInvincible, invincibilityTimer);
    }

    for (const auto& obstacle : obstacles) {
        obstacle.draw(lcd);
    }

  for (const auto& powerUp : powerUps) {
        powerUp.draw(lcd);
  }
    for (const auto& spike : spikes) {
        spike.draw(lcd, screenHeight);
    }

    score.draw(lcd, health, maxHealth, score.getScore());
    lcd.refresh();
}