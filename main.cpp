#include <iostream>
#include <vector>
#include "graphics.hpp"
#include "square.hpp"
#include "widget.hpp"
#include "gamelogic.hpp"
#include "button.hpp"
#include "menu.hpp"

int main() {
    genv::gout.open(800, 800);

    while (true) {
        Menu menu(0, 0, 800, 800);
        bool start_game = false;
        bool clear_state = false;
        int grid_size = 0;

        // Menu loop
        while (!start_game) {
            genv::event ev;
            if (!(genv::gin >> ev)) {
                return 0; // Exit gracefully if the event stream is closed
            }

            if (ev.type == genv::ev_key && ev.keycode == genv::key_escape) {
                return 0; // Exit gracefully on Escape key
            }

            menu.handle(ev, start_game, clear_state, grid_size);
            menu.draw();

            if (clear_state) {
                // Reset the game state
                start_game = false;
                clear_state = false;
            }
        }

        const int square_size = 700 / grid_size; // Adjusted to fit within the screen
        const int grid_width = grid_size * square_size;
        const int x_offset = (800 - grid_width) / 2; // Calculate horizontal offset to center the grid

        genv::gout << genv::color(0, 0, 0) << genv::move_to(0, 0) << genv::box(800, 800); // Clear menu
        std::vector<Square> squares;
        for (int i = 0; i < grid_size; ++i) {
            for (int j = 0; j < grid_size; ++j) {
                squares.emplace_back(i * square_size + x_offset, j * square_size + 75, square_size);
            }
        }

        bool return_to_menu = false;

        GameLogic* game_logic_ptr = nullptr;

        Button restart_button(350, 750, 100, 40, "Restart", [&squares, &game_logic_ptr]() {
            for (auto& square : squares) {
                square.reset(); // Reset each square to its initial state
            }
            if (game_logic_ptr) {
                game_logic_ptr->set_game_over(false); // Ensure the game state is reset
            }
        });

        Button back_to_menu_button(650, 750, 100, 40, "Menu", [&return_to_menu]() {
            return_to_menu = true; // Set the flag to return to the menu
        });

        GameLogic game_logic(grid_size, squares, restart_button, back_to_menu_button);
        game_logic_ptr = &game_logic;

        game_logic.event_loop(return_to_menu);

        if (return_to_menu) {
            // Reset the game state and re-enter the menu loop
            squares.clear();
            start_game = false;
            continue; // Re-enter the menu loop
        }
    }

    return 0;
}
