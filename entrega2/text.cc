#include "text.hh"
#include <iostream>
#include <fstream>
#include <sstream> 
#include <map>

namespace pro2 {

    std::ifstream read_file(std::string fname) {
        return std::ifstream (fname);
    }
    
    Palette read_colors(std::ifstream &strm) {
        Palette colors;
        
        std::string name;
        int color;
        
        while (strm >> name >> std::hex >> color) {
            colors[name] = color;
        }
        
        return colors;
    }
    
    Font read_sprites(std::ifstream &strm) {
        int count;
        strm >> count;
        
        Font sprites(count);
        
        int h, w;
        strm >> h >> w;
        
        for (int c = 0; c < count; c++) {
            std::vector<std::vector<std::string>> sprite(h);
            for (int y = 0; y < h; y++) {
                std::vector<std::string> line(w);
                for (int x = 0; x < w; x++) {
                    strm >> line[x];
                }
                sprite[y] = line;
            }
            sprites[c] = sprite;
        }
        return sprites;
    }
    
    Charset read_charset(std::ifstream &strm) {
        char ch;
        int i = 0;
        
        Charset charset;

        while (strm.get(ch)) {
            charset[ch] = i;
            i++;
        }
        return charset;
    }
    
    Sprite color_sprite(const std::vector<std::vector<std::string>> &sprite, const Palette &colors) {
        std::vector<std::vector<int>> result;
        for (std::vector<std::vector<std::string>>::const_iterator it_y = sprite.begin(); it_y != sprite.end(); it_y++) {
            std::vector<int> line;
            for (std::vector<std::string>::const_iterator it_x = (*it_y).begin(); it_x != (*it_y).end(); it_x++) {
                Palette::const_iterator color = colors.find(*it_x);
                if (color != colors.end()) line.push_back(color->second);
                else line.push_back(-1);
            }
            result.push_back(line);
        }
        return result;
    }

    void paint_char(Window& window, Pt& orig, Sprite sprite, int& size) {
        for (int y = 0; y < sprite.size(); y++) {
            for (int i = 0; i < size; i++) {
                for (int x = 0; x < sprite[y].size(); x++) {
                    for (int j = 0; j < size; j++) {
                        if (sprite[y][x] > -1) window.set_pixel({orig.x + x*size + j, orig.y + y*size + i}, sprite[y][x]);
                    }
                }
            }
        }
    }

    TextWriter::TextWriter(Font font, std::string palette_path) {
        font_ = font; 
        std::ifstream strm = read_file(palette_path);
        palette_ = read_colors(strm);
    }
    TextWriter::TextWriter(std::string font_path, Palette palette) {
        palette_ = palette;
        std::ifstream strm = read_file(font_path);
        font_ = read_sprites(strm);
    }
    TextWriter::TextWriter(std::string font_path, std::string palette_path) {
        std::ifstream strm = read_file(font_path);
        font_ = read_sprites(strm);
        strm = read_file(palette_path);
        palette_ = read_colors(strm);
    }

    void TextWriter::set_font(std::string path) {
        std::ifstream strm = read_file(path);
        font_ = read_sprites(strm);
    }
            
    void TextWriter::set_palette(std::string path) {
        std::ifstream strm = read_file(path);
        palette_ = read_colors(strm);
    };

    void TextWriter::set_charset(std::string path) {
        std::ifstream strm = read_file(path);
        charset_ = read_charset(strm);
    }

    Sprite TextWriter::get_sprite(char ch) const{
        Charset::const_iterator it = charset_.find(ch);
        if (it == charset_.end()) {
            it--; // Null character
            std::cout << "NULL\n";
        }
        Font::const_iterator sp_it = font_.begin();
        for (int i = 0; i < it->second; i++) sp_it++;
        
        return color_sprite(*sp_it, palette_);
    }

    void TextWriter::write_text(Window& window, const Pt& orig, const std::string& text, int space_between_chars=1, int size=4) {
        Pt cursor = orig;

        int char_h = font_[0].size(), char_w = font_[0][0].size();
        
        char ch;
        std::istringstream strm(text);
        while (strm >> ch) {
            if (ch == '\n') {
                cursor.y += char_h*size + space_between_chars;
                cursor.x = orig.x;
            }
            else {
                paint_char(window, cursor, get_sprite(ch), size);
                cursor.x += char_w*size + space_between_chars;
            }
        }
    }
}