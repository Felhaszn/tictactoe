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

    Menu menu(0, 0, 800, 800);
    bool start_game = false;
    bool clear_state = false;

    while (!start_game) {
        genv::event ev;
        genv::gin >> ev;
        menu.handle(ev, start_game, clear_state);
        menu.draw();

        if (clear_state) {
            // Reset the game state
            start_game = false;
            clear_state = false;
        }
    }

    const int grid_size = 3;
    const int square_size = 700 / grid_size; // Adjusted to fit within the screen

    genv::gout << genv::color(0, 0, 0) << genv::move_to(0, 0) << genv::box(800, 800); // Clear menu
    std::vector<Square> squares;
    for (int i = 0; i < grid_size; ++i) {
        for (int j = 0; j < grid_size; ++j) {
            squares.emplace_back(i * square_size + 25, j * square_size + 75, square_size);
        }
    }

    GameLogic* game_logic_ptr = nullptr;

    Button restart_button(350, 750, 100, 40, "Restart", [&]() {
        if (game_logic_ptr) {
            game_logic_ptr->set_game_over(false);
        }
    });

    GameLogic game_logic(grid_size, squares, restart_button);
    game_logic_ptr = &game_logic;

    game_logic.event_loop();

    return 0;
}
