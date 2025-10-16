#ifndef UTILS_HH
#define UTILS_HH

#include <vector>
#include <cstdlib>          // For RNG
#include "geometry.hh"
#include "window.hh"

namespace pro2 {

typedef std::vector<std::vector<int>> Sprite;
    
/**
 * @brief   Returns a `double` between `min` and `max` with n digits of precision.
 * 
 * @param min       Minimum value.
 * @param max       Maximum value.
 * @param precision Integer equal to 10^n (n digits of preceision).
 */
double random_double(int min, int max, int precision);

/**
 * @brief   Draws a horizontal line onto the screen.
 *
 * @param window    Window where to draw.
 * @param xini      Initial x coordinate.
 * @param xfin      Final x coordinate.
 * @param y         Y coordinate.
 * @param color     Line color (by default it is set to `white`).
 */
void paint_hline(Window& window, int xini, int xfin, int y, Color color = white);

/**
 * @brief   Draws a vertical line onto the screen.
 *
 * @param window    Window where to draw.
 * @param x         X coordinate.
 * @param yini      Initial y coordinate.
 * @param yfin      Final y coordinate.
 * @param color     Line color (by default it is set to `white`).
 */
void paint_vline(Window& window, int x, int yini, int yfin, Color color = white);

/**
 * @brief   Draws a `pro2::Rect` rectangle.
 * 
 * @param window    Window where to draw.
 * @param rect      `pro2::Rect` to draw.
 * @param color     Line color.
 * @param brush_sz  Line width.
 */
void paint_rect(
    Window& window,
    Rect    rect,
    Color   color,
    int     brush_sz
);

/**
 * @brief   Draws and fills a `pro2::Rect` rectangle.
 * 
 * @param window    Window where to draw.
 * @param rect      `pro2::Rect` to draw.
 * @param color     Color of the rectangle.
 */
void paint_rect_fill(
    Window& window,
    Rect    rect,
    Color   color
);

/**
 * @brief   Draws Dibuixa i emplena un rectangle 'Rect' amb transparència
 * 
 * @param window    Window where to draw.
 * @param rect      `pro2::Rect` to draw.
 * @param color     Color of the rectangle.
 * @param transp    Transparency (from 0 for opaque to 1 for totally transparent)
 */
void paint_rect_fill_transparent(
    Window& window,
    Rect    rect,
    Color   color,
    double  transp
);

/**
 * @brief   Paints a pixel with a color and transparency.
 * 
 * @param window    Window where to draw.
 * @param pos       `pro2::Pt` with the position of the pixel.
 * @param color     Color.
 * @param transp    Transparency (from 0 for opaque to 1 for totally transparent)
 */
void paint_pixel_transparent(
    Window& window,
    Pt      pos,
    Color   color,
    double  transp
);

/**
 * @brief   Draws a sprite onto the screen.
 *
 * @param window    Window where to draw.
 * @param orig      `pro2::Pt` with the upper left corner of the sprite.
 * @param sprite    `pro2::Sprite` to draw.
 * @param mirror    True/False to mirror the sprite.
 */
void paint_sprite(Window&           window,
                  Pt                orig,
                  const Sprite&     sprite,
                  bool              mirror);
}

// namespace pro2

#endif