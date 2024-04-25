#ifndef OPTIONS_MENU_H
#define OPTIONS_MENU_H

#include "Screen.h"

class OptionsMenu : public Screen {
public:
    void draw(N5110& lcd);
    void update();
};

#endif