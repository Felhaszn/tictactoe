#ifndef MENU_HPP
#define MENU_HPP

#include "button.hpp"

class Menu {
private:
    Button play_button;
    Button exit_button;
    Button clear_button;
    bool menu_active;
    bool clear_game_state;

public:
    Menu();
    void draw() const;
    void handle(genv::event ev, bool& start_game, bool& clear_state);
    bool is_active() const { return menu_active; }
    void deactivate() { menu_active = false; }
};

#endif
