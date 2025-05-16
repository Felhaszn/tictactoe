#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "widget.hpp"
#include <functional>
#include <string>

class Button : public Widget {
private:
    std::string label;
    std::function<void()> on_click; // Callback function for button click
    bool clicked; // Tracks whether the button was clicked
public:
    Button(int x, int y, int width, int height, const std::string& label, std::function<void()> on_click);
    void draw() const override;
    void handle(genv::event ev) override;
    bool is_clicked() const { return clicked; } // Returns whether the button was clicked
};

#endif
