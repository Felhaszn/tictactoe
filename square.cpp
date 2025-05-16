#include "square.hpp"

bool Square::is_circle_turn = true;

Square::Square(int x, int y, int size)
    : Widget(x, y, size, size), state(EMPTY) {}

void Square::draw() const {
    using namespace genv;
    gout << move_to(x, y) << color(128, 0, 128) << box(width, height);
    gout << move_to(x + 2, y + 2) << color(0, 0, 0) << box(width - 4, height - 4);

    if (state == CIRCLE) {
        draw_circle(x + width / 2, y + height / 2, width / 2 - 5);
    } else if (state == CROSS) {
        draw_cross(x, y, width);
    }
}

void Square::handle(genv::event ev) {
    if (ev.type == genv::ev_mouse && ev.button == genv::btn_left &&
        ev.pos_x > x && ev.pos_x < x + width &&
        ev.pos_y > y && ev.pos_y < y + height) {
        if (state == EMPTY) {
            state = is_circle_turn ? CIRCLE : CROSS;
            is_circle_turn = !is_circle_turn;
        }
    }
}

SquareState Square::get_state() const {
    return state;
}

void Square::draw_circle(int cx, int cy, int radius) {
    using namespace genv;
    for (int y = -radius; y <= radius; ++y) {
        for (int x = -radius; x <= radius; ++x) {
            int dist_squared = x * x + y * y;
            if (dist_squared <= radius * radius && dist_squared > (radius - 1) * (radius - 1)) {
                gout << move_to(cx + x, cy + y) << color(0, 0, 255) << dot;
            }
        }
    }
}

void Square::draw_cross(int x, int y, int size) {
    using namespace genv;
    gout << color(128, 0, 128)
         << move_to(x + 5, y + 5) << line(size - 10, size - 10)
         << move_to(x + 5, y + size - 5) << line(size - 10, -size + 10);
}