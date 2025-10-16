#ifndef INTERACTABLES_HH
#define INTERACTABLES_HH

#include <vector>
#include "geometry.hh"
#include "finder.hh"
#include "platform.hh"
#include "block.hh"
#include "utils.hh"
#include "window.hh"

/**
 * @class Interactable
 * 
 * @brief The classs `Interactable` is used for every type of object which interacti with Mario.
 * 
 * There are 4 types:
 * - 0: Coin which is created by a block when mario jumps into it from below.
 *      It acts as an animation, floating upwards and disappearing automatically.
 *      The coin is added to the coin counter.
 * 
 * - 1: Mushroom which makes Mario change into its 'big' state.
 *      Once it is spawned, it moves horizontally and it is also affected by gravity and block collisitions.
 *      It disappears once Mario touches it.
 * 
 * - 2: The level end flag.
 *      It triggers the game win condition once Mario touches it.
 *
 * - 3: An enemy 'goomba'.
 *      If Mario jumps on top of it, it is despawned and a coin is spawned.
 *      If the goomba touches Mario in any other way, it damages Mario.
 */
class Interactable {
    private:
        int type_;
        
        pro2::Pt pos_;
        int direction = 1;

        int despawn_timer_;

    public:
        Interactable(pro2::Pt pos, int type) : pos_(pos), type_(type), despawn_timer_((type==0)? 10 : -1) {};

        bool update(pro2::Window& window, const Finder<Platform>& platforms, const Finder<Block>& blocks);

        void paint(pro2::Window& window) const;

        pro2::Rect collision_box() const {
            if (type_ == 0) return {0,0,0,0};
            else if (type_ == 1 or type_ == 3) return {pos_.x, pos_.y, pos_.x + 15, pos_.y + 15};
            else return {pos_.x+7, pos_.y, pos_.x + 8, pos_.y + 168};
        }

        int type() const {return type_;}

        pro2::Pt pos() const {return pos_;}

    private:
        static const std::vector<std::vector<std::vector<int>>> sprites;
};

#endif