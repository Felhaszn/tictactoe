#ifndef MENU_HPP
#define MENU_HPP

#include "button.hpp"
#include "widget.hpp"

class Menu : public Widget {
private:
    Button play_button;
    Button exit_button;
    Button clear_button;
    bool menu_active;
    bool clear_game_state;

public:
    Menu(int x, int y, int width, int height);
    void draw() const override; // Matches Widget's draw() signature
    void handle(genv::event ev) override; // Matches Widget's handle() signature
    void handle(genv::event ev, bool& start_game, bool& clear_state); // Additional overload
    bool is_active() const { return menu_active; }
    void deactivate() { menu_active = false; }
};

#endif
