#include <vector>
#include "game.hh"
#include "window.hh"

using namespace std;

const int WIDTH = 480, HEIGHT = 320;
const int ZOOM = 2;
const int FPS = 48;

int main() {
    pro2::Window window("Mario Pro 2", WIDTH, HEIGHT, ZOOM);
    window.set_fps(FPS);

    Game game(WIDTH, HEIGHT);

    while (window.next_frame() && !game.is_finished()) {
        game.update(window);
        game.paint(window);
    }
}