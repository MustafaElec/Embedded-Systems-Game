#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "Screen.h"

class PauseMenu : public Screen {
public:
    void draw(N5110& lcd);
    void update();
};

#endif