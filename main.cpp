#include "mbed.h"
#include "N5110.h"
#include "Joystick.h"
#include <vector>
#include <cstdlib>

using namespace std;

N5110 lcd(PC_7 /*SCE*/, PA_9 /*RST*/, PB_10 /*D/C*/, PB_5 /*MOSI*/, PB_3 /*SCLK*/, PA_10 /*LED*/);
Joystick joystick(PC_0 /*Vertical*/, PC_1 /*Horizontal*/);
DigitalIn joystickButton(PB_0, PullUp); // Ensure button is configured with PullUp if needed

const int screenHeight = 48;
const int screenWidth = 84;
int pixelX = screenWidth / 2;
int pixelY = screenHeight / 2;
const int squareSize = 5;
int health = 3;
bool gameActive = true;
bool isInvincible = false;
Timer invincibilityTimer;
const int invincibilityPeriod = 2000; // 2 seconds of invincibility
const int movementSpeed = 4; // Increased movement speed
const int gravityEffect = 1; // Gravity effect for diagonal falling

struct Obstacle {
    int x;
    int y;
    int width;
    int height;
};

struct Spike {
    int x;
    Timer timer;
    bool isPeeping;
    bool isFull;
    const int peepingDuration = 2000; // Duration before full appearance
    const int fullDuration = 3000;    // Duration spike stays full
};

vector<Obstacle> obstacles;
vector<Spike> spikes;

void initializeGame() {
    pixelX = screenWidth / 2;
    pixelY = screenHeight / 2;
    health = 3;
    gameActive = true;
    isInvincible = false;
    invincibilityTimer.reset();

    obstacles.clear();
    for (int i = 0; i < 3; i++) {
        obstacles.push_back({rand() % screenWidth, rand() % screenHeight, 15, 5});
    }

    spikes.clear();
    for (int i = 0; i < 3; i++) {
        Spike spike = {rand() % screenWidth, Timer(), true, false};
        spike.timer.start();
        spikes.push_back(spike);
    }
}

void updateGameLogic() {
    if (isInvincible && invincibilityTimer.read_ms() >= invincibilityPeriod) {
        isInvincible = false;
    }

    for (auto& obstacle : obstacles) {
        obstacle.x -= 2;
        if (obstacle.x + obstacle.width < 0) {
            obstacle.x = screenWidth;
            obstacle.y = rand() % (screenHeight - obstacle.height);
        }
    }

    for (auto& spike : spikes) {
        int elapsed = spike.timer.read_ms();

        if (spike.isPeeping && elapsed >= spike.peepingDuration) {
            spike.isPeeping = false;
            spike.isFull = true;
            spike.timer.reset(); // Reset the timer when the spike fully appears
        } else if (spike.isFull && elapsed >= spike.fullDuration) {
            spike.isFull = false;
            spike.x = rand() % screenWidth; // Change location
            spike.timer.reset();
            spike.timer.start();
            spike.isPeeping = true; // Restart the cycle
        }
    }

    if (joystick.get_direction() == N) pixelY -= movementSpeed;
    else if (joystick.get_direction() == S) pixelY += movementSpeed;
    else pixelY += gravityEffect; // Apply gravity

    if (joystick.get_direction() == W) pixelX -= movementSpeed;
    else if (joystick.get_direction() == E) pixelX += movementSpeed;

    pixelX = max(0, min(pixelX, screenWidth - squareSize));
    pixelY = max(0, min(pixelY, screenHeight - squareSize));
}

void checkCollisions() {
    if (isInvincible) return;

    for (const auto& obstacle : obstacles) {
        if (pixelX < obstacle.x + obstacle.width && pixelX + squareSize > obstacle.x &&
            pixelY < obstacle.y + obstacle.height && pixelY + squareSize > obstacle.y) {
            if (!isInvincible) {
                health--;
                isInvincible = true;
                invincibilityTimer.start();
            }
        }
    }

    for (auto& spike : spikes) {
        if (spike.isFull && pixelX < spike.x + 3 && pixelX + squareSize > spike.x) {
            if (!isInvincible) {
                health--;
                isInvincible = true;
                invincibilityTimer.start();
            }
        }
    }

    if (health <= 0) {
        gameActive = false;
    }
}

void draw() {
    lcd.clear();

    if (!isInvincible || invincibilityTimer.read_ms() % 400 < 200) {
        for (int i = 0; i < squareSize; i++) {
            for (int j = 0; j < squareSize; j++) {
                lcd.setPixel(pixelX + i, pixelY + j, true);
            }
        }
    }

    for (const auto& obstacle : obstacles) {
        for (int i = 0; i < obstacle.width; i++) {
            for (int j = 0; j < obstacle.height; j++) {
                lcd.setPixel(obstacle.x + i, obstacle.y + j, true);
            }
        }
    }

    for (const auto& spike : spikes) {
        if (spike.isPeeping) {
            lcd.setPixel(spike.x, screenHeight - 1, true); // Show a dot at the bottom
        } else if (spike.isFull) {
            for (int y = 0; y < screenHeight; y++) {
                lcd.setPixel(spike.x, y, true); // Spike appears fully
            }
        }
    }

    for (int i = 0; i < health; i++) {
        for (int x = screenWidth - 15 + (i * 5); x < screenWidth - 10 + (i * 5); x++) {
            lcd.setPixel(x, 1, true);
        }
    }

    lcd.refresh();
}

int main() {
    lcd.init(LPH7366_1);
    joystick.init();
    initializeGame();

    while (true) {
        if (gameActive) {
            updateGameLogic();
            checkCollisions();
            draw();
        } else {
            lcd.clear();
            lcd.printString("Game Over", 15, 2);
            lcd.refresh();
            // Make sure the button press is properly registered to restart
            while (joystickButton.read() == 1); // Wait for button to be pressed
            //while (joystickButton.read() == 0); // Wait for button to be released
            initializeGame();
        }

        ThisThread::sleep_for(50ms);
    }
}

 