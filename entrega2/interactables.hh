#ifndef INTERACTABLES_HH
#define INTERACTABLES_HH

#include <vector>
#include "geometry.hh"
#include "finder.hh"
#include "platform.hh"
#include "block.hh"
#include "utils.hh"
#include "window.hh"

/**
 * @brief La classe Interactable engloba tot tipus d'objectes que tenen un comportament diferent amb els que el mario pot interactuar. 
 * 
 * N'hi ha 3 tipus:
 * 
 * - 0: Moneda que és creada per un bloc quan el mario hi salta des de sota. 
 *      Actua com una animació, pujant cap a munt durant un temps i desapareixent automàticament.
 *      La moneda s'afegeix al comptador de monedes
 * 
 * - 1: Bolet que fa que el mario es faci gran.
 *      Un cop apareix el bolet, aquest es mou i es xoca amb les parets fins que el mario el toca
 * 
 * - 2: La bandera del final del nivell. 
 *      Un cop el mario la toca, es guanya el joc. 
 * 
 * - 3: És un 'goomba' enemic. Si el mario hi salta a sobre mor i crea una moneda, si el 'goomba' toca al mario, el mario mor.
 */
class Interactable {
    private:
        int type_; // 0 per moneda, 1 per bolet, 2 per bandera, 3 per goomba
        
        pro2::Pt pos_;
        int direction = 1;

        int despawn_timer_;

    public:
        Interactable(pro2::Pt pos, int type) : pos_(pos), type_(type), despawn_timer_((type==0)? 10 : -1) {};

        bool update(pro2::Window& window, const Finder<Platform>& platforms, const Finder<Block>& blocks);

        void paint(pro2::Window& window) const;

        pro2::Rect collision_box() const {
            if (type_ == 0) return {0,0,0,0};
            else if (type_ == 1 or type_ == 3) return {pos_.x, pos_.y, pos_.x + 15, pos_.y + 15};
            else return {pos_.x+7, pos_.y, pos_.x + 8, pos_.y + 168};
        }

        int type() const {return type_;}

        pro2::Pt pos() const {return pos_;}

    private:
        static const std::vector<std::vector<std::vector<int>>> sprites;
};

#endif