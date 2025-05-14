#include "square.hpp"

Square::Square(int x, int y, int size)
    : Widget(x, y, size, size), state(EMPTY) {}

void Square::draw() const {
    using namespace genv;
    gout << move_to(x, y) << color(200, 200, 200) << box(width, height);
    gout << move_to(x + 2, y + 2) << color(255, 255, 255) << box(width - 4, height - 4);

    if (state == CIRCLE) {
        gout << color(0, 0, 255) 
             << move_to(x + width / 2, y + height / 2)
             << box(width / 4, height / 4);
    } else if (state == CROSS) {
        gout << color(255, 0, 0)
             << move_to(x + 5, y + 5) << line(width - 10, height - 10)
             << move_to(x + 5, y + height - 5) << line(width - 10, -height + 10);
    }
}

void Square::handle(genv::event ev) {
    if (ev.type == genv::ev_mouse && ev.button == genv::btn_left &&
        ev.pos_x > x && ev.pos_x < x + width &&
        ev.pos_y > y && ev.pos_y < y + height) {
        if (state == EMPTY) {
            state = CIRCLE; // Change to CROSS if needed
        }
    }
}

SquareState Square::get_state() const {
    return state;
}