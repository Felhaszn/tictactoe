#include "menu.hpp"
#include "graphics.hpp"

using namespace genv;

Menu::Menu(int x, int y, int width, int height)
    : Widget(x, y, width, height),
      play_button(x + width / 2 - 50, y + 100, 100, 40, "Play", [&]() { menu_active = false; }),
      exit_button(x + width / 2 - 50, y + 200, 100, 40, "Exit", [&]() { std::exit(0); }),
      clear_button(x + width / 2 - 75, y + 300, 150, 40, "Clear Game State", [&]() { clear_game_state = true; }),
      menu_active(true), clear_game_state(false) {}

void Menu::draw() const {
    genv::gout << genv::color(0, 0, 0) << genv::move_to(x, y) << genv::box(width, height); // Clear screen
    genv::gout << genv::color(255, 255, 255) << genv::move_to(x + 50, y + 50) << genv::text("Welcome to Tic Tac Toe!");
    play_button.draw();
    exit_button.draw();
    clear_button.draw();
    genv::gout << genv::refresh;
}

void Menu::handle(genv::event ev) {
    // Default handle implementation for Widget
    bool dummy_start_game = false;
    bool dummy_clear_state = false;
    handle(ev, dummy_start_game, dummy_clear_state);
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
