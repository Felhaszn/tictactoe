#include "button.hpp"
#include "graphics.hpp"

using namespace genv;

Button::Button(int x, int y, int width, int height, const std::string& label, std::function<void()> on_click)
    : Widget(x, y, width, height), label(label), on_click(on_click) {}

void Button::draw() const {
    gout << move_to(x, y) << color(128, 128, 128) << box(width, height);
    gout << move_to(x + 2, y + 2) << color(200, 200, 200) << box(width - 4, height - 4);
    gout << color(0, 0, 0) << move_to(x + width / 2 - gout.twidth(label) / 2, y + height / 2 + gout.cascent() / 2) << text(label);
}

void Button::handle(genv::event ev) {
    if (ev.type == ev_mouse && ev.button == btn_left &&
        ev.pos_x > x && ev.pos_x < x + width &&
        ev.pos_y > y && ev.pos_y < y + height) {
        on_click(); // Trigger the callback function
    }
}
