#ifndef SCREEN_H
#define SCREEN_H

class N5110;

class Screen {
public:
    void draw(N5110& lcd);
    void update();
};

#endif