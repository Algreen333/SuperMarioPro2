#include "game.hh"
#include "utils.hh"
#include <iostream>
using namespace pro2;

Game::Game(int width, int height, TextWriter TW, pro2::Rect death_barrier): 
    mario_(Keys::Up, Keys::Left, Keys::Right, {width / 2, 150}),
    platforms_(Finder<Platform>({-10000,-10000,100000,100000}, {100,100})),
    coins_(Finder<Coin>({-10000,-1000,100000,1000}, {100,100})),
    blocks_(Finder<Block>({-10000,-1000,100000,1000}, {100,100})),
    finished_(false), 
    TW_(TW),
    paused_(false)
    {
    /*
    for (int i = 1; i < 1000; i++) {
        platforms_list_.emplace_back(i * 200, 150 + i * 200, 150, 161);
        platforms_.add(&platforms_list_.back());
        for (int j = 1; j < 10; j++) {
            coins_list_.emplace_back(pro2::Pt{i * 200 + 15 * j, 150});
            coins_.add(&coins_list_.back());
        }
    }
    */
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            blocks_list_.emplace_back(0, pro2::Pt{(i*14 + j)*16, 172});
            blocks_.add(&blocks_list_.back());
            coins_list_.emplace_back(pro2::Pt{(i*14 + j)*16 + 8, 170});
            coins_.add(&coins_list_.back());
        }
    }
    blocks_list_.emplace_back(0, pro2::Pt{16, 156});
    blocks_.add(&blocks_list_.back());
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
    anim_step();

    // Check colision with mario and coins
    pro2::Rect mario_collision_box = mario_.collision_box();
    std::set<Coin *> colliding_coins = coins_.query(mario_collision_box);

    for (Coin * c : coins_.query(mario_collision_box)) {
        coins_.remove(c);
        coins_list_.remove_if([c](const Coin& coin) {
            return &coin == c;
        });

        mario_.add_coin();
    }

    // Process objects within processing box
    const Pt cam = window.camera_center();
    pro2::Rect processing_box = {
        cam.x - window.width() / 2 - 10, 
        cam.y - window.height() / 2 - 10, 
        cam.x + window.width() / 2 + 10, 
        cam.y + window.height() / 2 + 10
    };

    std::set<Platform *> close_platforms = platforms_.query(processing_box);
    std::set<Block *> close_blocks = blocks_.query(processing_box);

    mario_.update(window, close_platforms, close_blocks);

    for (Coin * c : coins_.query(processing_box)) {
        c->update(window, close_platforms);
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

    const Pt cam = window.camera_center();
    pro2::Rect view_box = {
        cam.x - window.width() / 2, 
        cam.y - window.height() / 2, 
        cam.x + window.width() / 2, 
        cam.y + window.height() / 2
    };
        
    for (Platform* platform : platforms_.query(view_box)) {
        platform->paint(window);
    }

    for (Coin* c : coins_.query(view_box)) {
        c->paint(window, curr_anim_frame_);
    }

    for (Block* block : blocks_.query(view_box)) {
        block->paint(window, curr_anim_frame_);
    }

    mario_.paint(window);
    
    Sprite coin_sprite = Coin::sprites[0];
    paint_sprite(window, {cam.x - 12 + window.width() / 2, cam.y - window.height() / 2 + 2}, coin_sprite, false);

    TW_.write_text(window, {cam.x - 16 + window.width() / 2, cam.y - window.height() / 2 + 2}, std::to_string(mario_.get_coin_count()), 2, 2, {2,0});
    
    if (paused_) {
        //pro2::paint_rect_fill(window, view_box, 0xFF0000);
        pro2::paint_rect_fill_transparent(window, view_box, 0, 0.2);
        TW_.write_text(window, {cam.x, cam.y}, "PAUSED", 4,4, {1,1});
    }
}

void Game::spawn_coin(pro2::Pt pos, pro2::DoubPt vel) {
    coins_list_.emplace_back(pos, vel, DoubPt{0,0});
    coins_.add(&coins_list_.back());
}