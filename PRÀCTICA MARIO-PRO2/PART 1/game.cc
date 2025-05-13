#include "game.hh"
#include "utils.hh"
using namespace pro2;
using namespace std;


Game::Game(int width, int height)
    : mario_({width / 2, 150}),
      platforms_{
          Platform(100, 300, 200, 211),
          Platform(0, 200, 250, 261),
          Platform(250, 400, 150, 161),
      },
      strawberrys_{
        Strawberry({200, 200}),
        Strawberry({100, 250}),
        Strawberry({325, 150}),
      },
      finished_(false) {
    for (int i = 1; i < 20; i++) {
        platforms_.push_back(Platform(250 + i * 200, 400 + i * 200, 150, 161));
        strawberrys_.push_back(Strawberry({325 + i * 200, 150}));
    }
}

void Game::process_keys(pro2::Window& window) {
    if (window.is_key_down(Keys::Escape)) {
        finished_ = true;
        return;
    }
}

void Game::update_objects(pro2::Window& window) {
    mario_.update(window, platforms_);

    for (Strawberry& s : strawberrys_) {
        s.update(window);

        if (!s.is_collected() && rects_overlap(mario_.get_rect(), s.get_rect())) {
            s.collect();
            ++strawberry_count_;
            cout << "Maduixa recollida! Tens: " << strawberry_count_ << " maduixes!!!" << endl;
        }
    }
}

void Game::update_camera(pro2::Window& window) {
    const Pt pos = mario_.pos();
    const Pt cam = window.camera_center();

    const int left = cam.x - window.width() / 4;
    const int right = cam.x + window.width() / 4;
    const int top = cam.y - window.height() / 4;
    const int bottom = cam.y + window.height() / 4;

    int dx = 0, dy = 0;
    if (pos.x > right) {
        dx = pos.x - right;
    } else if (pos.x < left) {
        dx = pos.x - left;
    }
    if (pos.y < top) {
        dy = pos.y - top;
    } else if (pos.y > bottom) {
        dy = pos.y - bottom;
    }

    window.move_camera({dx, dy});
}

void Game::update(pro2::Window& window) {
    process_keys(window);
    update_objects(window);
    update_camera(window);
}

void Game::paint(pro2::Window& window) {
    window.clear(sky_blue);
    for (const Platform& p : platforms_) {
        p.paint(window);
    }
    for (Strawberry s : strawberrys_) {
        s.paint(window);
    }
    mario_.paint(window);
}