#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "widget.hpp"

enum SquareState { EMPTY, CIRCLE, CROSS };

class Square : public Widget {
private:
    SquareState state;
public:
    Square(int x, int y, int size);
    void draw() const override;
    void handle(genv::event ev) override;
    SquareState get_state() const;
};

#endif