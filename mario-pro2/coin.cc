#include "coin.hh"
#include "utils.hh"
using namespace std;
using namespace pro2;

const int _ = -1;
const int y = 0xDB9F40;
const int b = 0x924F1A;
const int d = 0x4C2408;
const int k = 0x000000;


// clang-format off
const vector<vector<vector<int>>> Coin::sprites = {
    {
    { _,  _,  y,  y,  y,  y,  k,  k,  _,  _},
    { _,  y,  y,  y,  y,  y,  y,  k,  k,  _},
    { _,  y,  y,  b,  b,  y,  y,  k,  k,  _},
    { y,  y,  b,  y,  y,  k,  y,  y,  k,  k},
    { y,  y,  b,  y,  y,  k,  y,  y,  k,  k},
    { y,  y,  b,  y,  y,  k,  y,  y,  k,  k},
    { y,  y,  b,  y,  y,  k,  y,  y,  k,  k},
    { y,  y,  b,  y,  y,  k,  y,  y,  k,  k},
    { y,  y,  b,  y,  y,  k,  y,  y,  k,  k},
    { y,  y,  b,  y,  y,  k,  y,  y,  k,  k},
    { y,  y,  b,  y,  y,  k,  y,  y,  k,  k},
    { _,  y,  y,  k,  k,  y,  y,  k,  k,  _},
    { _,  y,  y,  y,  y,  y,  y,  k,  k,  _},
    { _,  _,  y,  y,  y,  y,  k,  k,  _,  _},
    },
    {
    { _,  _,  b,  b,  b,  b,  k,  k,  _,  _},
    { _,  b,  b,  b,  b,  b,  b,  k,  k,  _},
    { _,  b,  b,  b,  b,  b,  b,  k,  k,  _},
    { b,  b,  b,  b,  b,  k,  b,  b,  k,  k},
    { b,  b,  b,  b,  b,  k,  b,  b,  k,  k},
    { b,  b,  b,  b,  b,  k,  b,  b,  k,  k},
    { b,  b,  b,  b,  b,  k,  b,  b,  k,  k},
    { b,  b,  b,  b,  b,  k,  b,  b,  k,  k},
    { b,  b,  b,  b,  b,  k,  b,  b,  k,  k},
    { b,  b,  b,  b,  b,  k,  b,  b,  k,  k},
    { b,  b,  b,  b,  b,  k,  b,  b,  k,  k},
    { _,  b,  b,  k,  k,  b,  b,  k,  k,  _},
    { _,  b,  b,  b,  b,  b,  b,  k,  k,  _},
    { _,  _,  b,  b,  b,  b,  k,  k,  _,  _},
    },
    {
    { _,  _,  d,  d,  d,  d,  k,  k,  _,  _},
    { _,  d,  d,  d,  d,  d,  d,  k,  k,  _},
    { _,  d,  d,  b,  b,  d,  d,  k,  k,  _},
    { d,  d,  b,  d,  d,  k,  d,  d,  k,  k},
    { d,  d,  b,  d,  d,  k,  d,  d,  k,  k},
    { d,  d,  b,  d,  d,  k,  d,  d,  k,  k},
    { d,  d,  b,  d,  d,  k,  d,  d,  k,  k},
    { d,  d,  b,  d,  d,  k,  d,  d,  k,  k},
    { d,  d,  b,  d,  d,  k,  d,  d,  k,  k},
    { d,  d,  b,  d,  d,  k,  d,  d,  k,  k},
    { d,  d,  b,  d,  d,  k,  d,  d,  k,  k},
    { _,  d,  d,  k,  k,  d,  d,  k,  k,  _},
    { _,  d,  d,  d,  d,  d,  d,  k,  k,  _},
    { _,  _,  d,  d,  d,  d,  k,  k,  _,  _},
    }
};
// clang-format on

const int Coin::sz_h = 14;
const int Coin::sz_w = 10;

const vector<int> Coin::animation {
    0,0,0,0,0,0,
    1,1,1,1,1,1,
    2,2,2,2,2,2
};

pro2::Rect Coin::collision_box() const {
    return pro2::Rect{pos_.x - sz_w/2, pos_.y - sz_h, pos_.x + sz_w/2, pos_.y};
}

void Coin::paint(pro2::Window& window) const {
    const Pt top_left = {pos_.x - sz_w/2, pos_.y - sz_h};
    paint_sprite(window, top_left, Coin::get_sprite(), false);
}

void Coin::apply_physics_() {
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

void Coin::update(pro2::Window& window, const vector<Platform>& platforms) {
    last_pos_ = pos_;
    
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
    
    anim_step();
}