#include <iostream>
#include <vector>
#include "graphics.hpp"
#include "square.hpp"
#include "widget.hpp"

using namespace std;
using namespace genv;

void handle_event(event ev, vector<Square>& squares) {
    for (auto& square : squares) {
        square.handle(ev);
    }
}

int main() {
    const int grid_size = 20;
    const int square_size = 800 / grid_size;

    gout.open(800, 800);
    gout << color(0, 0, 0) << move_to(0, 0) << box(800, 800);

    vector<Square> squares;
    for (int i = 0; i < grid_size; ++i) {
        for (int j = 0; j < grid_size; ++j) {
            squares.emplace_back(i * square_size, j * square_size, square_size);
        }
    }

    event ev;
    while (gin >> ev) {
        handle_event(ev, squares);
        for (auto& square : squares) {
            square.draw();
        }
        gout << refresh;
    }

    return 0;
}
