#ifndef GAME_HH
#define GAME_HH

#include <list>
#include "mario.hh"
#include "platform.hh"
#include "window.hh"
#include "coin.hh"
#include "text.hh"
#include "finder.hh"
#include "block.hh"
#include "pickup.hh"


class Game {
    Mario               mario_;
    Finder<Platform>    platforms_;
    Finder<Coin>        coins_;
    Finder<Block>       blocks_;
    
    std::list<Pickup>    pickups_;
    
    pro2::Rect          death_barrier_;

    int curr_anim_frame_ = 0;

    bool finished_;
    int exit_code_ = 0;
    bool paused_;

    pro2::TextWriter TW_;

    void process_keys(pro2::Window& window);
    void update_objects(pro2::Window& window);
    void update_camera(pro2::Window& window);

 public:
    Game(int width, int height, pro2::TextWriter TW, pro2::Rect death_barrier=pro2::Rect{-1000, -2000, 100000, 400});

    void update(pro2::Window& window);
    void paint(pro2::Window& window);

    bool is_finished() const {
        return finished_;
    }
    
    bool is_paused() const {
        return paused_;
    }

    /**
     * @brief Retorna 1 si el jugador ha mort, 2 si s'ha guanyat o 0 altrament
     */
    int exit_code() const {return exit_code_;}

    void spawn_coin(pro2::Pt pos, pro2::DoubPt vel);

    /**
     * @brief Actualitza el comptador de l'animació per passar al següent sprite.
     */
    void anim_step() {
        curr_anim_frame_++;
        curr_anim_frame_ %= 18;
    }

 private:
    static constexpr int sky_blue = 0x5c94fc;
    
    static constexpr int anim_len = 10;
};

#endif