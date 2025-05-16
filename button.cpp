#include "button.hpp"
#include "graphics.hpp"

using namespace genv;

Button::Button(int x, int y, int width, int height, const std::string& label, std::function<void()> on_click)
    : Widget(x, y, width + 20, height + 10), label(label), on_click(on_click), clicked(false) {}

void Button::draw() const {
    gout.load_font("LiberationSans-Regular.ttf", 20); // Load the font
    gout << move_to(x, y) << color(128, 128, 128) << box(width, height);
    gout << move_to(x + 2, y + 2) << color(200, 200, 200) << box(width - 4, height - 4);

    // Center the text both horizontally and vertically, adjusting the vertical position slightly upward
    int text_width = gout.twidth(label);
    int text_height = gout.cascent() - gout.cdescent();
    gout << color(0, 0, 0)
         << move_to(x + (width - text_width) / 2, y + (height - gout.cascent()) / 2 - gout.cdescent() - 2) // Adjusted upward by 2 pixels
         << text(label);
}

void Button::handle(genv::event ev) {
    if (ev.type == ev_mouse && ev.button == btn_left &&
        ev.pos_x > x && ev.pos_x < x + width &&
        ev.pos_y > y && ev.pos_y < y + height) {
        clicked = true; // Mark the button as clicked
        on_click(); // Trigger the callback function
    } else {
        clicked = false; // Reset the clicked state if the button is not clicked
    }
}
