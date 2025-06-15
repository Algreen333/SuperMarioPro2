#ifndef PICKUP_HH
#define PICKUP_HH

#include <vector>
#include "geometry.hh"
#include "finder.hh"
#include "platform.hh"
#include "block.hh"
#include "utils.hh"
#include "window.hh"

class Pickup {
    private:
        int type_; // 0 per moneda, 1 per bolet, 2 per bandera
        
        pro2::Pt pos_;
        int direction = 1;

        int despawn_timer_;

    public:
        Pickup(pro2::Pt pos, int type) : pos_(pos), type_(type), despawn_timer_((type==0)? 10 : -1) {};

        bool update(pro2::Window& window, const Finder<Platform>& platforms, const Finder<Block>& blocks);

        void paint(pro2::Window& window) const;

        pro2::Rect collision_box() const {
            if (type_ == 0) return {0,0,0,0};
            if (type_ == 1) return {pos_.x, pos_.y, pos_.x + 15, pos_.y + 15};
            else return {pos_.x, pos_.y, pos_.x + 16, pos_.y + 168};
        }

        int type() const {return type_;}

    private:
        static const std::vector<std::vector<std::vector<int>>> sprites;
};

#endif