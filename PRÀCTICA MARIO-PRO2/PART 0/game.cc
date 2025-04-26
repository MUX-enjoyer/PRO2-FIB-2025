#include "game.hh"

using namespace pro2;

Game::Game(int width, int height)
    : mario_({width / 2, 150}, 0),
      mario2_({width / 2 - 30, 150}, 1),
      platforms_{
          Platform(100, 300, 200, 211),
          Platform(0, 200, 250, 261),
          Platform(250, 400, 150, 161),
      },
    finished_(false) {
    for (int i = 1; i < 20; i++) {
        platforms_.push_back(Platform(250 + i * 200, 400 + i * 200, 150, 161));
    }
}

void Game::process_keys(pro2::Window& window) {
    if (window.is_key_down(Keys::Escape)) {
        finished_ = true;
        return;
    }

    // Miro només si l'he apretat, no que estigui apretada!
    if (window.was_key_pressed('P')) {
        paused_ = !paused_;
        return;
    }
}

void Game::update_objects(pro2::Window& window) {
    mario_.update(window, platforms_);
    mario2_.update(window, platforms_);
}

void Game::update_camera(pro2::Window& window) {
    const Pt pos = mario_.pos();
    const Pt cam = window.camera_center();

    const int left = cam.x - window.width() / 4;
    const int right = cam.x + window.width() / 4;
    const int top = cam.y - window.height() / 4;
    const int bottom = cam.y + window.height() / 4;

    int dx = 0, dy = 0;

    // if (pos.x > right) {
    //     dx = pos.x - right;
    // } else if (pos.x < left) {
    //     dx = pos.x - left;
    // }
    // if (pos.y < top) {
    //     dy = pos.y - top;
    // } else if (pos.y > bottom) {
    //     dy = pos.y - bottom;
    // }

    dx = pos.x-cam.x;
    dy = pos.y-cam.y;

    window.move_camera({dx, dy});
}

void Game::update(pro2::Window& window) {
    process_keys(window);

    if (paused_) return;

    update_objects(window);
    update_camera(window);
}

void Game::paint(pro2::Window& window) {
    window.clear(sky_blue);
    for (const Platform& p : platforms_) {
        p.paint(window);
    }
    mario_.paint(window);
    mario2_.paint(window);

    Rect cam = window.camera_rect();
    Color vermell = 0x00ff0000;
    paint_hline(window, cam.left, cam.right, cam.top, vermell);
    paint_hline(window, cam.left, cam.right, cam.bottom-1, vermell);
    paint_vline(window, cam.left, cam.top, cam.bottom, vermell);
    paint_vline(window, cam.right-1, cam.top, cam.bottom, vermell);

    if (window.frame_count()%75<25) {
        Pt centre = window.camera_center();
        Rect rectanglePetit = {centre.x-10, centre.y+10, centre.x+10, centre.y-10};
        Color groc = 0x00ffff00;
        paint_rect(window, rectanglePetit, groc);    
    }
}