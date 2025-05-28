#ifndef FINDER_HH
#define FINDER_HH

#include "geometry.hh"
#include <algorithm>
#include <map>
#include <set>
#include <vector>


const int NUM_DIVS = 32;
const int MAX_SZ = 20000;
const int DIVIDER = MAX_SZ/NUM_DIVS;

template <typename T>
class Finder {
    private:
        // Vector de caselles amb els objectes
        std::vector< std::set<const T *> > _container;
        
        // Set d'apuntadors a les caselles on hi ha l'objecte
        std::map<const T *, std::set<int> > _locator; 

    public:
        Finder() {
            // Inicialitza les {NUM_DIVS*NUM_DIVS} caselles
            _container = std::vector< std::set<const T *> > (NUM_DIVS*NUM_DIVS);
        };

        void add(const T *t) {
            pro2::Rect rect = t->get_rect();
            for (int i = rect.top/DIVIDER; i <= rect.bottom/DIVIDER; i++) {
                for (int j = rect.left/DIVIDER; j <= rect.right/DIVIDER; j++) {
                    _container[i*NUM_DIVS + j].insert(t);
                    _locator[t].insert(i*NUM_DIVS + j);
                }
            }
        };
        
        void update(const T *t) {
            remove(t);
            add(t);
        };
        
        void remove(const T *t) {
            for (std::set<int>::iterator it = _locator.find(t)->second.begin(); it != _locator.find(t)->second.end(); it++) {
                _container[*it].erase(t);
            }
            _locator.erase(t);
        };
        
        std::set<const T *> query(pro2::Rect rect) const {
            std::set<const T *> result;
            for (int i = rect.top/DIVIDER; i <= rect.bottom/DIVIDER; i++) {
                for (int j = rect.left/DIVIDER; j <= rect.right/DIVIDER; j++) {
                    for (typename std::set<const T *>::const_iterator it = _container[i*NUM_DIVS + j].begin(); it != _container[i*NUM_DIVS + j].end(); it++) {
                        pro2::Rect obj_rect = (*it)->get_rect();
                        if ((rect.left <= obj_rect.left ? rect.right >= obj_rect.left : rect.left <= obj_rect.right) and (rect.top <= obj_rect.top ? rect.bottom >= obj_rect.top : rect.top <= obj_rect.bottom)) result.insert(*it);
                    } 
                }
            }

            return result;
        };
};

    
#endif