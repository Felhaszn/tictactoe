#ifndef GAMELOGIC_HPP
#define GAMELOGIC_HPP

#include <vector>
#include <string>
#include "square.hpp"
#include "button.hpp"

class GameLogic {
private:
    int grid_size;
    std::vector<Square>& squares;
    Button& restart_button;
    bool game_over;

    int circle_score;
    int cross_score;
    bool is_circle_turn;

    bool check_winner(SquareState state) const;
    bool is_draw() const;
    void display_result(const std::string& message, SquareState winner) const;
    void draw_game_status() const;

public:
    GameLogic(int grid_size, std::vector<Square>& squares, Button& restart_button);
    void event_loop();
    void set_game_over(bool state);
};

#endif
