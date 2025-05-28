#ifndef GAME_HH
#define GAME_HH

#include <vector>
#include "mario.hh"
#include "platform.hh"
#include "window.hh"
#include "coin.hh"
#include "text.hh"
#include "finder.hh"


class Game {
    Mario                 mario_;
    std::vector<Platform> platforms_;
    std::vector<Coin>     coins_;

    Finder<Platform>      platform_finder;

    bool finished_;
    bool paused_;

    pro2::TextWriter TW_;

    void process_keys(pro2::Window& window);
    void update_objects(pro2::Window& window);
    void update_camera(pro2::Window& window);

 public:
    Game(int width, int height);

    void update(pro2::Window& window);
    void paint(pro2::Window& window);

    bool is_finished() const {
        return finished_;
    }
    
    bool is_paused() const {
        return paused_;
    }

    void spawn_coin(pro2::Pt pos, pro2::DoubPt vel);

 private:
    static constexpr int sky_blue = 0x5c94fc;
    
    static constexpr int anim_len = 10;
};

#endif