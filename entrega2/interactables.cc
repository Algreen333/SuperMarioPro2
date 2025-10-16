#include "interactables.hh"
#include "utils.hh"

/// @cond

const int _ = -1;
const int y = 0xDB9F40;
const int b = 0x924F1A;
const int d = 0x4C2408;
const int k = 0x000000;

const int c = 0xD8A22E;
const int r = 0xA33E26;
const int e = 0xFFFEFF;

const int g = 0x499309;
const int p = 0x98CC17;

const int a = 0x8E500E;
const int w = 0xF5D0C6;

const int coin_speed = -8;
const pro2::Pt speed = {2,4};

const std::vector<std::vector<std::vector<int>>> Interactable::sprites = {
    {
        {_,_,y,y,y,y,k,k,_,_},
        {_,y,y,y,y,y,y,k,k,_},
        {_,y,y,b,b,y,y,k,k,_},
        {y,y,b,y,y,k,y,y,k,k},
        {y,y,b,y,y,k,y,y,k,k},
        {y,y,b,y,y,k,y,y,k,k},
        {y,y,b,y,y,k,y,y,k,k},
        {y,y,b,y,y,k,y,y,k,k},
        {y,y,b,y,y,k,y,y,k,k},
        {y,y,b,y,y,k,y,y,k,k},
        {y,y,b,y,y,k,y,y,k,k},
        {_,y,y,k,k,y,y,k,k,_},
        {_,y,y,y,y,y,y,k,k,_},
        {_,_,y,y,y,y,k,k,_,_},
    },
    {
        {_,_,_,_,_,_,c,c,c,c,_,_,_,_,_,_},
        {_,_,_,_,_,c,c,c,c,r,r,_,_,_,_,_},
        {_,_,_,_,c,c,c,c,r,r,r,r,_,_,_,_},
        {_,_,_,c,c,c,c,c,r,r,r,r,r,_,_,_},
        {_,_,c,c,c,c,c,c,c,r,r,r,c,c,_,_},
        {_,c,c,r,r,r,c,c,c,c,c,c,c,c,c,_},
        {_,c,r,r,r,r,r,c,c,c,c,c,c,c,c,_},
        {c,c,r,r,r,r,r,c,c,c,c,c,r,r,c,c},
        {c,c,r,r,r,r,r,c,c,c,c,c,r,r,r,c},
        {c,c,c,r,r,r,c,c,c,c,c,c,c,r,r,c},
        {c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c},
        {_,c,r,r,r,e,e,e,e,e,e,r,r,r,c,_},
        {_,_,_,_,e,e,e,e,e,e,e,e,_,_,_,_},
        {_,_,_,_,e,e,e,e,e,e,c,e,_,_,_,_},
        {_,_,_,_,_,e,e,e,e,c,e,_,_,_,_,_}
    },
    {
        {_,_,k,k,k,k,_,_},
        {_,k,p,g,g,g,k,_},
        {k,p,g,g,g,g,g,k},
        {k,p,g,g,g,g,g,k},
        {k,g,g,g,g,g,g,k},
        {k,g,g,g,g,g,g,k},
        {_,k,g,g,g,g,k,_},
        {_,_,k,k,k,k,_,_},
    },
    {
        {a,w,w,w,w,w,w,w,w,w,w,w,w,w,w,k},
        {w,a,w,w,w,w,w,w,w,w,w,w,w,w,k,k},
        {w,w,a,w,w,w,w,w,w,w,w,w,w,k,k,k},
        {w,w,w,a,w,w,w,w,w,w,w,w,k,k,k,k},
        {w,w,w,w,a,a,a,a,a,a,a,a,k,k,k,k},
        {w,w,w,w,a,a,a,a,a,a,a,a,k,k,k,k},
        {w,w,w,w,a,a,a,a,a,a,a,a,k,k,k,k},
        {w,w,w,w,a,a,a,a,a,a,a,a,k,k,k,k},
        {w,w,w,w,a,a,a,a,a,a,a,a,k,k,k,k},
        {w,w,w,w,a,a,a,a,a,a,a,a,k,k,k,k},
        {w,w,w,w,a,a,a,a,a,a,a,a,k,k,k,k},
        {w,w,w,w,a,a,a,a,a,a,a,a,k,k,k,k},
        {w,w,w,k,k,k,k,k,k,k,k,k,a,k,k,k},
        {w,w,k,k,k,k,k,k,k,k,k,k,k,a,k,k},
        {w,k,k,k,k,k,k,k,k,k,k,k,k,k,a,k},
        {k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,a},
    },
    {
        {_,_,_,_,_,_,a,a,a,a,_,_,_,_,_,_},
        {_,_,_,_,_,a,a,a,a,a,a,_,_,_,_,_},
        {_,_,_,_,a,a,a,a,a,a,a,a,_,_,_,_},
        {_,_,_,a,a,a,a,a,a,a,a,a,a,_,_,_},
        {_,_,a,k,k,a,a,a,a,a,a,k,k,a,_,_},
        {_,a,a,a,w,k,a,a,a,a,k,w,a,a,a,_},
        {_,a,a,a,w,k,k,k,k,k,k,w,a,a,a,_},
        {a,a,a,a,w,k,w,a,a,w,k,w,a,a,a,a},
        {a,a,a,a,w,w,w,a,a,w,w,w,a,a,a,a},
        {a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a},
        {_,a,a,a,a,w,w,w,w,w,w,a,a,a,a,_},
        {_,_,_,_,w,w,w,w,w,w,w,w,_,_,_,_},
        {_,_,k,k,w,w,w,w,w,w,w,w,k,k,_,_},
        {_,k,k,k,k,k,w,w,w,w,k,k,k,k,k,_},
        {_,k,k,k,k,k,k,w,w,k,k,k,k,k,k,_},
        {_,_,k,k,k,k,k,_,_,k,k,k,k,k,_,_}
    }
};
/// @endcond

bool Interactable::update(pro2::Window& window, const Finder<Platform>& platforms, const Finder<Block>& blocks) {
    if (type_ == 0) {
        pos_ += {0, coin_speed};
        despawn_timer_ --;
        if (despawn_timer_ == 0) return true;
        else return false;
    }
    else if (type_ == 1 or type_ == 3) {
        std::set<Platform *> vert_platforms = platforms.query(collision_box()+={2, speed.y, -1, speed.y});
        std::set<Block *> vert_blocks = blocks.query(collision_box()+={2, speed.y, -1, speed.y});
        
        if (vert_platforms.size() + vert_blocks.size() > 0) {
            int max_y;
            if (vert_platforms.size() > 0) max_y = (*vert_platforms.begin())->get_rect().top;
            else max_y = (*vert_blocks.begin())->get_rect().top;
            
            for (const Platform* platform : vert_platforms) {
                max_y = std::max(max_y, platform->get_rect().top);
            }
            for (const Block* block : vert_blocks) {
                max_y = std::max(max_y, block->get_rect().top);
            }
            pos_.y = max_y - 14;
        }
        else pos_.y += speed.y;

        std::set<Platform *> hor_platforms = platforms.query(collision_box()+={speed.x, 2, speed.x, -2});
        std::set<Block *> hor_blocks = blocks.query(collision_box()+={speed.x, 2, speed.x, -2});

        if (hor_platforms.size() + hor_blocks.size() > 0) {
            if (direction > 0) {
                int min_x;
                if (hor_platforms.size() > 0) min_x = (*hor_platforms.begin())->get_rect().left;
                else min_x = (*hor_blocks.begin())->get_rect().left;
                
                for (const Platform* platform : hor_platforms) {
                    min_x = std::min(min_x, platform->get_rect().left);
                }
                for (const Block* block : hor_blocks) {
                    min_x = std::min(min_x, block->get_rect().left);
                }
                pos_.x = min_x - 20;
                direction *= -1;
            }
            else {
                int max_x = (*hor_platforms.begin())->get_rect().right;
                if (hor_platforms.size() > 0) max_x = (*hor_platforms.begin())->get_rect().right;
                else max_x = (*hor_blocks.begin())->get_rect().right;

                for (const Platform* platform : hor_platforms) {
                    max_x = std::max(max_x, platform->get_rect().right);
                }
                for (const Block* block : hor_blocks) {
                    max_x = std::max(max_x, block->get_rect().right);
                }
                pos_.x = max_x;
                direction *= -1;
            }
        }
        else pos_.x += speed.x*direction;
        return false;
    }
    else return false;
}

void Interactable::paint(pro2::Window& window) const {
    if (type_ == 0) paint_sprite(window, pos_, sprites[0], false);
    else if (type_ == 1) paint_sprite(window, pos_, sprites[1], false);
    else if (type_ == 2) {
        paint_sprite(window, pos_ + pro2::Pt {4, 0}, sprites[2], false);
        paint_rect_fill(window, {pos_.x + 7, pos_.y + 8, pos_.x + 8, pos_.y + 152}, p);
        paint_sprite(window, pos_ + pro2::Pt {0, 152}, sprites[3], false);
    }
    else paint_sprite(window, pos_, sprites[4], false);
}
