#ifndef TEXT_HH
#define TEXT_HH

#include <iostream>
#include <fstream>
#include <map>
#include "utils.hh"
#include "window.hh"
#include "geometry.hh"


namespace pro2 {  
    typedef std::vector<std::vector<std::vector<std::string>>> Font;
    typedef std::map<std::string, int> Palette;
    typedef std::map<char, int> Charset;

    std::ifstream read_file(std::string fname);
    
    Palette read_colors(std::ifstream &stream);
    
    Font read_sprites(std::ifstream &stream);
    
    Charset read_charset(std::ifstream &stream);

    Sprite color_sprite(const std::vector<std::vector<std::string>> &sprite, const std::map<std::string,int> &colors);
    
    void paint_char(Window& window, Pt& pos, Sprite sprite, int& size);

    class TextWriter {
        private:
            Font font_;
            Palette palette_;
            Charset charset_;

        public:
            TextWriter(Font font, Palette palette) : font_(font), palette_(palette) {};
            TextWriter(Font font, std::string palette_path);
            TextWriter(std::string font_path, Palette palette);
            TextWriter(std::string font_path, std::string palette_path);
            
            Sprite get_sprite(char ch) const;

            void set_font(Font font) {font_ = font;}
            void set_font(std::string path);
            const Font get_font() {return font_;};
            
            void set_palette(Palette palette) {palette_ = palette;}
            void set_palette(std::string path);
            const Palette get_palette() {return palette_;};

            void set_charset(Charset charset) {charset_ = charset;}
            void set_charset(std::string path);
            const Charset get_charset() {return charset_;};

            void write_text(Window& window, const Pt& orig, const std::string& text, int space_between_chars, int size);
    };

    #endif
}