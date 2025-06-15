#include "win_death_screen.hh"
#include "utils.hh"

void death_screen(pro2::Window& window, pro2::TextWriter& tw) {
    int restart_counter = 150;
    window.set_camera_topleft({0,0});
    while (window.next_frame() and restart_counter > 0) {
        window.clear(0x000000);
        tw.write_text(window, {window.width()/2, window.height()/2}, "You died", 4, 4, {1,1});
        restart_counter--;
    }
}

void win_screen(pro2::Window& window, pro2::TextWriter& tw){
    int restart_counter = 150;
    window.set_camera_topleft({0,0});
    pro2::paint_rect_fill_transparent(window, {0,0,window.width(),window.height()}, 0x000000, 0.6);
    tw.write_text(window, {window.width()/2, window.height()/2}, "You won!", 4, 4, {1,1});
    while (window.next_frame() and restart_counter > 0) {
        restart_counter--;
    }
}