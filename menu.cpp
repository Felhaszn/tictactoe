#include "menu.hpp"
#include "square.hpp"
#include "graphics.hpp"
#include <cstdio> // Include for std::remove
#include <iostream> // Include for std::cerr

using namespace genv;

Menu::Menu(int x, int y, int width, int height)
    : Widget(x, y, width, height),
      small_grid_button(x + width / 2 - 75, y + 200, 150, 40, "15x15 Grid", [&]() { menu_active = false; }),
      medium_grid_button(x + width / 2 - 75, y + 300, 150, 40, "20x20 Grid", [&]() { menu_active = false; }),
      large_grid_button(x + width / 2 - 75, y + 400, 150, 40, "30x30 Grid", [&]() { menu_active = false; }),
      exit_button(x + width / 2 - 50, y + 500, 100, 40, "Exit", [&]() { std::exit(0); }),
      clear_button(x + width / 2 - 75, y + 740, 150, 40, "Clear Game State", [&]() { clear_game_state = true; }),
      menu_active(true), clear_game_state(false) {}

void Menu::draw() const {
    genv::gout << genv::color(0, 0, 0) << genv::move_to(x, y) << genv::box(width, height); // Clear screen

    // Draw the menu background with adjusted positions and sizes
    Square::draw_circle(150, 150, 40); // Top-left circle
    Square::draw_cross(250, 200, 60);  // Top-center cross
    Square::draw_circle(650, 150, 50); // Top-right circle
    Square::draw_cross(400, 400, 80);  // Center cross
    Square::draw_circle(200, 600, 50); // Bottom-left circle
    Square::draw_cross(600, 500, 70);  // Bottom-center cross
    Square::draw_circle(700, 700, 40); // Bottom-right circle
    Square::draw_cross(100, 700, 60);  // Bottom-left cross
    Square::draw_circle(300, 100, 30); // Top-left circle
    Square::draw_cross(500, 250, 50);  // Top-center cross
    Square::draw_circle(700, 300, 40); // Top-right circle
    Square::draw_cross(350, 600, 70);  // Bottom-center cross
    Square::draw_circle(100, 500, 30); // Bottom-left circle
    Square::draw_cross(250, 650, 50);  // Bottom-left cross
    Square::draw_circle(600, 600, 40); // Bottom-right circle
    Square::draw_cross(450, 550, 60);  // Center cross

    // Draw the menu
    genv::gout.load_font("LiberationSans-Regular.ttf", 80); // Load the font
    genv::gout << genv::color(128, 0, 128) << genv::move_to(x + 400 - gout.twidth("TIC-TAC-TOE") / 2, y + 40) << genv::text("TIC-TAC-TOE"); // Title
    genv::gout.load_font("LiberationSans-Regular.ttf", 20); // Load the font
    genv::gout << genv::color(255, 255, 255) << genv::move_to(400 - gout.twidth("Select Grid Size:") / 2, y + 150) << genv::text("Select Grid Size:");

    // Draw buttons
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
            // Attempt to delete the score file
            const char* file_path = "result.txt";
            if (std::remove(file_path) != 0) {
                std::cerr << "Error: Unable to delete score file or file does not exist.\n";
            }

            clear_state = true; // Signal to clear the game state
            clear_game_state = false; // Reset the flag
        }
    }
}
