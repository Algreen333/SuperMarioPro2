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
 * La meva implementació de l'objecte finder consisteix en un contenidor, dividit en cel·les. 
 * Cada element s'afegirà a les cel·les que es corresponen amb les coordenades on es troba l'objecte.
 */
template <typename T>
class Finder {
    private:
        // Vector de caselles amb els objectes
        std::vector< std::set<T *> > _container;
        
        // Set d'apuntadors a les caselles on hi ha l'objecte
        std::map<T *, std::set<int> > _locator; 

        pro2::Pt _divider;
        pro2::Rect _range;
        pro2::Pt   _num_divs;

    public:
        /**
         * @brief   Crea un objecte Finder<T> i inicialitza el contenidor amb les cel·les buides.
         * @pre     Els objectes de tipus T han de tenir un mètode 'get_rect()' que retorni un pro2::Rect
         * 
         * @param range     pro2::Rect amb {xmin, ymin, xmax, ymax} del rang de coordenades que admet
         * @param divider   pro2::Pt amb el tamany de cada divisió del contenidor
         * 
         * Els valors per defecte són {0,0,MAX_SZ,MAX_SZ} i {MAX_SZ/NUM_DIVS,MAX_SZ/NUM_DIVS}, que per defecte
         * estan inicialitzades a MAX_SZ = 20000 i NUM_DIVS = 32 (valors emprats per a la solució del Jutge)
         */
        Finder (pro2::Rect range = {0,0,MAX_SZ,MAX_SZ}, pro2::Pt divider = {MAX_SZ/NUM_DIVS, MAX_SZ/NUM_DIVS}) : _range(range), _divider(divider), _num_divs({(range.right-range.left)/divider.x, (range.bottom-range.top)/divider.y}) 
        {
            _container = std::vector< std::set<T *> > (_num_divs.x*_num_divs.y);
        };

        /**
         * @brief Afegeix un element al finder.
         * 
         * @param t (T *t) Punter a l'element a afegir.
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
         * @brief   Actualitza les coordenades de l'objecte.
         * 
         * @param   T *t Punter a l'objecte
         * 
         * @pre     L'objecte apuntat *t ja és present al contenidor (s'ha afegit previament i no s'ha eliminat)
         */
        void update(T *t) {
            remove(t);
            add(t);
        };
        
        /**
         * @brief   Elimina un objecte del contenidor.
         * 
         * @param   T *t Punter a l'objecte
         * 
         * @pre     L'objecte apuntat *t ja és present al contenidor (s'ha afegit previament i no s'ha eliminat)
         */
        void remove(T *t) {
            for (std::set<int>::iterator it = _locator.find(t)->second.begin(); it != _locator.find(t)->second.end(); it++) {
                _container[*it].erase(t);
            }
            _locator.erase(t);
        };

        /**
         * @brief   Elimina un objecte del contenidor i el borra
         * 
         * @param   T *t Punter a l'objecte
         * 
         * @pre     L'objecte apuntat *t ja és present al contenidor (s'ha afegit previament i no s'ha eliminat)
         */
        void remove_and_delete(T *t) {
            remove(t);
            delete t;
        }
        
        /**
         * @brief   Retorna un set amb els punters que interseccionen amb 'rect'
         * 
         * @param   rect pro2::Rect amb les coordenades a comprovar
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
         * @brief   Afegeix tots els elements d'un set al finder.
         */
        void AddFromList(std::list<T> &set) {
            for (typename std::list<T>::const_iterator it = set.begin(); it != set.end(); it++) {
                add(&(*it));
            }
        }
};
    
#endif