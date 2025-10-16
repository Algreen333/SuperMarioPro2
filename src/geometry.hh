#ifndef GEOMETRY_HH
#define GEOMETRY_HH

#include <utility>

namespace pro2 {

struct Pt {
    int x = 0, y = 0;

    Pt operator+(const Pt& other) const {
        return {x + other.x, y + other.y};
    }
    Pt operator-(const Pt& other) const {
        return {x - other.x, y - other.y};
    }

    Pt& operator+=(const Pt& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    Pt& operator-=(const Pt& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
};

/**
 * @brief Compares two points
 * 
 * The comparation is necessary for `Pt` to be used as a `map` key.
 * It first checks the `x` coordinate, and if they are equal, it checks the `y` coordinate.
 */
inline bool operator<(const Pt& a, const Pt& b) {
    return a.x != b.x ? a.x < b.x : a.y < b.y;
}

// `double` coordinate points
struct DoubPt {
    double x = 0, y = 0;
};

/**
 * @brief Returns a `pro2::Pt` with the truncated values of a `pro2::DoubPt`.
*/
inline Pt round_dpt(const DoubPt& a) {
    return Pt{int(a.x), int(a.y)};
};

struct Rect {
    int left, top, right, bottom;
    int width() const {return right - left;}
    int height() const {return bottom - top;}

    Rect& operator+=(const Rect& other) {
        left += other.left;
        right += other.right;
        top += other.top;
        bottom += other.bottom;
        return *this;
    }

    Rect& operator-=(const Rect& other) {
        left -= other.left;
        right -= other.right;
        top -= other.top;
        bottom -= other.bottom;
        return *this;
    }
};

/**
 * @brief Returns true if the two `pro2::Rect` are intersecting.
*/
inline bool check_collision(const Rect& a, const Rect& b) {
    return ((a.left <= b.left ? a.right >= b.left : a.left <= b.right) and (a.top <= b.top ? a.bottom >= b.top : a.top <= b.bottom));
};

/**
 * @brief Returns true if it has crossed the rect vertically and an integer with the direction in which it has coressed:
 * - 1 if it has crossed from below.
 * - -1 if it has crossed from above.
 */
std::pair<bool, int> resolve_collision_vertical(const Rect& prev, Rect curr, const Rect& block);

/**
 * @brief Returns true if it has crossed the rect horizontally and an integer with the direction in which it has coressed:
 * - 1 if it has crossed from left to right.
 * - -1 if it has crossed from right to left.
 */
std::pair<bool, int> resolve_collision_horizontal(const Rect& prev, Rect curr, const Rect& block);

}

#endif