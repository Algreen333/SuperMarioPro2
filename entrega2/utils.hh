#ifndef UTILS_HH
#define UTILS_HH

#include <vector>
#include <cstdlib>          // Per als valors aleatoris
#include "geometry.hh"
#include "window.hh"

namespace pro2 {

typedef std::vector<std::vector<int>> Sprite;
    
/**
 * @brief Retorna un double entre (min, max), amb una precisó de n digits
 * 
 * @param min       Valor mínim
 * @param max       Valor màxim
 * @param precision Int de la forma 10^n
 */
double random_double(int min, int max, int precision);

/**
 * @brief Dibuja una línea horizontal en la ventana.
 *
 * @param window Ventana en la que se dibuja la línea.
 * @param xini Coordenada x inicial.
 * @param xfin Coordenada x final.
 * @param y Coordenada y.
 * @param color Color de la línea (opcional, si no se pone se asume `white`).
 */
void paint_hline(Window& window, int xini, int xfin, int y, Color color = white);

/**
 * @brief Dibuja una línea vertical en la ventana.
 *
 * @param window Ventana en la que se dibuja la línea.
 * @param x Coordenada x.
 * @param yini Coordenada y inicial.
 * @param yfin Coordenada y final.
 * @param color Color de la línea (opcional, si no se pone se asume `white`).
 */
void paint_vline(Window& window, int x, int yini, int yfin, Color color = white);

/**
 * @brief Dibuixa un rectangle 'Rect'.
 * 
 * @param window    Finestra a la que pintar
 * @param rect      Rectangle a pintar
 * @param color     Color de les línies
 * @param brush_sz  Gruix de les línies
 */
void paint_rect(
    Window& window,
    Rect    rect,
    Color   color,
    int     brush_sz
);

/**
 * @brief Dibuixa i emplena un rectangle 'Rect'
 * 
 * @param window    Finestra a la que pintar
 * @param rect      Rectangle a dibuixar
 * @param color     Color del rectangle
 */
void paint_rect_fill(
    Window& window,
    Rect    rect,
    Color   color
);

/**
 * @brief Dibuixa i emplena un rectangle 'Rect' amb transparència
 * 
 * @param window    Finestra a la que pintar
 * @param rect      Rectangle a dibuixar
 * @param color     Color del rectangle
 * @param transp    Transparència (del 0 al 1) 
 */
void paint_rect_fill_transparent(
    Window& window,
    Rect    rect,
    Color   color,
    double  transp
);

/**
 * @brief Pinta un pixel amb color i transparència.
 * 
 * @param window    Finestra a la que pintar
 * @param pos       Posició del pixel
 * @param color     Color
 * @param transp    Transparència (del 0 al 1)
 *                  Amb transp=0 el rectangle és totalment opac, amb transp=1 totalment transparent (invisible)
 */
void paint_pixel_transparent(
    Window& window,
    Pt      pos,
    Color   color,
    double  transp
);

/**
 * @brief Dibuixa una imatge/textura a la finestra a partir d'una posició
 *
 * @param window    Finestra a la que pintar
 * @param orig      Origen (cantonada de dalt a l'esquerra) del rectangle que forma el _sprite_
 * @param sprite    Matriu de colors que representa la imatge (_sprite_).
 * @param mirror    Si cal pintar girar la textura horitzontalment
 */
void paint_sprite(Window&           window,
                  Pt                orig,
                  const Sprite&     sprite,
                  bool              mirror);
}

// namespace pro2

#endif