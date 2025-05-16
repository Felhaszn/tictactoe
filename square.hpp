#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "widget.hpp"

enum SquareState { EMPTY, CIRCLE, CROSS };

class Square : public Widget {
private:
    SquareState state;
    static bool is_circle_turn; // Tracks turn alternation
public:
    Square(int x, int y, int size);
    void draw() const override;
    void handle(genv::event ev) override;
    SquareState get_state() const;

    static void draw_circle(int x, int y, int radius);
    static void draw_cross(int x, int y, int size);
};

#endif