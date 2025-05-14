#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "graphics.hpp"

class Widget {
protected:
    int x, y, width, height;
public:
    Widget(int x, int y, int width, int height);
    virtual void draw() const = 0;
    virtual void handle(genv::event ev) = 0;
    virtual ~Widget() {}
};

#endif