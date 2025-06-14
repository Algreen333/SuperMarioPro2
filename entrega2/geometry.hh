#ifndef GEOMETRY_HH
#define GEOMETRY_HH

#include <utility>

namespace pro2 {

struct Pt {
    int x = 0, y = 0;
};

/**
 * @brief Compara dos punts del pla
 * 
 * La comparació és necessària per poder fer servir `Pt` com la clau d'un `map`.
 * La comparació utilitza primer la coordenada `x` (com si fos més "important"), 
 * i, quan les `x`s són iguals, la coordenada `y`.
 */
inline bool operator<(const Pt& a, const Pt& b) {
    return a.x != b.x ? a.x < b.x : a.y < b.y;
}

// Punts amb double
struct DoubPt {
    double x = 0, y = 0;
};

/**
 * @brief Retorna un pro2::Pt amb els valors truncats d'un pro2::DoubPt
*/
inline Pt round_dpt(const DoubPt& a) {
    return Pt{int(a.x), int(a.y)};
};

struct Rect {
    int left, top, right, bottom;
    int width() const {return right - left;}
    int height() const {return bottom - top;}
};

/**
 * @brief Retorna true si s'interseccionen els dos pro2::Rect
*/
inline bool check_collision(const Rect& a, const Rect& b) {
    return ((a.left <= b.left ? a.right >= b.left : a.left <= b.right) and (a.top <= b.top ? a.bottom >= b.top : a.top <= b.bottom));
};

/**
 * @brief Retorna true si s'ha interseccionat verticalment i un int amb la direcció: 1 si s'ha creuat des de sobre i -1 altrament
 */
std::pair<bool, int> resolve_collision_vertical(const Rect& prev, Rect curr, const Rect& block);

/**
 * @brief Retorna true si s'ha interseccionat verticalment i un int amb la direcció: 1 si s'ha creuat d'esquerra a dreta i -1 altrament
 */
std::pair<bool, int> resolve_collision_horizontal(const Rect& prev, Rect curr, const Rect& block);

}

#endif