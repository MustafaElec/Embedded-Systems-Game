#ifndef POWERUP_H
#define POWERUP_H

#include "mbed.h"
#include "Character.h"
#include "N5110.h"


enum PowerUpType {
    INVINCIBILITY,
    HEALTH
};

class PowerUp {
public:
    PowerUp(int x, int y, int size, PowerUpType type = INVINCIBILITY);
   void draw(N5110& lcd) const;
    void update(int screenWidth);
    bool checkCollision(const Character& character);
    PowerUpType getType() const;
    void setX(int newX);

private:
    int x;
    int y;
    int size;
    PowerUpType type;
};

#endif