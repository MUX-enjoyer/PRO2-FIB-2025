// <HUGE-WARNING>: This #include has to be first, don't move it!
#include "fenster.h"
// </HUGE-WARNING>

#include "window.hh"
using std::string;

namespace pro2 {

Window::Window(string title, int width, int height, int zoom)
    : fenster_{.title = title.c_str(), .width = width * zoom, .height = height * zoom},
      zoom_(zoom),
      pixels_size_(width * height * zoom * zoom)  //
{
    pixels_ = new uint32_t[width * height * zoom * zoom];
    fenster_.buf = pixels_;
    fenster_open(&fenster_);
    last_time_ = fenster_time();
}

void Window::update_camera_() {
    if (topleft_.x < topleft_target_.x) {
        topleft_.x += std::min(camera_speed_, topleft_target_.x - topleft_.x);
    } else if (topleft_.x > topleft_target_.x) {
        topleft_.x -= std::min(camera_speed_, topleft_.x - topleft_target_.x);
    }

    if (topleft_.y < topleft_target_.y) {
        topleft_.y += std::min(camera_speed_, topleft_target_.y - topleft_.y);
    } else if (topleft_.y > topleft_target_.y) {
        topleft_.y -= std::min(camera_speed_, topleft_.y - topleft_target_.y);
    }
}

bool Window::next_frame() {
    update_camera_();
    int wait = int(1000.0 / fps_) - (fenster_time() - last_time_);
    if (wait > 0) {
        fenster_sleep(wait);
    }
    last_time_ = fenster_time();
    frame_count_++;

    // Copy the keys array
    for (size_t i = 0; i < 256; i++) {
        last_keys_[i] = fenster_.keys[i];
    }
    last_mouse_ = fenster_.mouse;

    return fenster_loop(&fenster_) == 0;
}

void Window::clear(Color color) {
    for (size_t i = 0; i < pixels_size_; i++) {
        pixels_[i] = color;
    }
}

Pt Window::mouse_pos() const {
    const int width = fenster_.width / zoom_;
    const int height = fenster_.height / zoom_;

    int x = fenster_.x / zoom_;
    int y = fenster_.y / zoom_;
    if (x >= width) {
        x = width - 1;
    } else if (x < 0) {
        x = 0;
    }
    if (y >= height) {
        y = height - 1;
    } else if (y < 0) {
        y = 0;
    }

    return Pt{x + topleft_.x, y + topleft_.y};
}

void Window::set_pixel(Pt pt, Color color) {
    const Pt camera_pt = {pt.x - topleft_.x, pt.y - topleft_.y};
    for (int i = 0; i < zoom_; i++) {
        for (int j = 0; j < zoom_; j++) {
            const int _i = camera_pt.x * zoom_ + i;
            const int _j = camera_pt.y * zoom_ + j;
            if (_i >= 0 && _i < fenster_.width && _j >= 0 && _j < fenster_.height) {
                fenster_pixel(&fenster_, _i, _j) = color;
            }
        }
    }
}

}  // namespace pro2