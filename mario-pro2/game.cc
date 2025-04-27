#include <cstdlib>
#include "game.hh"
#include "utils.hh"
using namespace pro2;


Game::Game(int width, int height)
    : mario_(Keys::Up, Keys::Left, Keys::Right, {width / 2, 150}),
      platforms_{
          Platform(100, 300, 200, 211),
          Platform(0, 200, 250, 261),
          Platform(250, 400, 150, 161),
      },
      coins_{
        Coin({width/2, 100}),
        Coin({width/2, 120}, {0,-10}, {0,0}),
        Coin({width/2, 120}, {15, -10}, {0,0}),
        Coin({width/2 - 150, 120}, {25, -15}, {0,0})
      },
      finished_(false), TW_("assets/6x10rounded.txt","assets/colors.txt")
    {
    for (int i = 1; i < 20; i++) {
        platforms_.push_back(Platform(250 + i * 200, 400 + i * 200, 150, 161));
        platforms_.push_back(Platform(0, 11, 150 + 50 * i, 161 + 50 * i));
    }
    paused_ = false;

    TW_.set_charset("assets/charset.txt");
}

void Game::process_keys(pro2::Window& window) {
    if (window.is_key_down(Keys::Escape)) {
        finished_ = true;
    }

    if (window.was_key_pressed('P')) {
        paused_ = not paused_;
    }

    if (window.was_key_pressed('I')) {
        DoubPt vel = {random_double(-10, 10, 100), random_double(-20, -10, 100)};
        spawn_coin({mario_.pos().x, mario_.pos().y - 40}, vel);
    }
}

void Game::update_objects(pro2::Window& window) {
    mario_.update(window, platforms_);
    
    pro2::Rect mario_collision_box = mario_.collision_box();

    std::vector<Coin>::iterator coin_it = coins_.begin();
    while (coin_it != coins_.end()) {
        if (check_collision(mario_collision_box, (*coin_it).collision_box())) {
            coin_it = coins_.erase(coin_it);
            mario_.add_coin();
        }
        else {
            coin_it++;
        }
    }

    for (int i = 0; i < coins_.size(); i++) {
        coins_[i].update(window, platforms_);
    }
}

void Game::update_camera(pro2::Window& window) {
    const Pt pos = mario_.pos();
    const Pt cam = window.camera_center();

    const int left = cam.x - window.width() / 4;
    const int right = cam.x + window.width() / 4;
    const int top = cam.y - window.height() / 4;
    const int bottom = cam.y + window.height() / 4;

    int dx = 0, dy = 0;
    
    if (pos.x > right) {
        dx = pos.x - right;
    } else if (pos.x < left) {
        dx = pos.x - left;
    }
    if (pos.y < top) {
        dy = pos.y - top;
    } else if (pos.y > bottom) {
        dy = pos.y - bottom;
    }
    
    window.move_camera({dx, dy});
    

    /* Exercici 0.4
    window.move_camera({pos.x - cam.x, pos.y - cam.y});
    */
}

void Game::update(pro2::Window& window) {
    process_keys(window);
    if (not paused_) {
        update_objects(window);
        update_camera(window);
    }
}

void Game::paint(pro2::Window& window) {
    window.clear(sky_blue);

    Pt cam_pos = window.camera_center();
    pro2::Rect mario_collision_box = mario_.collision_box();
        
    for (const Platform& p : platforms_) {
        p.paint(window);
    }

    for (const Coin& c : coins_) {
        c.paint(window);
        /*
        if (check_collision(mario_collision_box, c.collision_box())){
            paint_rect(window, c.collision_box(), pro2::green, 1);
        }
        else {
            paint_rect(window, c.collision_box(), pro2::yellow, 1);
        }
        */
    }

    mario_.paint(window);

    const Pt cam = window.camera_center();

    const int right = cam.x + window.width() / 2;
    const int top = cam.y - window.height() / 2;

    TW_.write_text(window, {right - int(12*std::to_string(mario_.get_coin_count()).size()), top + 2}, std::to_string(mario_.get_coin_count()), 2, 2);

    //paint_rect(window, mario_.collision_box(), pro2::red, 1);
}

void Game::spawn_coin(pro2::Pt pos, pro2::DoubPt vel) {
    Coin new_coin(pos, vel, {0,0});
    coins_.push_back(new_coin);
}