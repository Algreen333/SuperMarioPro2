#ifndef FINDER_HH
#define FINDER_HH

#include "geometry.hh"
#include <algorithm>
#include <map>
#include <set>



template <typename T>
class Finder {
    private:
        std::set<std::pair<int, const T *>> _xs;
        std::set<std::pair<int, const T *>> _ys;

        std::map<const T *, pro2::Rect> _locator;
        
    public:
        Finder() {};

        void add(const T *t) {
            pro2::Rect rect = t->get_rect();

            _xs.insert({rect.left, t});
            _xs.insert({rect.right, t});

            _ys.insert({rect.top, t});
            _ys.insert({rect.bottom, t});

            _locator[t] = rect;
        };
        void update(const T *t) {
            pro2::Rect rect = _locator[t];
            remove_xs_and_ys(t, rect);
            _locator.erase(t);
            add(t);
        };
        void remove(const T *t) {
            pro2::Rect rect = t->get_rect();
            remove_xs_and_ys(t, rect);
            _locator.erase(t);
        };
        void remove_xs_and_ys(const T *t, pro2::Rect rect) {
            _xs.erase({rect.left, t});
            _xs.erase({rect.right, t});

            _ys.erase({rect.top, t});
            _ys.erase({rect.bottom, t});
        }

        std::set<const T *> query(pro2::Rect rect) const {
            std::set<const T *> result;
            std::set_intersection(_xs.lower_bound({rect.left, _xs.begin()->second}), _xs.upper_bound({rect.right, _xs.begin()->second}), _ys.lower_bound({rect.top, _ys.begin()->second}), _ys.upper_bound({rect.bottom, _ys.begin()->second}), result.begin());
            return result;
        };
};

    
#endif