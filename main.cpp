#include <iostream>
#include "graphics.hpp"
#include "square.hpp"
#include "widget.hpp"

using namespace std;
using namespace genv;

int main() {
    gout.open(800, 600);
    gout << color(255, 255, 255) << move_to(0, 0) << box(800, 600);

    Square square(200, 200, 100);

    event ev;
    while (gin >> ev) {
        square.handle(ev);
        square.draw();
        gout << refresh;
    }

    return 0;
}
