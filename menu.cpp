#include "menu.hpp"
#include "graphics.hpp"

using namespace genv;

Menu::Menu(int x, int y, int width, int height)
    : Widget(x, y, width, height),
      small_grid_button(x + width / 2 - 75, y + 100, 150, 40, "15x15 Grid", [&]() { menu_active = false; }),
      medium_grid_button(x + width / 2 - 75, y + 200, 150, 40, "20x20 Grid", [&]() { menu_active = false; }),
      large_grid_button(x + width / 2 - 75, y + 300, 150, 40, "30x30 Grid", [&]() { menu_active = false; }),
      exit_button(x + width / 2 - 50, y + 500, 100, 40, "Exit", [&]() { std::exit(0); }),
      clear_button(x + width / 2 - 75, y + 600, 150, 40, "Clear Game State", [&]() { clear_game_state = true; }),
      menu_active(true), clear_game_state(false) {}

void Menu::draw() const {
    genv::gout.load_font("LiberationSans-Regular.ttf", 20); // Load the font
    genv::gout << genv::color(0, 0, 0) << genv::move_to(x, y) << genv::box(width, height); // Clear screen
    genv::gout << genv::color(255, 255, 255) << genv::move_to(400 - gout.twidth("Select Grid Size:")/2, y + 50) << genv::text("Select Grid Size:");
    small_grid_button.draw();
    medium_grid_button.draw();
    large_grid_button.draw();
    exit_button.draw();
    clear_button.draw();
    genv::gout << genv::refresh;
}

void Menu::handle(genv::event ev) {
    // Default handle implementation for Widget
    bool dummy_start_game = false;
    bool dummy_clear_state = false;
    int dummy_grid_size = 0;
    handle(ev, dummy_start_game, dummy_clear_state, dummy_grid_size);
}

void Menu::handle(genv::event ev, bool& start_game, bool& clear_state, int& grid_size) {
    if (menu_active) {
        small_grid_button.handle(ev);
        medium_grid_button.handle(ev);
        large_grid_button.handle(ev);
        exit_button.handle(ev);
        clear_button.handle(ev);

        if (!menu_active) {
            if (small_grid_button.is_clicked()) {
                grid_size = 15;
            } else if (medium_grid_button.is_clicked()) {
                grid_size = 20;
            } else if (large_grid_button.is_clicked()) {
                grid_size = 30;
            }
            start_game = true; // Signal to start the game
        }

        if (clear_game_state) {
            clear_state = true; // Signal to clear the game state
            clear_game_state = false; // Reset the flag
        }
    }
}
