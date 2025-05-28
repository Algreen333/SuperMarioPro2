#ifndef FINDER_HH
#define FINDER_HH

#include <set>
#include <map>
#include <vector>
#include "geometry.hh"


template <class T>
bool comparelesstop(const T * a, const T * b) {
    int ra = a->get_rect().top;
    int rb = b->get_rect().top;
    
    return (ra == rb)? a < b : ra < rb;
}
template <class T>
bool comparelessbottom(const T * a, const T * b) {
    int ra = a->get_rect().bottom;
    int rb = b->get_rect().bottom;
    
    return (ra == rb)? a < b : ra < rb;
}
template <class T>
bool comparelessleft(const T * a, const T * b) {
    int ra = a->get_rect().left;
    int rb = b->get_rect().left;
    
    return (ra == rb)? a < b : ra < rb;
}
template <class T>
bool comparelessright(const T * a, const T * b) {
    int ra = a->get_rect().right;
    int rb = b->get_rect().right;
    
    return (ra == rb)? a < b : ra < rb;
}


template <class T>
class Finder {
    private:
        std::set<const T *, comparelesstop> topwise;
        std::set<const T *, comparelessbottom> bottomwise;
        std::set<const T *, comparelessleft> leftwise;
        std::set<const T *, comparelessright> rightwise;
    
    public:
        Finder();

        void add(const T *t) {
            topwise.insert(t);
            bottomwise.insert(t);
            leftwise.insert(t);
            rightwise.insert(t);
        };

        void update(const T *t) {
            remove(t);
            add(t);
        };

        void remove(const T *t) {
            topwise.erase(t);
            bottomwise.erase(t);
            leftwise.erase(t);
            rightwise.erase(t);
        };

        std::set<const T *> query(pro2::Rect rect) const {
            std::set<const T *> 
        };
};

#endif