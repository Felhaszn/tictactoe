#ifndef MENU_HPP
#define MENU_HPP

#include "button.hpp"
#include "widget.hpp"

class Menu : public Widget {
private:
    Button small_grid_button;
    Button medium_grid_button;
    Button large_grid_button;
    Button exit_button;
    Button clear_button;
    bool menu_active;
    bool clear_game_state;

public:
    Menu(int x, int y, int width, int height);
    void draw() const override; // Matches Widget's draw() signature
    void handle(genv::event ev) override; // Correctly overrides Widget's handle() function
    void handle(genv::event ev, bool& start_game, bool& clear_state, int& grid_size); // Overload for extended functionality
    bool is_active() const { return menu_active; }
    void deactivate() { menu_active = false; }
};

#endif
