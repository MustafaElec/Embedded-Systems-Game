#include "Game.h"
#include "GameOverScreen.h"
#include "Joystick.h"
#include <chrono>

using namespace std::chrono;

Game::Game(N5110& lcd, Joystick& joystick, mbed::DigitalIn& joystickButton)
    : lcd(lcd), joystick(joystick), joystickButton(joystickButton), character(screenWidth / 2, screenHeight / 2, squareSize), score(screenWidth) {
    initializeGame();
}

void Game::run() {
    while (true) {
        if (gameActive) {
            updateGameLogic();
            checkCollisions();
            draw();
        } else {
            GameOverScreen gameOverScreen;
            gameOverScreen.draw(lcd);

            while (joystickButton.read() == 1); // Wait for button press
            initializeGame();
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
        obstacles.push_back(Obstacle(rand() % screenWidth, rand() % screenHeight, 15, 5));
    }

    spikes.clear();
    for (int i = 0; i < 3; i++) {
        spikes.push_back(Spike(rand() % screenWidth));
    }
}

void Game::updateGameLogic() {
    if (isInvincible && duration_cast<milliseconds>(invincibilityTimer.elapsed_time()).count() >= invincibilityPeriod) {
        isInvincible = false;
        invincibilityTimer.stop();  // Stop the timer since invincibility has ended
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

    int dx = 0;
    int dy = gravityEffect;

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
            triggerInvincibility();
            break;
        }
    }

    for (const auto& spike : spikes) {
        if (spike.checkCollision(character)) {
            triggerInvincibility();
            break;
        }
    }

    if (health <= 0) {
        gameActive = false;
    }
}

void Game::triggerInvincibility() {
    if (!isInvincible) {
        health--;
        isInvincible = true;
        invincibilityTimer.reset();
        invincibilityTimer.start();
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

    for (const auto& spike : spikes) {
        spike.draw(lcd, screenHeight);
    }

    score.draw(lcd, health);

    lcd.refresh();
}
