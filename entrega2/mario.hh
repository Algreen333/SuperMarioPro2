#ifndef MARIO_HH
#define MARIO_HH

#include <iostream>
#include <list>
#include "platform.hh"
#include "window.hh"
#include "block.hh"
#include "finder.hh"
#include "interactables.hh"

class Mario {
 private:
    pro2::Pt pos_, last_pos_;
    pro2::Pt speed_ = {0, 0};
    pro2::Pt accel_ = {0, 0};
    int      accel_time_ = 0;

    int key_up_;
    int key_left_;
    int key_right_;

    bool grounded_ = true;
	bool looking_left_ = false;

    int coin_count_ = 0;

    int state_ = 0;
    int anim_frame_counter_;
	
 public:
    Mario(int key_up, int key_left, int key_right, pro2::Pt pos): 
        key_up_(key_up), key_left_(key_left), key_right_(key_right),
        pos_(pos), last_pos_(pos)
        {}

    void paint(pro2::Window& window) const;

    pro2::Rect collision_box() const;

    pro2::Pt pos() const {
        return pos_;
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

    void jump();

    /**
     * @brief Afegeix monedes al comptador de monedes
     * 
     * @param ammount Quantitat de monedes (per defecte: 1)
     */
    void add_coin(int ammount = 1) {
        coin_count_ += ammount;
    }

    /**
     * @brief Retorna el valor del comptador de monedes
     */
    int get_coin_count() {
        return coin_count_; 
    }

    void update(pro2::Window& window, const Finder<Platform>& platforms, Finder<Block>& blocks, std::list<Interactable>& interactables);

    /**
     * @brief Canvia el estat del jugador a mario petit (0) o a mario gran (1). 
     *      També hi ha els estats 2 i 3 per passar de petit a gran i viceversa (s'usen per a les animacions)
     * 
     * @param new_state Nou estat al que passa el jugador
     */
    void set_state(int new_state);

    /**
     * @brief Retorna l'estat del mario: mario petit (0) o mario gran (1)
     */
    int get_state() const {return state_;}
    
 private:
    static const std::vector<std::vector<int>> mario_sprite_normal_;
    static const std::vector<std::vector<int>> mario_sprite_tall_;
};

#endif