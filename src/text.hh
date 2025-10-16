#ifndef TEXT_HH
#define TEXT_HH

#include <iostream>
#include <fstream>
#include <map>
#include "utils.hh"
#include "window.hh"
#include "geometry.hh"


namespace pro2 {
    /**
     * @brief   Vector of characters, which each character being an array of strings.
     *          Each element of the array represents a pixel to be painted, and the string is mapped to the 
     *          color it should be painted into.
     */
    typedef std::vector<std::vector<std::vector<std::string>>> Font;

    /**
     * @brief   Map from the strings to the colors.
     */
    typedef std::map<std::string, int> Palette;
    /**
     * @brief   Map from the characters to the index of the corresponding sprite from the font.
     */
    typedef std::map<char, int> Charset;

    /**
     * @brief   Loads a text file as a `stream`.
     * 
     * @param fname File path.
     */
    std::ifstream read_file(std::string fname);
    
    /**
     * @brief   Generates a palette of colors from a text file.
     * 
     * @param stream `Stream` of the text file.
     */
    Palette read_colors(std::ifstream &stream);
    
    /**
     * @brief   Generates a `font` (vector of sprites of every character) from a text file.
     *          The font text files have the following structure:
     *          - On the first line, there are three integers with 'count' (number of sprites), 'height' and 'width' (of each sprites).
     *          - The next lines contain all of the sprites with the characters of the font.
     * 
     * @param stream `Stream` of the text file.
     */
    Font read_sprites(std::ifstream &stream);
    
    /**
     * @brief   Loads the charset (available characters and how they are ordered) of the font from a text file.
     * 
     * @param stream `Stream` of the text file.
     */
    Charset read_charset(std::ifstream &stream);

    /**
     * @brief   Paints the character of the font with a color palette.
     * 
     * @param sprite Sprite of the character with the templates of the color.
     * @param colors Color palette.
     */
    Sprite color_sprite(const std::vector<std::vector<std::string>> &sprite, const Palette &colors);
    

    /**
     * @brief   Draws onto the screen a character with a position and size.
     * 
     * @param window Window where to draw.
     * @param pos    Position where to draw.
     * @param sprite Sprite of the painted character.
     * @param size   Text size.
     */
    void paint_char(Window& window, Pt& pos, Sprite sprite, int& size);

    /**
     * @brief   Divides a multiline text (separated by '\n') into a vector of each line's string.
     * 
     * @param text Text to divide.
     */
    std::vector<std::string> split_lines(std::string text);

    /**
     * @class TextWriter
     * 
     * @brief It is used to store the font, color palette and the charsets, as well as drawing characters onto the screen.
     */
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
            
            /**
             * @brief   Returns the sprite of the character painted with the palette.
             *          If the character does not exist within the font, it returns a NULL character sprite (last character in the font).
             * 
             * @param ch Character
             */
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

            /**
             * @brief   Draws a string as text on the screen. Dibuixa un string com a text a la pantalla.
             * 
             * @param window    Window where to draw.
             * @param orig      Origin coordinates for the textbox (depends on alignment).
             * @param text      String with the text to draw.
             * @param space_between_chars Space that will be left between characters.
             * @param size      Tamany (gruix) del text
             * @param alignment Detemines how the text will be aligned: {x_align, y_align}.
             *      x_align and y_align can have the values [0,1,2], corresponding to [left/top, center, right/bottom] respectively.
             *      i.e. with the align {0,0}, the textbox will have at is orig the top left corner of the text.
             */
            void write_text(Window& window, const Pt& orig, const std::string& text, int space_between_chars=1, int size=4, Pt alignment={0,0});
        };
    }
#endif