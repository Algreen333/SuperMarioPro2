#include "game.hh"
#include "game.hh"
#include "utils.hh"
#include <iostream>
using namespace pro2;

Game::Game(int width, int height): 
    mario_(Keys::Up, Keys::Left, Keys::Right, {width / 2, 150}),
    platforms_finder_(Finder<Platform>({-10000,-10000,100000,100000}, {100, 100})),
    coins_finder_(Finder<Coin>({-10000,-10000,100000,100000}, {100, 100})),

    finished_(false), 
    TW_("assets/6x10rounded.txt","assets/colors.txt")
    {
    for (int i = 1; i < 10; i++) {
        Platform plat = Platform(250 + i * 200, 400 + i * 200, 150, 161);
        platforms_finder_.add(&plat);
        for (int j = 1; j < 10; j++) {
            Coin c = Coin({250 + i * 200 + 15 * j, 150});
            coins_finder_.add(&c);
        }
    }

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
    // Update only the objects that are near
    const Pt cam = window.camera_center();

    const int left = cam.x - window.width() / 2;
    const int right = cam.x + window.width() / 2;
    const int top = cam.y - window.height() / 2;
    const int bottom = cam.y + window.height() / 2;

    pro2::Rect processing_box = {left-20, top-20, right+20, bottom+20};
    
    std::set<const Platform *> near_platforms = platforms_finder_.query(processing_box);
    mario_.update(window, near_platforms);
    
    pro2::Rect mario_collision_box = mario_.collision_box();
    for (const Coin* c : coins_finder_.query(mario_collision_box)) {
        coins_finder_.remove(c);
        mario_.add_coin();
    }
    
    for (const Coin* c : coins_finder_.query(processing_box)) {
        Coin new_c = *c;
        coins_finder_.remove(c);
        new_c.update(window, near_platforms);
        coins_finder_.add(&new_c);
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
    std::cout << "TEST" << std::endl;
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
    
    std::set<const Platform *> platforms_to_draw = platforms_finder_.query(view_box);
    std::cout << platforms_to_draw.size() << std::endl;
    for (std::set<const Platform *>::const_iterator it = platforms_to_draw.begin(); it != platforms_to_draw.end(); it++) {
        (*it)->paint(window);
    }
    
    for (const Coin* c : coins_finder_.query(view_box)) {
        c->paint(window);
    }
    
    
    mario_.paint(window);

    TW_.write_text(window, {right - int(12*std::to_string(mario_.get_coin_count()).size()), top + 2}, std::to_string(mario_.get_coin_count()), 2, 2);
}

void Game::spawn_coin(pro2::Pt pos, pro2::DoubPt vel) {
    Coin new_coin(pos, vel, {0,0});
    coins_finder_.add(&new_coin);
}