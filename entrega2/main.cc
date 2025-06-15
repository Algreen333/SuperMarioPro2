#include <vector>
#include "game.hh"
#include "window.hh"
#include "start_screen.hh"
#include "win_death_screen.hh"

using namespace std;

const int WIDTH = 480, HEIGHT = 320;
const int ZOOM = 2;
const int FPS = 48;

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