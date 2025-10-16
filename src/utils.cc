#include "utils.hh"
#include <iostream>
using namespace std;

namespace pro2 {

double random_double(int min, int max, int precision) {
    int range = (max - min)*precision;
    int rand_int = (rand() % range);
    return (rand_int / precision) + min;
}

void paint_hline(Window& window, int xini, int xfin, int y, Color color) {
    for (int x = xini; x <= xfin; x++) {
        window.set_pixel({x, y}, color);
    }
}

void paint_vline(Window& window, int x, int yini, int yfin, Color color) {
    for (int y = yini; y <= yfin; y++) {
        window.set_pixel({x, y}, color);
    }
}

void paint_rect(Window& window, Rect rect, Color color, int brush_sz) {
    for (int i = 0; i < brush_sz; i++) {
        paint_hline(window, rect.left - (brush_sz/2), rect.right + (brush_sz/2), rect.top - (brush_sz/2) + i, color);
        paint_hline(window, rect.left - (brush_sz/2), rect.right + (brush_sz/2), rect.bottom - (brush_sz/2) + i, color);
        paint_vline(window, rect.left - (brush_sz/2) + i, rect.top, rect.bottom, color);
        paint_vline(window, rect.right - (brush_sz/2) + i, rect.top, rect.bottom, color);
    }
}

void paint_rect_fill(Window &window, Rect rect, Color color) {
    for (int y = rect.top; y <= rect.bottom; y++) {
        for (int x = rect.left; x <= rect.right; x++) {
            window.set_pixel({x, y}, color);
        }
    }
}

void paint_rect_fill_transparent(
    Window& window,
    Rect    rect,
    Color   color,
    double  transp
) {
    for (int y = rect.top; y <= rect.bottom; y++) {
        for (int x = rect.left; x <= rect.right; x++) {
            paint_pixel_transparent(window, {x,y}, color, transp);
        }
    } 
}

void paint_pixel_transparent(
    Window& window,
    Pt      pos,
    Color   color,
    double        transp
) {
    int prev_col = window.get_pixel({pos.x - window.topleft().x, pos.y - window.topleft().y});

    int b = (prev_col%256) * (1-transp) + (color%256) * transp;
    int g = ((prev_col / 256) % 256) * (1-transp) + ((color / 256) % 256) * transp;
    int r = ((prev_col / 65536) % 256) * (1-transp) + ((color / 65536) % 256) * transp;
    
    window.set_pixel(pos, r*65536 + g * 256 + b);
}

void paint_sprite(Window&           window,
                  Pt                orig,
                  const Sprite&     sprite,
                  bool              mirror) {
    for (int i = 0; i < sprite.size(); i++) {
        const vector<int>& line = sprite[i];
        for (int j = 0; j < line.size(); j++) {
            const int _j = mirror ? line.size() - j - 1 : j;
            if (line[_j] >= 0) {
                window.set_pixel({orig.x + j, orig.y + i}, line[_j]);
            }
        }
    }
}

}  // namespace pro2