#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Screen.h"

class MainMenu : public Screen {
public:
    void draw(N5110& lcd);
    void update();
};

#endif