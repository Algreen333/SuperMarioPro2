#ifndef START_SCREEN_HH
#define START_SCREEN_HH

#include <vector>
#include <string>
#include "geometry.hh"
#include "window.hh"
#include "text.hh"
#include "utils.hh"


/**
 * @brief Classe que implementa botons i la seva funcionalitat.
 * 
 *      Els botons poden ser clicats i quan el ratolí passa per sobre d'ells, poden canviar de color de fons (bg_normal/bg_selected)
 */
class Button {
    private:
        pro2::Rect rect;
        std::string text;
        int bg_normal, bg_selected;
    public:
        Button(
            pro2::Rect rect, 
            std::string text, 
            int bg_normal=0xCD612E, 
            int bg_selected=0xC97A55
        ) : rect(rect), text(text), bg_normal(bg_normal), bg_selected(bg_selected) {};

        pro2::Rect get_rect() const {return rect;}
        
        /**
         * @brief Retorna si el punter del ratolí és a sobre del botó
         */
        bool selected(pro2::Pt pos) const {return (pos.x >= rect.left and pos.x <= rect.right and pos.y >= rect.top and pos.y <= rect.bottom);}

        void paint(pro2::Window& window, pro2::TextWriter& writer) const;
};


/**
 * @brief Aquesta classe s'encarrega de dibuixar el menú principal i gestionar la interacció de l'usuari
 *        
 *      Disposa de dos botons, un per iniciar el joc i l'altra per sortir.
 *      Quan el mario mor, guanya o quan es prem la tecla "Escape" dins del joc, es retorna al menú principal.
 */
class StartScreen {
    private:
        std::vector< Button > buttons;
        pro2::TextWriter TW_;
        
        // Flags
        bool finished_ = false;
        int exit_code_ = 0;

        int height_;
        int width_;

    public:
        StartScreen(int width, int height, pro2::TextWriter TW);

        inline bool is_finished() const {return finished_;}

        void process_keys(pro2::Window& window);

        void update(pro2::Window& window);

        void paint(pro2::Window& window);
        
        /**
         * @brief Retorna 1 si s'ha pres el botó d'iniciar el joc i -1 altrament
         */
        int exit_code() const {return exit_code_;}

        /**
         * @brief Restableix els valors per defecte
         */
        void restart(pro2::Window& window);
    
    private:
        static constexpr int sky_blue = 0x5c94fc;
};


#endif