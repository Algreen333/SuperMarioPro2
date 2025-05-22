#ifndef FINDER_HH
#define FINDER_HH

#include "geometry.hh"
#include <map>
#include <set>

template <typename T>
class Finder {
    private:
    std::map<T *, pro2::Rect> objs_;

    // mapa[y][x]
    std::map<int, std::map<int, std::set<T *>>> container_;
        
    public:
    Finder() {}
    Finder(std::map<T *, pro2::Rect> objs, std::map<int, std::map<int, T *>> container) : objs_(objs), container_(container) {}
        
    void add(const T *t);
    void update(const T *t);
    void remove(const T *t);
        
    /**
     * @brief Retorna el conjunt d'objectes amb rectangles 
     *        total o parcialment dins de `rect`.
     *
     * Si el nombre de rectangles del contenidor és `n`, el 
     * cost de l'algorisme ha de ser O(log n).
     *
     * @param rect El rectangle de cerca
     *
     * @returns Un conjunt de punters a objectes que tenen un 
     *          rectangle parcial o totalment dins de `rect`
     */
    std::set<const T *> query(pro2::Rect rect) const;
};

    
#endif   