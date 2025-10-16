#ifndef START_SCREEN_HH
#define START_SCREEN_HH

#include <vector>
#include <string>
#include "geometry.hh"
#include "window.hh"
#include "text.hh"
#include "utils.hh"


/**
 * @brief   Class which implements buttons and their functionality
 *          The buttons can be clicked, and when the cursor goes over them the background color can be changed (bg_normal/bg_selected)
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
         * @brief Returns true if the button is being hovered.
         */
        bool selected(pro2::Pt pos) const {return (pos.x >= rect.left and pos.x <= rect.right and pos.y >= rect.top and pos.y <= rect.bottom);}

        void paint(pro2::Window& window, pro2::TextWriter& writer) const;
};


/**
 * @brief   This class is used to draw the Start Screen and handle the user interactions.
 *      
 *          The Start Screen has two buttons, one to play and the other to quit.
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
         * @brief   Returns 1 if the 'play' button has been pressed and -1 if the 'quit' button has been pressed.
         */
        int exit_code() const {return exit_code_;}

        /**
         * @brief Resets the class to its default values.
         */
        void restart(pro2::Window& window);
    
    private:
        static constexpr int sky_blue = 0x5c94fc;
};


#endif