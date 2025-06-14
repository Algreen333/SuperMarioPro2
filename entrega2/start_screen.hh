#ifndef START_SCREEN_HH
#define START_SCREEN_HH

#include <vector>
#include <string>
#include "geometry.hh"
#include "window.hh"
#include "text.hh"
#include "utils.hh"


class Button {
    private:
        pro2::Rect rect;
        std::string text;
        int bg_normal, text_normal, bg_selected, text_selected;
    public:
        Button(
            pro2::Rect rect, 
            std::string text, 
            int bg_normal=0xCD612E, 
            int text_normal=0xF9DECA, 
            int bg_selected=0xC97A55, 
            int text_selected=0xF9DECA
        ) : rect(rect), text(text), bg_normal(bg_normal), text_normal(text_normal), bg_selected(bg_selected), text_selected(text_selected) {};

        pro2::Rect get_rect() const {return rect;}
        
        bool selected(pro2::Pt pos) const {return (pos.x >= rect.left and pos.x <= rect.right and pos.y >= rect.top and pos.y <= rect.bottom);}

        void paint(pro2::Window& window, pro2::TextWriter& writer) const;
};

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
        
        int exit_code() const {return exit_code_;}

        void restart(pro2::Window& window);
    
    private:
        static constexpr int sky_blue = 0x5c94fc;
};


#endif