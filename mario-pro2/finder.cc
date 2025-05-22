#include "finder.hh"
#include "geometry.hh"
#include "utils.hh"

using namespace std;

template <typename T> void Finder<T>::add(const T *t) {
    pro2::Rect rect = t->get_rect();
    container_[rect.top][rect.left].insert(t);
    container_[rect.top][rect.right].insert(t);
    container_[rect.bottom][rect.left].insert(t);
    container_[rect.bottom][rect.right].insert(t);

    objs_[t] = rect;
}

template <typename T> void Finder<T>::remove(const T *t) {
    pro2::Rect rect = objs_[t];
    container_[rect.top][rect.left].erase(t);
    container_[rect.top][rect.right].erase(t);
    container_[rect.bottom][rect.left].erase(t);
    container_[rect.bottom][rect.right].erase(t);
    
    objs_.erase(rect);
}

template <typename T> void Finder<T>::update(const T *t) {
    remove(t);
    add(t);
}

template <typename T> std::set<const T *> Finder<T>::query(pro2::Rect rect) const {
    std::set<const T *> result;
    std::map<T *, bool> found;
    for (int y = rect.top; y < rect.bottom; y++) {
        for (int x = rect.left; x < rect.right; x++) {
            T *t = container_[y][x];
            if (not found[t]) {
                found[t] = true;
                result.insert(t);
            }
        }
    }
}