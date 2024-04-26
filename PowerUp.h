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
    void draw(N5110& lcd);
    void update(int screenWidth);
    bool checkCollision(const Character& character);
    PowerUpType getType();
    void setX(int newX);
    int getX() const;
    int getY() const;
    int getSize() const;

 const int HEART_SPRITE[7][7]= {
	{ 0,1,1,1,1,1,0 },
	{ 1,0,0,1,0,0,1 },
	{ 1,0,0,1,0,0,1 },
	{ 1,1,0,0,0,1,1 },
	{ 0,1,1,0,1,1,0 },
	{ 0,0,1,1,1,0,0 },
	{ 0,0,0,1,0,0,0 }
};

const int STOPWATCH_SPRITE[7][7]= {
	{ 0,1,1,1,1,1,0 },
	{ 1,0,0,1,0,0,1 },
	{ 1,0,0,1,0,0,1 },
	{ 1,0,0,1,1,1,1 },
	{ 1,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,1 },
	{ 0,1,1,1,1,1,0 }
};

private:
    int x;
    int y;
    int size;
    PowerUpType type;
};

#endif