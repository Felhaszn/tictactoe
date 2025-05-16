#include "gamelogic.hpp"
#include "graphics.hpp"
#include <fstream> // Include for file output
#include <iostream> // Include for std::cerr

using namespace genv;

GameLogic::GameLogic(int grid_size, std::vector<Square>& squares, Button& restart_button, Button& back_to_menu_button)
    : grid_size(grid_size), squares(squares), restart_button(restart_button), back_to_menu_button(back_to_menu_button),
      game_over(false), circle_score(0), cross_score(0), is_circle_turn(true) {}

void GameLogic::set_game_over(bool state) {
    game_over = state;
    if (!state) {
        // Clear the screen and redraw the grid
        genv::gout << genv::color(0, 0, 0) << genv::move_to(0, 0) << genv::box(800, 800);
        for (auto& square : squares) {
            square.reset(); // Reset each square to its initial state
            square.draw();
        }
        genv::gout << genv::refresh;
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
    genv::gout.load_font("LiberationSans-Regular.ttf", 20); // Load the font
    genv::gout << genv::color(0, 0, 0) << genv::move_to(0, 0) << genv::box(800, 800);
    genv::gout << genv::color(255, 255, 255) << genv::move_to(400 - gout.twidth(message)/2, 300) << genv::text(message);

    if (winner == CIRCLE) {
        Square::draw_circle(400, 400, 50);
    } else if (winner == CROSS) {
        Square::draw_cross(350, 375, 100);
    } else if (winner == EMPTY) {
        Square::draw_circle(350, 400, 50);
        Square::draw_cross(450, 375, 100);
    }

    // Read previous scores from the file
    int previous_circle_score = 0;
    int previous_cross_score = 0;
    std::ifstream result_file_in("/home/felhaszn/Documents/Órák/Prog2/tictactoe/result.txt");
    if (result_file_in.is_open()) {
        result_file_in >> previous_circle_score >> previous_cross_score;
        result_file_in.close();
    }

    // Update the scores
    int updated_circle_score = previous_circle_score + (winner == CIRCLE ? 1 : 0);
    int updated_cross_score = previous_cross_score + (winner == CROSS ? 1 : 0);

    // Write the updated scores back to the file
    std::ofstream result_file_out("/home/felhaszn/Documents/Órák/Prog2/tictactoe/result.txt");
    if (result_file_out.is_open()) {
        result_file_out << updated_circle_score << " " << updated_cross_score << "\n";
        result_file_out.close();
    } else {
        std::cerr << "Error: Unable to open result file for writing.\n";
    }

    // Enable the restart button
    restart_button.draw();
    genv::gout << genv::refresh;
}

void GameLogic::draw_game_status() const {
    genv::gout.load_font("LiberationSans-Regular.ttf", 20); // Load the font
    genv::gout << genv::color(0, 0, 0) << genv::move_to(0, 0) << genv::box(800, 50); // Clear the status area
    genv::gout << genv::color(255, 255, 255);

    // Read the saved scores from the file
    int saved_circle_score = 0;
    int saved_cross_score = 0;
    std::ifstream result_file_in("result.txt");
    if (result_file_in.is_open()) {
        result_file_in >> saved_circle_score >> saved_cross_score;
        result_file_in.close();
    }

    genv::gout.load_font("LiberationSans-Regular.ttf", 40); // Load the font
    // Draw the circle score on the left
    Square::draw_circle(30, 40, 20);
    genv::gout << genv::move_to(90, 15) << genv::text(std::to_string(saved_circle_score));

    // Draw the cross score on the right
    Square::draw_cross(750, 20, 40);
    genv::gout << genv::move_to(700, 15) << genv::text(std::to_string(saved_cross_score));

    // Center the current turn indicator
    std::string turn_text = is_circle_turn ? "Circle's Turn" : "Cross's Turn";
    int text_width = genv::gout.twidth(turn_text);
    genv::gout << genv::move_to((800 - text_width) / 2, 15) << genv::text(turn_text);
}

void GameLogic::event_loop(bool& return_to_menu) {
    genv::event ev;

    while (genv::gin >> ev) {
        if (game_over) {
            restart_button.handle(ev);
            back_to_menu_button.handle(ev);
        } else {
            for (auto& square : squares) {
                square.handle(ev);
            }

            // Check for a winner or draw
            if (check_winner(CIRCLE)) {
                circle_score++;
                display_result("The winner is:", CIRCLE);
                set_game_over(true);
            } else if (check_winner(CROSS)) {
                cross_score++;
                display_result("The winner is:", CROSS);
                set_game_over(true);
            } else if (is_draw()) {
                display_result("Draw", EMPTY);
                set_game_over(true);
            }

            if (!game_over) {
                // Redraw the grid
                genv::gout << genv::color(0, 0, 0) << genv::move_to(0, 50) << genv::box(800, 750); // Clear grid area
                for (auto& square : squares) {
                    square.draw();
                }
            }
        }

        // Always draw the game status and buttons
        draw_game_status();
        if (game_over) {
            restart_button.draw();
            back_to_menu_button.draw();
        }
        genv::gout << genv::refresh;

        // Handle back to menu button
        if (back_to_menu_button.is_clicked()) {
            return_to_menu = true;
            break;
        }
    }
}
