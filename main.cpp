#include <iostream>
#include <vector>
#include "graphics.hpp"
#include "square.hpp"
#include "widget.hpp"
#include "gamelogic.hpp"
#include "button.hpp"

using namespace std;
using namespace genv;

int main() {
    const int grid_size = 20;
    const int square_size = 750 / grid_size; // Adjust grid size to fit below the status area

    gout.open(800, 800);
    gout << color(0, 0, 0) << move_to(0, 0) << box(800, 800);

    vector<Square> squares;
    for (int i = 0; i < grid_size; ++i) {
        for (int j = 0; j < grid_size; ++j) {
            squares.emplace_back(i * square_size + 25, j * square_size + 75, square_size);
        }
    }

    GameLogic* game_logic_ptr = nullptr; // Declare a pointer to GameLogic

    Button restart_button(350, 750, 100, 40, "Restart", [&]() {
        if (game_logic_ptr) {
            game_logic_ptr->set_game_over(false); // Reset the game state
        }
    });

    GameLogic game_logic(grid_size, squares, restart_button);
    game_logic_ptr = &game_logic; // Assign the pointer to the GameLogic instance

    game_logic.event_loop();

    return 0;
}
