#ifndef FINDER_HH
#define FINDER_HH

#include "geometry.hh"
#include <algorithm>
#include <map>
#include <set>
#include <list>
#include <iostream>


const int NUM_DIVS = 32;
const int MAX_SZ = 20000;
const int DIVIDER = MAX_SZ/NUM_DIVS;



/**
 * This class consists in a container divided into cells. 
 * Each object will be added to the corresponding cell based on its coordinates.
 */
template <typename T>
class Finder {
    private:
        // Vector of cells with the objects
        std::vector< std::set<T *> > _container;
        
        // Map with the pointers to the cells
        std::map<T *, std::set<int> > _locator; 

        pro2::Pt _divider;
        pro2::Rect _range;
        pro2::Pt   _num_divs;

    public:
        /**
         * @brief Creates a Finder<T> object and initializes the container with empty cells.
         * @pre   Thr type 'T' objects must have a get_rect method that returns a pro2:Rect
         * 
         * @param range     pro2::Rect with {xmin, ymin, xmax, ymax} of the range of coordinates it accepts
         * @param divider   pro2::Pt with the size of each cell
         * 
         * The default values are {0, 0, MAX_SZ, MAX_SZ} and {MAX_SZ/NUM_DIVS, MAX_SZ/NUM_DIVS}, 
         * with MAX_SZ = 20000 and NUM_DIVS = 32
         */
        Finder (pro2::Rect range = {0,0,MAX_SZ,MAX_SZ}, pro2::Pt divider = {MAX_SZ/NUM_DIVS, MAX_SZ/NUM_DIVS}) : _range(range), _divider(divider), _num_divs({(range.right-range.left)/divider.x, (range.bottom-range.top)/divider.y}) 
        {
            _container = std::vector< std::set<T *> > (_num_divs.x*_num_divs.y);
        };

        /**
         * @brief Adds an element to finder.
         * 
         * @param t (T *t) Pointer to the element to be added.
         */
        void add(T *t) {
            pro2::Rect rect = t->get_rect();
            for (int i = (rect.top - _range.top)/_divider.y; i <= (rect.bottom - _range.top)/_divider.y; i++) {
                for (int j = (rect.left - _range.left)/_divider.x; j <= (rect.right - _range.left)/_divider.x; j++) {
                    _container[i*_num_divs.y + j].insert(t);
                    _locator[t].insert(i*_num_divs.y + j);
                }
            }
        };
        
        /**
         * @brief   Updates an object's coordinates
         * 
         * @param   T *t Pointer to the object
         * 
         * @pre     The object must already be present in the container.
         */
        void update(T *t) {
            remove(t);
            add(t);
        };
        
        /**
         * @brief   Removes an object from the container.
         * 
         * @param   T *t Pointer to the object.
         * 
         * @pre     The object must already be present in the container.
         */
        void remove(T *t) {
            for (std::set<int>::iterator it = _locator.find(t)->second.begin(); it != _locator.find(t)->second.end(); it++) {
                _container[*it].erase(t);
            }
            _locator.erase(t);
        };

        /**
         * @brief   Removes an objet from the conainer and deletes it.
         * 
         * @param   T *t Pointer to the object.
         * 
         * @pre     The object must already be present in the container.
         */
        void remove_and_delete(T *t) {
            remove(t);
            delete t;
        }
        
        /**
         * @brief   Returns a set with the pointers which are within the rect.
         * 
         * @param   rect pro2::Rect with the coordinates to check
         */
        std::set<T *> query(pro2::Rect rect) const {
            std::set<T *> result;
            for (int i = (rect.top - _range.top)/_divider.y; i <= (rect.bottom - _range.top)/_divider.y; i++) {
                for (int j = (rect.left - _range.left)/_divider.x; j <= (rect.right - _range.left)/_divider.x; j++) {
                    for (typename std::set<T *>::const_iterator it = _container[i*_num_divs.y + j].begin(); it != _container[i*_num_divs.y + j].end(); it++) {
                        pro2::Rect obj_rect = (*it)->get_rect();
                        if (not(rect.left > obj_rect.right or rect.right < obj_rect.left or rect.top > obj_rect.bottom or rect.bottom < obj_rect.top)) result.insert(*it);
                    } 
                }
            }
            return result;
        };

        /**
         * @brief   Adds all of the element from a list to the container.
         */
        void AddFromList(std::list<T> &set) {
            for (typename std::list<T>::const_iterator it = set.begin(); it != set.end(); it++) {
                add(&(*it));
            }
        }
};
    
#endif