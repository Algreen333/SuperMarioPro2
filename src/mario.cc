#include "mario.hh"
#include "utils.hh"
using namespace std;
using namespace pro2;

/// @cond

const int _ = -1;
const int r = 0xA33E26;
const int s = 0xDBA42F;
const int b = 0xA33E26;
const int y = pro2::yellow;
const int h = 0x6B6E0A;
const int g = 0xDBA42F;
const int w = 0x8d573c;

// clang-format off
const vector<vector<int>> Mario::mario_sprite_normal_ = {
    {_,_,_,r,r,r,r,r,_,_,_,_},
    {_,_,r,r,r,r,r,r,r,r,r,_},
    {_,_,h,h,h,s,s,h,s,_,_,_},
    {_,h,s,h,s,s,s,h,s,s,s,_},
    {_,h,s,h,h,s,s,s,h,s,s,s},
    {_,h,h,s,s,s,s,h,h,h,h,_},
    {_,_,_,s,s,s,s,s,s,s,_,_},
    {_,_,h,h,b,h,h,h,_,_,_,_},
    {_,h,h,h,b,h,h,b,h,h,h,_},
    {h,h,h,h,b,b,b,b,h,h,h,h},
    {g,g,h,b,s,b,b,s,b,h,g,g},
    {g,g,g,b,b,b,b,b,b,g,g,g},
    {g,g,b,b,b,b,b,b,b,b,g,g},
    {_,_,b,b,b,_,_,b,b,b,_,_},
    {_,h,h,h,_,_,_,_,h,h,h,_},
    {h,h,h,h,_,_,_,_,h,h,h,h},
};

const vector<vector<int>> Mario::mario_sprite_tall_ = {
    {_,_,_,_,_,_,r,r,r,r,r,_,_,_,_,_},
    {_,_,_,_,r,r,r,r,r,r,s,_,_,_,_,_},
    {_,_,_,r,r,r,r,r,r,s,s,_,_,_,_,_},
    {_,_,_,r,r,r,r,r,r,r,r,r,r,r,_,_},  
    {_,_,_,h,h,h,s,s,h,s,s,s,_,_,_,_},
    {_,_,h,s,s,h,s,s,h,h,s,s,s,s,_,_},
    {_,_,h,s,s,h,h,s,s,s,s,s,s,s,s,_},
    {_,h,h,s,s,h,h,s,s,s,h,s,s,s,s,_},
    {_,h,h,s,s,s,s,s,h,h,h,h,h,h,_,_},
    {_,h,h,h,s,s,s,s,s,h,h,h,h,h,_,_},
    {_,_,_,h,h,s,s,s,s,s,s,s,s,_,_,_},
    {_,_,_,_,r,s,s,s,s,s,h,_,_,_,_,_},
    {_,_,_,_,h,r,h,h,h,h,r,h,_,_,_,_},
    {_,_,_,h,h,r,h,h,h,h,r,h,h,_,_,_},
    {_,_,h,h,h,r,h,h,h,h,r,h,h,h,_,_},
    {_,h,h,h,h,r,h,h,h,h,r,h,h,h,h,_},
    {_,h,h,h,r,r,h,h,h,h,r,r,h,h,h,_},
    {h,h,h,h,r,r,h,h,h,h,r,r,h,h,h,h},
    {h,h,h,h,r,r,r,r,r,r,r,r,h,h,h,h},
    {h,h,h,h,r,s,r,r,r,r,s,r,h,h,h,h},
    {s,s,s,s,r,r,r,r,r,r,r,r,s,s,s,s},
    {s,s,s,s,r,r,r,r,r,r,r,r,s,s,s,s},
    {_,s,s,s,r,r,r,r,r,r,r,r,s,s,s,_},
    {_,_,r,r,r,r,r,r,r,r,r,r,r,r,_,_},
    {_,r,r,r,r,r,r,_,_,r,r,r,r,r,r,_},
    {_,r,r,r,r,r,_,_,_,_,r,r,r,r,r,_},
    {_,r,r,r,r,r,_,_,_,_,r,r,r,r,r,_},
    {_,_,h,h,h,h,_,_,_,_,h,h,h,h,_,_},
    {_,_,h,h,h,h,_,_,_,_,h,h,h,h,_,_},
    {h,h,h,h,h,h,_,_,_,_,h,h,h,h,h,h},
    {h,h,h,h,h,h,_,_,_,_,h,h,h,h,h,h},
};
// clang-format on
/// @endcond

void Mario::paint(pro2::Window& window) const {
    if (state_ == 0 or ((state_ == 2 or state_ == 3) and anim_frame_counter_%3 == 0)) {
        const Pt top_left = {pos_.x - 6, pos_.y - 15};
        paint_sprite(window, top_left, mario_sprite_normal_, looking_left_);
    }
    else {
        const Pt top_left = {pos_.x - 8, pos_.y - 30};
        paint_sprite(window, top_left, mario_sprite_tall_, looking_left_);
    }
}

pro2::Rect Mario::collision_box() const {
    if (state_ == 0 or state_ == 3) return pro2::Rect{pos_.x - 6, pos_.y - 15, pos_.x + 6, pos_.y};
    else return pro2::Rect{pos_.x - 8, pos_.y - 30, pos_.x + 8, pos_.y};
}

void Mario::jump() {
    if (grounded_) {
        accel_.y = -5;
        grounded_ = false;
        accel_time_ = 3;
    }
}

void Mario::set_state(int new_state) {
    if (state_ != new_state) {
        if (new_state == 1) {
            anim_frame_counter_ = 0;
            state_ = 2;
        }
        else {
            anim_frame_counter_ = 0;
            state_ = 3;
        }
    }
}

void Mario::update(pro2::Window& window, const Finder<Platform>& platforms, Finder<Block>& blocks, list<Interactable>& interactables) {
    // Powerup
    if (state_ == 2) {
        anim_frame_counter_++;
        if (anim_frame_counter_ > 30) {
            state_ = 1;
        }
    }
    // Powerdown (damage)
    else if (state_ == 3) {
        anim_frame_counter_++;
        if (anim_frame_counter_ > 90) {
            state_ = 0;
        }
    }

    last_pos_ = pos_;

    speed_.y += 1; // Gravity
    
    if (window.is_key_down(key_up_)) {
        jump();
    }

    // Velocitat horitzontal
    speed_.x = 0; 
    if (window.is_key_down(key_left_)) {
        speed_.x = -4;
    } else if (window.is_key_down(key_right_)) {
        speed_.x = 4;
    }
    if (speed_.x != 0) {
        looking_left_ = speed_.x < 0;
    }
    
    // If Mario is jumping
    if (accel_time_ > 0) {
        speed_.y += accel_.y;
        accel_time_--;
    }

    // Collision checking with blocks and platforms.
    std::set<Platform *> vert_platforms = platforms.query(collision_box()+={1, speed_.y, -1, speed_.y});
    std::set<Block *> vert_blocks = blocks.query(collision_box()+={1, speed_.y, -1, speed_.y});

    if (vert_platforms.size() + vert_blocks.size() > 0) {
        if (speed_.y > 0) {
            int max_y;
            if (vert_platforms.size() > 0) max_y = (*vert_platforms.begin())->get_rect().top;
            else max_y = (*vert_blocks.begin())->get_rect().top;

            for (const Platform* platform : vert_platforms) {
                max_y = max(max_y, platform->get_rect().top);
            }
            for (const Block* block : vert_blocks) {
                max_y = max(max_y, block->get_rect().top);
            }
            pos_.y = max_y;
            
            set_grounded(true);
        }
        else if (speed_.y < 0) {
            int min_y;
            if (vert_platforms.size() > 0) min_y = (*vert_platforms.begin())->get_rect().bottom;
            else min_y = (*vert_blocks.begin())->get_rect().bottom;

            for (const Platform* platform : vert_platforms) {
                min_y = min(min_y, platform->get_rect().bottom);
            }
            for (Block* block : vert_blocks) {
                min_y = min(min_y, block->get_rect().bottom);
                int result = block->check_bumped(state_);
                if (result == 1) blocks.remove_and_delete(block);
                else if (result == 2) {
                    interactables.emplace_back(block->pos() + Pt{4, 0}, 0);
                    add_coin();
                }
                else if (result == 3) interactables.emplace_back(block->pos() + Pt{0, -17}, 1);
            }
            pos_.y = min_y + ((state_==0 or (state_==2 and anim_frame_counter_%2 == 0))? 15 : 30);
        }
        speed_.y = 0;
    }
    else {
        set_grounded(false);
        pos_.y += speed_.y;
    }

    std::set<Platform *> hor_platforms = platforms.query(collision_box()+={speed_.x, 1, speed_.x, -1});
    std::set<Block *> hor_blocks = blocks.query(collision_box()+={speed_.x, 1, speed_.x, -1});

    if (hor_platforms.size() + hor_blocks.size() > 0) {
        if (speed_.x > 0) {
            int min_x;
            if (hor_platforms.size() > 0) min_x = (*hor_platforms.begin())->get_rect().left;
            else min_x = (*hor_blocks.begin())->get_rect().left;
            
            for (const Platform* platform : hor_platforms) {
                min_x = min(min_x, platform->get_rect().left);
            }
            for (const Block* block : hor_blocks) {
                min_x = min(min_x, block->get_rect().left);
            }
            pos_.x = min_x - ((state_==0 or (state_==2 and anim_frame_counter_%2 == 0))? 6 : 8);            
        }
        else if (speed_.x < 0) {
            int max_x = (*hor_platforms.begin())->get_rect().right;
            if (hor_platforms.size() > 0) max_x = (*hor_platforms.begin())->get_rect().right;
            else max_x = (*hor_blocks.begin())->get_rect().right;

            for (const Platform* platform : hor_platforms) {
                max_x = max(max_x, platform->get_rect().right);
            }
            for (const Block* block : hor_blocks) {
                max_x = max(max_x, block->get_rect().right);
            }
            pos_.x = max_x + ((state_==0 or (state_==2 and anim_frame_counter_%2 == 0))? 6 : 8);
        }
        speed_.x = 0;
    }
    else {
        pos_.x += speed_.x;
    }
}