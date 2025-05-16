#include "menu.hpp"
#include "graphics.hpp"

using namespace genv;

Menu::Menu()
    : play_button(350, 300, 100, 40, "Play", [&]() { menu_active = false; }),
      exit_button(350, 400, 100, 40, "Exit", [&]() { exit(0); }),
      clear_button(350, 500, 150, 40, "Clear Game State", [&]() { clear_game_state = true; }),
      menu_active(true), clear_game_state(false) {}

void Menu::draw() const {
    gout << color(0, 0, 0) << move_to(0, 0) << box(800, 800); // Clear screen
    gout << color(255, 255, 255) << move_to(300, 200) << text("Welcome to Tic Tac Toe!");
    play_button.draw();
    exit_button.draw();
    clear_button.draw();
    gout << refresh;
}

void Menu::handle(genv::event ev, bool& start_game, bool& clear_state) {
    if (menu_active) {
        play_button.handle(ev);
        exit_button.handle(ev);
        clear_button.handle(ev);
        if (!menu_active) {
            start_game = true; // Signal to start the game
        }
        if (clear_game_state) {
            clear_state = true; // Signal to clear the game state
            clear_game_state = false; // Reset the flag
        }
    }
}
