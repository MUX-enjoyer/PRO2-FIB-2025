#ifndef MARIO_HH
#define MARIO_HH

#include <iostream>
#include <vector>
#include "platform.hh"
#include "window.hh"

class Mario {
 private:
    pro2::Pt pos_, last_pos_;
    pro2::Pt speed_ = {0, 0};
    pro2::Pt accel_ = {0, 0};
    int      accel_time_ = 0;

    bool grounded_ = false;
	bool looking_left_ = false;

	void apply_physics_();

    pro2::Keys jump_key_, left_key_, right_key_;
	
 public:
    Mario(pro2::Pt pos, int id) : pos_(pos), last_pos_(pos) {
        if (id == 0) {
            jump_key_ = pro2::Keys::Up;
            left_key_ = pro2::Keys::Left;
            right_key_ = pro2::Keys::Right;
        }
        else {
            jump_key_ = pro2::Keys::W;
            left_key_ = pro2::Keys::A;
            right_key_ = pro2::Keys::D;
        }
    }

    void paint(pro2::Window& window) const;

    pro2::Pt pos() const {
        return pos_;
    }

    void set_y(int y) {
        pos_.y = y;
    }

    bool is_grounded() const {
        return grounded_;
    }

    void set_grounded(bool grounded) {
        grounded_ = grounded;
        if (grounded_) {
            speed_.y = 0;
        }
    }

    void toggle_grounded() {
        set_grounded(!grounded_);
    }

    void jump();

    void update(pro2::Window& window, const std::vector<Platform>& platforms);

 private:
    static const std::vector<std::vector<int>> mario_sprite_normal_;
};

#endif