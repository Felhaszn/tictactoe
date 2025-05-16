#include "gamelogic.hpp"
#include "graphics.hpp"

using namespace genv;

GameLogic::GameLogic(int grid_size, std::vector<Square>& squares, Button& restart_button)
    : grid_size(grid_size), squares(squares), restart_button(restart_button), game_over(false) {}

void GameLogic::set_game_over(bool state) {
    game_over = state;
    if (!state) {
        // Clear the screen and redraw the grid
        gout << color(0, 0, 0) << move_to(0, 0) << box(800, 800);
        for (auto& square : squares) {
            square = Square(square.get_x(), square.get_y(), square.get_width()); // Reset each square
            square.draw();
        }
        gout << refresh;
    }
}

bool GameLogic::check_winner(SquareState state) const {
    // Check rows, columns, and diagonals for 5 consecutive states
    for (int i = 0; i < grid_size; ++i) {
        for (int j = 0; j <= grid_size - 5; ++j) {
            // Check row
            bool row_win = true;
            for (int k = 0; k < 5; ++k) {
                if (squares[i * grid_size + j + k].get_state() != state) {
                    row_win = false;
                    break;
                }
            }
            if (row_win) return true;

            // Check column
            bool col_win = true;
            for (int k = 0; k < 5; ++k) {
                if (squares[(j + k) * grid_size + i].get_state() != state) {
                    col_win = false;
                    break;
                }
            }
            if (col_win) return true;
        }
    }

    // Check diagonals
    for (int i = 0; i <= grid_size - 5; ++i) {
        for (int j = 0; j <= grid_size - 5; ++j) {
            // Check main diagonal
            bool diag1_win = true;
            for (int k = 0; k < 5; ++k) {
                if (squares[(i + k) * grid_size + j + k].get_state() != state) {
                    diag1_win = false;
                    break;
                }
            }
            if (diag1_win) return true;

            // Check anti-diagonal
            bool diag2_win = true;
            for (int k = 0; k < 5; ++k) {
                if (squares[(i + k) * grid_size + j + 4 - k].get_state() != state) {
                    diag2_win = false;
                    break;
                }
            }
            if (diag2_win) return true;
        }
    }

    return false;
}

bool GameLogic::is_draw() const {
    for (const auto& square : squares) {
        if (square.get_state() == EMPTY) {
            return false;
        }
    }
    return true;
}

void GameLogic::display_result(const std::string& message, SquareState winner) const {
    gout << color(0, 0, 0) << move_to(0, 0) << box(800, 800);
    gout << color(255, 255, 255) << move_to(300, 300) << text(message);

    if (winner == CIRCLE) {
        Square::draw_circle(400, 400, 50);
    } else if (winner == CROSS) {
        Square::draw_cross(350, 375, 100);
    } else if (winner == EMPTY) {
        Square::draw_circle(350, 400, 50);
        Square::draw_cross(450, 375, 100);
    }

    // Enable the restart button
    restart_button.draw();
    gout << refresh;
}

void GameLogic::event_loop() {
    event ev;

    while (gin >> ev) {
        if (game_over) {
            restart_button.handle(ev);
        } else {
            for (auto& square : squares) {
                square.handle(ev);
            }

            // Check for a winner or draw
            if (check_winner(CIRCLE)) {
                display_result("The winner is:", CIRCLE);
                set_game_over(true);
            } else if (check_winner(CROSS)) {
                display_result("The winner is:", CROSS);
                set_game_over(true);
            } else if (is_draw()) {
                display_result("Draw", EMPTY);
                set_game_over(true);
            }

            if (!game_over) {
                // Redraw the grid
                gout << color(0, 0, 0) << move_to(0, 0) << box(800, 800);
                for (auto& square : squares) {
                    square.draw();
                }
            }
        }

        // Always draw the restart button
        if (game_over) {
            restart_button.draw();
        }
        gout << refresh;
    }
}
