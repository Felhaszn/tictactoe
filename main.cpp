#include <iostream>
#include "graphics.hpp"

using namespace std;
using namespace genv;

int main(){
    gout.open(800, 600);
    gout << color(255, 255, 255) << move_to(0, 0) << box(800, 600);
    gout << color(0, 0, 0) << move_to(100, 100) << box(700, 500);
    gout << color(255, 255, 255) << move_to(150, 150) << text("Hello, World!") << refresh;

    event ev;
    while(gin >> ev){

    }

    return 0;
}
