#ifndef FINDER_HH
#define FINDER_HH

#include "geometry.hh"
#include <map>
#include <set>

bool point_inside(pro2::Rect rect, pro2::Pt point) {
    return point.x >= rect.left and point.x <= rect.right  and  point.y >= rect.top and point.y <= rect.bottom;
}


template <typename T>
class Finder {
    private:
        std::set<const T *> _container;

    public:
        Finder() {};

        void add(const T *t) {
            _container.insert(t);
        };
        void update(const T *t) {
            remove(t);
            add(t);
        };

        void remove(const T *t) {
            _container.erase(t);
        };

        std::set<const T *> query(pro2::Rect rect) const {
            std::set<const T *> result;
            for (typename std::set<const T*>::const_iterator it = _container.begin(); it != _container.end(); it++) {
                pro2::Rect obj_rect = (*it)->get_rect();
                if (point_inside(rect, {obj_rect.left, obj_rect.top}) or
                    point_inside(rect, {obj_rect.right, obj_rect.top}) or
                    point_inside(rect, {obj_rect.left, obj_rect.bottom}) or
                    point_inside(rect, {obj_rect.right, obj_rect.bottom})
                ) result.insert(*it);
            }
            return result;
        };
};

    
#endif