#ifndef COIN_HH
#define COIN_HH

#include <iostream>
#include <vector>
#include <set>
#include "platform.hh"
#include "window.hh"

class Coin {
 private:
    double gravity = 1;
    
    pro2::Pt pos_, last_pos_;
    pro2::DoubPt speed_;
    pro2::DoubPt accel_;        // L'acceleració per defecte és -gravetat (moneda estàtica)
    pro2::DoubPt drag_coef_;    // F = -b*v

    bool grounded_ = false;
    
    int curr_anim_frame_ = 0;

	void apply_physics_();
	
 public:
    
    /**
     * @brief Les monedes s'inicialitzen amb una posició inicial i, opcionalment, amb velocitat, acceleració i coeficient de drag.
     * En cas de deixar la velocitat, accel i drag en els seus valors per defecte, la moneda s'inicialitzarà estàtica, sense ser afectada per la gravetat
     * 
     * @param pos   Posició
     * @param speed Velocitat
     * @param accel Acceleració
     * @param drag  Coeficient de drag
     */
    Coin(pro2::Pt pos, pro2::DoubPt speed = {0, 0}, pro2::DoubPt accel = {0, -1}, pro2::DoubPt drag = {0.075, 0.075}) : pos_(pos), last_pos_(pos), speed_(speed), accel_(accel), drag_coef_(drag) {}

    /**
     * @brief Pinta el sprite de la moneda corresponent amb l'animació
     * 
     * @param window Finestra on es dibuixarà
     */
    void paint(pro2::Window& window) const;

    pro2::Pt pos() const {
        return pos_;
    }

    pro2::Rect collision_box() const;

    inline pro2::Rect get_rect() const {
        return {pos_.x, pos_.y, pos_.x + sz_w, pos_.y + sz_h};
    }

    /**
     * @brief Retorna la matriu del sprite del frame de l'animació corresponent
     */
    inline std::vector<std::vector<int>> get_sprite() const {
        return sprites[animation[curr_anim_frame_]];
    }

    void set_y(int y) {
        pos_.y = y;
    }

    bool is_grounded() const {
        return grounded_;
    }

    void set_grounded(bool grounded) {
        grounded_ = grounded;
        if (grounded_) {
            speed_.y = 0;
        }
    }

    void toggle_grounded() {
        set_grounded(!grounded_);
    }

    void update(pro2::Window& window, const std::set<const Platform *>& platforms);
    
    /**
     * @brief Actualitza el comptador de l'animació per passar al següent sprite.
     */
    void anim_step() {
        curr_anim_frame_++;
        curr_anim_frame_ %= animation.size();
    }

 private:
    static const std::vector<std::vector<std::vector<int>>> sprites;    // Vector de els diferents sprites de l'animació
    static const std::vector<int> animation;                            // Vector amb els índex dels sprites de l'animació
    static const int sz_h;
    static const int sz_w;
};

#endif