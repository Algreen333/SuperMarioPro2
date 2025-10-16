#include <vector>
#include "game.hh"
#include "window.hh"
#include "start_screen.hh"

using namespace std;


const int WIDTH = 480, HEIGHT = 320;
const int ZOOM = 2;
const int FPS = 48;


/**
 * @brief Draws the death screen which lasts for 5 seconds or until the 'Escape' key is pressed.
 */
void death_screen(pro2::Window& window, pro2::TextWriter& tw) {
    int restart_counter = 150;
    window.set_camera_topleft({0,0});
    pro2::paint_rect_fill_transparent(window, {0,0,window.width(),window.height()}, 0x000000, 0.6);
    tw.write_text(window, {window.width()/2, window.height()/2}, "Game Over", 4, 4, {1,1});
    while (window.next_frame() and restart_counter > 0 and !window.was_key_pressed(pro2::Keys::Escape)) {
        restart_counter--;
    }
}

/**
 * @brief Draws the win screen which lasts for 5 seconds or until the 'Escape' key is pressed.
 */
void win_screen(pro2::Window& window, pro2::TextWriter& tw){
    int restart_counter = 150;
    window.set_camera_topleft({0,0});
    pro2::paint_rect_fill_transparent(window, {0,0,window.width(),window.height()}, 0x000000, 0.6);
    tw.write_text(window, {window.width()/2, window.height()/2}, "You won!", 4, 4, {1,1});
    while (window.next_frame() and restart_counter > 0 and !window.was_key_pressed(pro2::Keys::Escape)) {
        restart_counter--;
    }
}

int main() {
    pro2::Window window("Mario Pro 2", WIDTH, HEIGHT, ZOOM);
    pro2::TextWriter tw("assets/6x10rounded.txt","assets/colors.txt");
    tw.set_charset("assets/charset.txt");
    window.set_fps(FPS);

    StartScreen startscreen(WIDTH, HEIGHT, tw);
    Game game(WIDTH, HEIGHT, tw);

    while (startscreen.exit_code() != -1) {
        while (window.next_frame() && !startscreen.is_finished()) {
            startscreen.update(window);
            startscreen.paint(window);
        }
        if (startscreen.exit_code() == 1) {
            Game game(WIDTH, HEIGHT, tw);
            while (window.next_frame() && !game.is_finished()) {
                game.update(window);
                game.paint(window);
            }
            if (game.exit_code() == 1) death_screen(window, tw);
            else if (game.exit_code() == 2) win_screen(window, tw);
            startscreen.restart(window);
        }
    }
    return 0;
}