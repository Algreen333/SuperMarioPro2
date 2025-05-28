#ifndef MARIO_HH
#define MARIO_HH

#include <iostream>
#include <vector>
#include <set>
#include "platform.hh"
#include "window.hh"

class Mario {
 private:
    pro2::Pt pos_, last_pos_;
    pro2::Pt speed_ = {0, 0};
    pro2::Pt accel_ = {0, 0};
    int      accel_time_ = 0;

    int key_up_;
    int key_left_;
    int key_right_;

    bool grounded_ = false;
	bool looking_left_ = false;

	void apply_physics_();

    int coin_count_ = 0;
	
 public:
    Mario(int key_up, int key_left, int key_right, pro2::Pt pos): 
        key_up_(key_up), key_left_(key_left), key_right_(key_right),
        pos_(pos), last_pos_(pos)
        {}

    void paint(pro2::Window& window) const;

    pro2::Rect collision_box() const;

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

    void add_coin(int ammount = 1) {
        coin_count_ += ammount;
    }

    int get_coin_count() {
        return coin_count_; 
    }

    void update(pro2::Window& window, const std::set<const Platform *>& platforms);

 private:
    static const std::vector<std::vector<int>> mario_sprite_normal_;
};

#endif