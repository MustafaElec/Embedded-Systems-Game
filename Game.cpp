#include "Game.h"
#include "GameOverScreen.h"
#include "Joystick.h"
#include <chrono>

using namespace std::chrono;

#define HIT_SOUND_FREQUENCY 1000
#define HIT_SOUND_DURATION 100ms
#define COUNTDOWN_BEEP_FREQUENCY 1000
#define COUNTDOWN_BEEP_DURATION 100ms

#define GAME_OVER_TONE_1_FREQUENCY 262
#define GAME_OVER_TONE_2_FREQUENCY 294
#define GAME_OVER_TONE_3_FREQUENCY 330
#define GAME_OVER_TONE_DURATION 500ms
#define COUNTDOWN_FINAL_BEEP_DURATION 500ms


const int JETSCAPE_SPRITE[30][82]= {
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1 },
	{ 0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,1,0,0,0,0,1,0,0,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,1 },
	{ 0,0,1,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,1,0,0,1,0,0,1,1,0,0,0,1,0,1,1,1,1,0,1,0,0,1,0,0,0,0,0,0,0,1 },
	{ 0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,1,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,1,0,0,0,1,0,1,0,0,1,0,1,0,0,1,0,0,0,0,1,1,1,0 },
	{ 0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,0,1,1,1,0,0,0,0,0,1,0,0,0,1,1,1,0,1,1,0,0,0,1,0,0,1,1,0,1,1,1,0,0,1,0,0,1,0,0,1,1,1,0,0,0 },
	{ 0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,1,0,0,1,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0 },
	{ 0,0,1,1,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0 },
	{ 0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,1,0,0,1,1,1,1,1,1,0,1,0,0,0,0,1,1,1,1,1 },
	{ 0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,1,0,0,1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1 },
	{ 0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,0,0,1,0,1,0,0,0,0,1,1,0,1,1,0,0,1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,0 },
	{ 0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,1,0,1,1,0,0 },
	{ 0,0,0,1,0,0,0,0,1,0,0,0,1,0,1,1,1,1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0 },
	{ 0,0,0,1,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,0,1,0,1,1,1,1,0,1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0 },
	{ 0,0,0,1,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,0,1,0,1,0,0,0,0,1,0,1,0,0,1,0,1,0,1,0,0,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0 },
	{ 0,0,0,1,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,0,0,0,0,1,0,1,0,0,1,0,1,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1 },
	{ 0,0,0,1,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,0,0,0,0,1,0,1,0,0,1,0,1,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1 },
	{ 0,0,0,1,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0,1,0,1,1,0,0,0,1,0,1,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1 },
	{ 1,1,1,1,0,0,0,0,1,0,0,0,1,0,1,1,1,1,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1,0,0,1,0,0,1,1,1,1,1,0,1,0,0,0,1,1,0,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,0,1,0,0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1 },
	{ 1,0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,1,1,0,0,1,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 1,0,0,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
};

Game::Game(N5110& lcd, Joystick& joystick, mbed::DigitalIn& joystickButton, mbed::DigitalOut& redLED, mbed::DigitalOut& blueLED, mbed::PwmOut& buzzer)
    : lcd(lcd), joystick(joystick), joystickButton(joystickButton), redLED(redLED), blueLED(blueLED), buzzer(buzzer), character(0, screenHeight - 13), score(screenWidth) {
    initializeGame();
    maxHealth = Score::MAX_HEALTH;
}

void Game::drawCountdown() {
    lcd.clear();
    lcd.printString("Ready?", 0, 0);

    for (int i = 3; i > 0; i--) {
        lcd.clear();
        lcd.printString("Ready?", 20, 1);
        char countdownStr[2];
        snprintf(countdownStr, sizeof(countdownStr), "%d", i);
        lcd.printString(countdownStr, 36, 3);
        lcd.refresh();

        playCountdownBeep();
        ThisThread::sleep_for(1s - COUNTDOWN_BEEP_DURATION);
    }

    lcd.clear();
    lcd.printString("GO!", 30, 2);
    lcd.refresh();
    playFinalCountdownBeep();
}

void Game::playCountdownBeep() {
    buzzer.period_us((float)1000000.0f / (float)COUNTDOWN_BEEP_FREQUENCY);
    buzzer.pulsewidth_us(buzzer.read_period_us() / 2);
    ThisThread::sleep_for(COUNTDOWN_BEEP_DURATION);
    buzzer.pulsewidth_us(0);
    
}
void Game::playFinalCountdownBeep() {
    buzzer.period_us((float)1000000.0f / (float)COUNTDOWN_BEEP_FREQUENCY);
    buzzer.pulsewidth_us(buzzer.read_period_us() / 2);
    ThisThread::sleep_for(COUNTDOWN_FINAL_BEEP_DURATION);
    buzzer.pulsewidth_us(0);
}

void Game::drawMainMenu() {
    lcd.clear();

    // Draw the sprite
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 82; j++) {
            if (JETSCAPE_SPRITE[i][j] == 1) {
                lcd.setPixel(j, i, true);
            }
        }
    }

    lcd.printString("Press to start", 0, 4);
    lcd.refresh();

    // Wait for joystick button press to start the game
    while (true) {
        if (joystickButton.read() == 0) {
            while (joystickButton.read() == 0); // Wait for button release
            break;
        }
        ThisThread::sleep_for(50ms);
    }
}

void Game::run() {
    drawMainMenu();
    drawCountdown();
    

    bool ledState = false;
    Timer ledTimer;
    ledTimer.start();

    while (true) {
        if (gameActive) {
            updateGameLogic();
            draw();

            // Alternate red and blue LED colors
            if (ledTimer.elapsed_time() >= 500ms) {
                ledState = !ledState;
                redLED = ledState;
                blueLED = !ledState;
                ledTimer.reset();
            }
        } else {
            gameOverScreen.draw(lcd, score.getScore());
            lcd.refresh();
            redLED = 0;
            blueLED = 0;
            playGameOverSound();
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

void Game::playGameOverSound() {
    buzzer.period_us((float)1000000.0f / (float)GAME_OVER_TONE_1_FREQUENCY);
    buzzer.pulsewidth_us(buzzer.read_period_us() / 2);
    ThisThread::sleep_for(GAME_OVER_TONE_DURATION);

    buzzer.period_us((float)1000000.0f / (float)GAME_OVER_TONE_2_FREQUENCY);
    buzzer.pulsewidth_us(buzzer.read_period_us() / 2);
    ThisThread::sleep_for(GAME_OVER_TONE_DURATION);

    buzzer.period_us((float)1000000.0f / (float)GAME_OVER_TONE_3_FREQUENCY);
    buzzer.pulsewidth_us(buzzer.read_period_us() / 2);
    ThisThread::sleep_for(GAME_OVER_TONE_DURATION * 2);

    buzzer.pulsewidth_us(0);
}

void Game::initializeGame() {
    health = 3;
    gameActive = true;
    isInvinciblePowerUp = false;
    isInvincible = false;
    invincibilityTimer.stop();
    invincibilityTimer.reset();

    obstacles.clear();
    for (int i = 0; i < 3; i++) {
        obstacles.push_back(Obstacle(rand() % screenWidth, rand() % (screenHeight - obstacleHeight)));
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

    if (isInvinciblePowerUp) {
        auto elapsed_ms = duration_cast<milliseconds>(invincibilityTimer.elapsed_time()).count();
        if (elapsed_ms >= invincibilityPeriod) {
            isInvinciblePowerUp = false;
            invincibilityTimer.stop();
        }
    }

    if (powerUpCounter >= 20) {
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
    if (isInvinciblePowerUp) return;

    for (auto& obstacle : obstacles) {
        if (obstacle.checkCollision(character)) {
            health--;
            character.setHit(true);
            triggerInvincibilityPowerUp(2000);
            playHitSound();
            if (health <= 0) {
                gameActive = false;
                break;
            }
        }
    }

    for (auto& spike : spikes) {
        if (spike.checkCollision(character)) {
            health--;
            character.setHit(true);
            triggerInvincibilityPowerUp(2000);
            playHitSound();
            if (health <= 0) {
                gameActive = false;
                break;
            }
        }
    }
}

void Game::playHitSound() {
    buzzer.period_us((float)1000000.0f / (float)HIT_SOUND_FREQUENCY);
    buzzer.pulsewidth_us(buzzer.read_period_us() / 2);
    ThisThread::sleep_for(HIT_SOUND_DURATION);
    buzzer.pulsewidth_us(0);
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
