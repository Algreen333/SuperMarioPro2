#include "game.hh"
#include "utils.hh"
using namespace pro2;

Game::Game(int width, int height, TextWriter TW, pro2::Rect death_barrier): 
    mario_(Keys::Up, Keys::Left, Keys::Right, {width / 2, 50}),
    platforms_(Finder<Platform>({-10000,-10000,100000,100000}, {100,100})),
    coins_(Finder<Coin>({-10000,-1000,100000,1000}, {100,100})),
    blocks_(Finder<Block>({-10000,-1000,100000,1000}, {100,100})),
    finished_(false), 
    TW_(TW),
    paused_(false),
    death_barrier_(death_barrier)
    {
    
    platforms_.add(new Platform{0, 2000, 170, 500});
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j <= i; j++) {
            blocks_.add(new Block{pro2::Pt{300 + 16*i, 155 - 16*j}, 3});
        }
    }

    blocks_.add(new Block{pro2::Pt{500, 107}, 0});
    blocks_.add(new Block{pro2::Pt{516, 107}, 0, 1});
    blocks_.add(new Block{pro2::Pt{548, 107}, 1, 1});
    blocks_.add(new Block{pro2::Pt{564, 107}, 1, 2});

    pickups_.emplace_back(pro2::Pt{700, 3}, 2);
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
    if (window.was_key_pressed('J')) {
        pickups_.emplace_back(mario_.pos() + Pt{0, -100}, 1);
    }
}

void Game::update_objects(pro2::Window& window) {
    anim_step();

    // Check colision with mario and coins
    pro2::Rect mario_collision_box = mario_.collision_box();
    std::set<Coin *> colliding_coins = coins_.query(mario_collision_box);

    for (Coin * c : coins_.query(mario_collision_box)) {
        coins_.remove_and_delete(c);
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

    mario_.update(window, platforms_, blocks_, pickups_);
    
    // Mira que el mario no s'hagi sortit dels límits
    pro2::Pt pos = mario_.pos();
    if (pos.x < death_barrier_.left or pos.x > death_barrier_.right or pos.y < death_barrier_.top or pos.y > death_barrier_.bottom) {
        finished_ = true;
        exit_code_ = 1;
        std::cout << pos.x << ", " << pos.y << std::endl;
        std::cout << death_barrier_.left << ", " << death_barrier_.top << ", " << death_barrier_.right << ", " << death_barrier_.bottom << std::endl;
    }


    for (Coin * c : coins_.query(processing_box)) {
        c->update(window, close_platforms);
    }

    std::list<Pickup>::iterator p = pickups_.begin();
    while (p != pickups_.end()) {
        bool res = p->update(window, platforms_, blocks_);
        if (p->type() == 1 and check_collision(mario_.collision_box(), p->collision_box())) {
            p = pickups_.erase(p);
            mario_.change_state(1);
        }
        else if (res) {
            p = pickups_.erase(p);
        }
        if (p->type() == 2 and check_collision(mario_.collision_box(), p->collision_box())) {
            finished_ = true;
            exit_code_ = 2;
            p++;
        }
        else p++;
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

    for (std::list<Pickup>::iterator p = pickups_.begin(); p != pickups_.end(); p++) {
        p->paint(window);
    }

    mario_.paint(window);
    
    Sprite coin_sprite = Coin::sprites[0];
    paint_sprite(window, {cam.x - 12 + window.width() / 2, cam.y - window.height() / 2 + 2}, coin_sprite, false);

    TW_.write_text(window, {cam.x - 16 + window.width() / 2, cam.y - window.height() / 2 + 2}, std::to_string(mario_.get_coin_count()), 2, 2, {2,0});
    
    if (paused_) {
        pro2::paint_rect_fill_transparent(window, view_box, 0, 0.2);
        TW_.write_text(window, {cam.x, cam.y}, "PAUSED", 4,4, {1,1});
    }
}

void Game::spawn_coin(pro2::Pt pos, pro2::DoubPt vel) {
    coins_.add(new Coin{pos, vel, DoubPt{0,0}});
}