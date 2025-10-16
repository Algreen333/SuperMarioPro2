#ifndef COIN_HH
#define COIN_HH

#include <iostream>
#include <set>
#include <vector>
#include "platform.hh"
#include "window.hh"

class Coin {
 private:
    double gravity = 1;
    
    pro2::Pt pos_, last_pos_;   // Left upper corner new position and last position 
    pro2::DoubPt speed_;
    pro2::DoubPt accel_;        // By default: -gravity (floating coin)
    pro2::DoubPt drag_coef_;    // F = -b*v

    bool grounded_ = false;
    
	void apply_physics_();
	
 public:
    
    /**
     * @brief Coins are initilised with an initial position and, optionally, speed, acceleration and drag.
     * Leaing speed, acceleration and drag on default, the coin will be spawned floating and static.
     * 
     * @param pos
     * @param speed
     * @param accel
     * @param drag
     */
    Coin(pro2::Pt pos, pro2::DoubPt speed = {0, 0}, pro2::DoubPt accel = {0, -1}, pro2::DoubPt drag = {0.075, 0.075}) : 
        pos_(pos), last_pos_(pos), speed_(speed), accel_(accel), drag_coef_(drag) {}

    /**
     * @brief Paints the sprite of the coin of the current animation
     * 
     * @param window Window where it will be drawn
     */
    void paint(pro2::Window& window, int anim_frame) const;

    pro2::Pt pos() const {
        return pos_;
    }
    
    inline pro2::Rect get_rect() const {
        return {pos_.x - sz_w/2, pos_.y - sz_h, pos_.x + sz_w/2, pos_.y};
    }

    /**
     * @brief Returns the array of the current sprite
     */
    inline std::vector<std::vector<int>> get_sprite(int anim_frame) const {
        return sprites[animation[anim_frame]];
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

    void update(pro2::Window& window, const std::set<Platform *>& platforms);

    static const std::vector<std::vector<std::vector<int>>> sprites;
 private:
    static const std::vector<int> animation;
    static const int sz_h;
    static const int sz_w;
};

#endif