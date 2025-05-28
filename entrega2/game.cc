#include "game.hh"
#include "game.hh"
#include "utils.hh"
#include <iostream>
using namespace pro2;

Game::Game(int width, int height): 
    mario_(Keys::Up, Keys::Left, Keys::Right, {width / 2, 150}),
    platforms_{
        Platform(100, 300, 200, 211),
        Platform(0, 200, 250, 261),
        Platform(250, 400, 150, 161),
    },
    coins_{
      Coin({width/2, 100}),
      Coin({width/2 + 50, 100}),
      Coin({width/2 + 100, 100}),
      Coin({width/2, 120}, {0,-10}, {0,0}),
      Coin({width/2, 120}, {15, -10}, {0,0}),
      Coin({width/2 - 150, 120}, {25, -15}, {0,0})
    },
    finished_(false), 
    TW_("assets/6x10rounded.txt","assets/colors.txt")
    {
    for (int i = 1; i < 200000; i++) {
        platforms_.push_back(Platform(250 + i * 200, 400 + i * 200, 150, 161));
    }

    //Finder<Platform> platform_finder = InitializeFinder(platforms_);
    platform_finder = Finder<Platform>({-10000,-10000,100000,100000}, {100,100});
    platform_finder.AddFromVector(platforms_);
    platform_finder.add(&platforms_[0]);
    platform_finder.add(&platforms_[1]);
    platform_finder.add(&platforms_[2]);

    TW_.set_charset("assets/charset.txt");
}

void Game::process_keys(pro2::Window& window) {
    if (window.is_key_down(Keys::Escape)) {
        finished_ = true;
        return;
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

    pro2::Rect mario_collision_box = mario_.collision_box();

    const Pt cam = window.camera_center();

    const int left = cam.x - window.width() / 2;
    const int right = cam.x + window.width() / 2;
    const int top = cam.y - window.height() / 2;
    const int bottom = cam.y + window.height() / 2;

    pro2::Rect view_box = {left, top, right, bottom};

    std::set<const Platform *> platforms_to_draw = platform_finder.query(view_box);
        
    for (std::set<const Platform *>::const_iterator it = platforms_to_draw.begin(); it != platforms_to_draw.end(); it++) {
        (*it)->paint(window);
    }

    for (const Coin& c : coins_) {
        c.paint(window);
    }

    mario_.paint(window);

    TW_.write_text(window, {right - int(12*std::to_string(mario_.get_coin_count()).size()), top + 2}, std::to_string(mario_.get_coin_count()), 2, 2);
}

void Game::spawn_coin(pro2::Pt pos, pro2::DoubPt vel) {
    Coin new_coin(pos, vel, {0,0});
    coins_.push_back(new_coin);
}