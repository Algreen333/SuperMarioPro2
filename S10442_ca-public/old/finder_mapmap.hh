#ifndef FINDER_HH
#define FINDER_HH

#include "geometry.hh"
#include <map>
#include <set>


template <typename T>
class Finder {
    private:
        std::map< pro2::Pt, std::set<const T *>> _container;
        std::map<const T *, pro2::Rect> _locator;

    public:
        Finder() {};

        void add(const T *t) {
            pro2::Rect rect = t->get_rect();
            _container[rect.left][rect.top].insert(t);
            _container[rect.right][rect.top].insert(t);
            _container[rect.left][rect.bottom].insert(t);
            _container[rect.right][rect.bottom].insert(t);
            _locator[t] = rect;
        };
        void update(const T *t) {
            pro2::Rect rect = _locator[t];
            _container[rect.left][rect.top].erase(t);
            _container[rect.right][rect.top].erase(t);
            _container[rect.left][rect.bottom].erase(t);
            _container[rect.right][rect.bottom].erase(t);
            add(t);
        };
        void remove(const T *t) {
            pro2::Rect rect = t->get_rect();
            _container[rect.left][rect.top].erase(t);
            _container[rect.right][rect.top].erase(t);
            _container[rect.left][rect.bottom].erase(t);
            _container[rect.right][rect.bottom].erase(t);
            _locator.erase(t);
        };

        std::set<const T *> query(pro2::Rect rect) const {
            std::set<const T *> result;
            typename std::map<int, std::map<int, std::set<const T *> > >::const_iterator x = _container.lower_bound(rect.left);
            typename std::map<int, std::map<int, std::set<const T *> > >::const_iterator x_end = _container.upper_bound(rect.right);
        
            while (x != x_end) {
                typename std::map<int, std::set<const T *> >::const_iterator y = (x->second).lower_bound(rect.top);
                typename std::map<int, std::set<const T *> >::const_iterator y_end = (x->second).upper_bound(rect.bottom);
                
                while (y != y_end) {
                    for (typename std::set<const T *>::const_iterator it = (y->second).begin(); it != (y->second).end(); it++) {
                        result.insert(*it);
                    }
                    y++;
                }
                x++;
            }

            return result;
        };
};

    
#endif