#include "platform.hh"
using namespace std;

using pro2::Color;

/// @cond

const int b = 0x8E500E;
const int w = 0xF7D0C7;
const int _ = 0;

// clang-format off
const vector<vector<int>> Platform::platform_texture_ = {

    {b,w,w,w,w,w,w,w,w,_,b,w,w,w,w,b},
    {w,b,b,b,b,b,b,b,b,_,w,b,b,b,b,_},
    {w,b,b,b,b,b,b,b,b,_,w,b,b,b,b,_},
    {w,b,b,b,b,b,b,b,b,_,w,b,b,b,b,_},
    {w,b,b,b,b,b,b,b,b,_,w,_,b,b,b,_},
    {w,b,b,b,b,b,b,b,b,_,b,_,_,_,_,b},
    {w,b,b,b,b,b,b,b,b,_,w,w,w,w,w,_},
    {w,b,b,b,b,b,b,b,b,_,w,b,b,b,b,_},
    {w,b,b,b,b,b,b,b,b,_,w,b,b,b,b,_},
    {w,b,b,b,b,b,b,b,b,_,w,b,b,b,b,_},
    {_,_,b,b,b,b,b,b,_,w,b,b,b,b,b,_},
    {w,w,_,_,b,b,b,b,_,w,b,b,b,b,b,_},
    {w,b,w,w,_,_,_,_,w,b,b,b,b,b,b,_},
    {w,b,b,b,w,w,w,_,w,b,b,b,b,b,b,_},
    {w,b,b,b,b,b,b,_,w,b,b,b,b,b,_,_},
    {b,_,_,_,_,_,_,b,w,_,_,_,_,_,_,b}
};
// clang-format on
/// @endcond


void Platform::paint(pro2::Window& window) const {
    const int xsz = platform_texture_.size();
    const int ysz = platform_texture_[0].size();
    for (int i = top_ + 1; i <= bottom_; i++) {
        for (int j = left_; j <= right_; j++) {
            window.set_pixel({j, i}, platform_texture_[(i - top_ - 1) % xsz][(j - left_) % ysz]);
        }
    }
}

bool Platform::has_crossed_floor_downwards(pro2::Pt plast, pro2::Pt pcurr) const {
    return (left_ <= plast.x && plast.x <= right_) && (left_ <= pcurr.x && pcurr.x <= right_) &&
           (plast.y <= top_ && pcurr.y >= top_);
}

bool Platform::is_pt_inside(pro2::Pt pt) const {
	return left_ <= pt.x && pt.x <= right_ && top_ <= pt.y && pt.y <= bottom_;
}