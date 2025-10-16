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
    
    platforms_.add(new Platform{-12, 691, 170, 500});

    blocks_.add(new Block{pro2::Pt{200, 107}, 1, 1});

    blocks_.add(new Block{pro2::Pt{264, 107}, 0});
    blocks_.add(new Block{pro2::Pt{280, 107}, 1, 1});
    blocks_.add(new Block{pro2::Pt{296, 107}, 0, 1});
    blocks_.add(new Block{pro2::Pt{312, 107}, 1, 1});
    blocks_.add(new Block{pro2::Pt{328, 107}, 0});
    
    blocks_.add(new Block{pro2::Pt{296, 43}, 1, 2});
    
    blocks_.add(new Block{pro2::Pt{388, 139}, 3});
    blocks_.add(new Block{pro2::Pt{404, 139}, 3});
    blocks_.add(new Block{pro2::Pt{388, 155}, 3});
    blocks_.add(new Block{pro2::Pt{404, 155}, 3});

    interactables_.emplace_back(pro2::Pt{430, 155}, 3);
    for (int i = 0; i < 8; i++) {
        coins_.add(new Coin{pro2::Pt{427 + 16*i, 170}});
    }

    blocks_.add(new Block{pro2::Pt{548, 123}, 3});
    blocks_.add(new Block{pro2::Pt{564, 123}, 3});
    blocks_.add(new Block{pro2::Pt{548, 139}, 3});
    blocks_.add(new Block{pro2::Pt{564, 139}, 3});
    blocks_.add(new Block{pro2::Pt{548, 155}, 3});
    blocks_.add(new Block{pro2::Pt{564, 155}, 3});
    
    platforms_.add(new Platform{740, 2000, 170, 500});

    blocks_.add(new Block{pro2::Pt{820, 155}, 3});
    interactables_.emplace_back(pro2::Pt{840, 155}, 3);
    for (int i = 0; i < 11; i++) {
        coins_.add(new Coin{pro2::Pt{843 + 16*i, -16}, {0,0}, {0,0}});
    }
    blocks_.add(new Block{pro2::Pt{1012, 155}, 3});

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j <= i; j++) {
            blocks_.add(new Block{pro2::Pt{1200 + 16*i, 155 - 16*j}, 3});
            if (j == i) coins_.add(new Coin {pro2::Pt{1207 + 16*i, 123 - 16*j}});
        }
    }

    interactables_.emplace_back(pro2::Pt{1444, 3}, 2);
}

void Game::process_keys(pro2::Window& window) {
    if (window.is_key_down(Keys::Escape)) {
        finished_ = true;
    }

    if (window.was_key_pressed('P')) {
        paused_ = not paused_;
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

    mario_.update(window, platforms_, blocks_, interactables_);
    
    // Mira que el mario no s'hagi sortit dels límits
    pro2::Pt pos = mario_.pos();
    if (pos.x < death_barrier_.left or pos.x > death_barrier_.right or pos.y < death_barrier_.top or pos.y > death_barrier_.bottom) {
        finished_ = true;
        exit_code_ = 1;
    }


    for (Coin * c : coins_.query(processing_box)) {
        c->update(window, close_platforms);
        if (!c->is_grounded()) {
            coins_.update(c);
        }
    }

    std::list<Interactable>::iterator p = interactables_.begin();
    while (p != interactables_.end()) {
        bool res = p->update(window, platforms_, blocks_);
        // Comprova si ha agafat un bolet
        if (p->type() == 1 and check_collision(mario_.collision_box(), p->collision_box())) {
            p = interactables_.erase(p);
            mario_.set_state(1);
        }
        // Comprova si ha tocat un goomba i com l'ha tocat;
        else if (p->type() == 3 and check_collision(mario_.collision_box(), p->collision_box())) {
            if (mario_.collision_box().bottom <= p->collision_box().top + 8) {
                spawn_coin(p->pos(), {0,-10});
                p = interactables_.erase(p);
                mario_.set_grounded(true);
                mario_.jump();
            }
            else {
                if (mario_.get_state() == 1) {
                    mario_.set_state(0);
                }
                else if (mario_.get_state() == 0) {
                    finished_ = true;
                    exit_code_ = 1;
                }
                p++;
            }
        }
        // Comprova si ha trencat un bloc
        else if (res) {
            p = interactables_.erase(p);
        }
        // Comprova si ha tocat la bandera
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

    for (std::list<Interactable>::iterator p = interactables_.begin(); p != interactables_.end(); p++) {
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