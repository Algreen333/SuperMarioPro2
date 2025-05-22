#ifndef FINDER_HH
#define FINDER_HH

#include "geometry.hh"
#include <map>
#include <set>


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
                if ((rect.left <= obj_rect.left ? rect.right >= obj_rect.left : rect.left <= obj_rect.right) and (rect.top <= obj_rect.top ? rect.bottom >= obj_rect.top : rect.top <= obj_rect.bottom)) result.insert(*it);
            }
            return result;
        };
};

    
#endif