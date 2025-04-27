#ifndef MARIO_HH
#define MARIO_HH

#include <iostream>
#include <vector>
#include "platform.hh"
#include "window.hh"

class Mario {
 private:
    double gravity = 1;

    pro2::Pt pos_, last_pos_;
    pro2::DoubPt speed_;
    pro2::DoubPt accel_;
    pro2::DoubPt drag_coef_;

    bool grounded_ = false;
	bool looking_left_ = false;

    int key_up_;
    int key_left_;
    int key_right_;

    int coin_count_ = 0;

	void apply_physics_();
	
 public:
    Mario(
        int key_up, int key_left, int key_right, 
        pro2::Pt pos, 
        pro2::DoubPt speed = {0,0}, 
        pro2::DoubPt accel = {0, -1}, 
        pro2::DoubPt drag_coef = {x_drag_c, 0.065}
    ):
        key_up_(key_up), key_left_(key_left), key_right_(key_right),
        pos_(pos), last_pos_(pos), speed_(speed), accel_(accel), drag_coef_(drag_coef) 
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

    void update(pro2::Window& window, const std::vector<Platform>& platforms);

 private:
    static const std::vector<std::vector<int>> mario_sprite_normal_;
    static const double walk_acc;
    static const double x_drag_c;
};

#endif