#include "geometry.hh"

namespace pro2 {

std::pair<bool, int> resolve_collision_vertical(const Rect& prev, Rect curr, const Rect& block) {
    if (!check_collision(curr, block)) return {false, 0};

    if (prev.bottom < curr.bottom and curr.bottom >= block.top and curr.top <= block.bottom and curr.bottom <= block.bottom) {
        return {true, 1};
    }
    else if (prev.bottom > curr.bottom and curr.top <= block.bottom and curr.bottom >= block.top) {
        return {true, -1};
    }
    else return {false, 0};
}

std::pair<bool, int> resolve_collision_horizontal(const Rect& prev, Rect curr, const Rect& block) {
    if (!check_collision(curr, block)) return {false, 0};
    
    if (prev.left < curr.left and curr.right >= block.left and curr.left <= block.right) {
        return {true, 1};
    }
    else if (prev.left > curr.left and curr.left <= block.right and curr.right >= block.left) {
        return {true, -1};
    }
    else return {false, 0};
}

}