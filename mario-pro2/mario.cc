#include "mario.hh"
#include "utils.hh"
using namespace std;
using namespace pro2;

const int _ = -1;
const int r = pro2::red;
const int s = 0xecc49b;
const int b = 0x5e6ddc;
const int y = pro2::yellow;
const int h = pro2::black;
const int g = 0xaaaaaa;
const int w = 0x8d573c;


// clang-format off
const vector<vector<int>> Mario::mario_sprite_normal_ = {
    {_, _, _, r, r, r, r, r, _, _, _, _},
    {_, _, r, r, r, r, r, r, r, r, r, _},
    {_, _, h, h, h, s, s, h, s, _, _, _},
    {_, h, s, h, s, s, s, h, s, s, s, _},
    {_, h, s, h, h, s, s, s, h, s, s, s},
    {_, h, h, s, s, s, s, h, h, h, h, _},
    {_, _, _, s, s, s, s, s, s, s, _, _},
    {_, _, r, r, b, r, r, r, _, _, _, _},
    {_, r, r, r, b, r, r, b, r, r, r, _},
    {r, r, r, r, b, b, b, b, r, r, r, r},
    {g, g, r, b, y, b, b, y, b, r, g, g},
    {g, g, g, b, b, b, b, b, b, g, g, g},
    {g, g, b, b, b, b, b, b, b, b, g, g},
    {_, _, b, b, b, _, _, b, b, b, _, _},
    {_, w, w, w, _, _, _, _, w, w, w, _},
    {w, w, w, w, _, _, _, _, w, w, w, w},
};

const double Mario::walk_acc = 1.2;
const double Mario::x_drag_c = 0.2;

// clang-format on

void Mario::paint(pro2::Window& window) const {
    const Pt top_left = {pos_.x - 6, pos_.y - 15};
    paint_sprite(window, top_left, mario_sprite_normal_, looking_left_);
}

pro2::Rect Mario::collision_box() const {
    return pro2::Rect{pos_.x - 6, pos_.y - 15, pos_.x + 6, pos_.y};
}

void Mario::apply_physics_() {
    if (grounded_) {
        speed_.y = 0;
        accel_.y = 0;
    }

    // Always falling to check if we aren't grounded
    // If we are, we will return to the same spot

    DoubPt drag_force = {drag_coef_.x*speed_.x, drag_coef_.y*speed_.y};

    speed_.y += gravity + accel_.y - drag_force.y;
    speed_.x += accel_.x - drag_force.x;

    Pt rounded_speed = round_dpt(speed_);

    pos_.x += rounded_speed.x;
    pos_.y += rounded_speed.y;
}

void Mario::jump() {
    if (grounded_) {
        speed_.y = -17.5;
        grounded_ = false;
    }
}

void Mario::update(pro2::Window& window, const vector<Platform>& platforms) {
    last_pos_ = pos_;
    
    if (window.is_key_down(key_up_)) {
        jump();
    }
        
    // Velocitat horitzontal (prev speed_x = 4)
    if (window.is_key_down(key_left_)) {
        accel_.x = -walk_acc;
    } else if (window.is_key_down(key_right_)) {
        accel_.x = walk_acc;
    }
    else accel_.x = 0;

    if (speed_.x != 0) {
        looking_left_ = speed_.x < 0;
    }

    // Apply acceleration and speed
    apply_physics_();

    // Check position
    set_grounded(false);

    for (const Platform& platform : platforms) {
        if (platform.has_crossed_floor_downwards(last_pos_, pos_)) {
            set_grounded(true);
            set_y(platform.top());
        }
    }
}