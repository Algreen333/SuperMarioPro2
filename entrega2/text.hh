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
     * @brief Vector de caràcters. Els caràcters són matrius de strings. 
     *  Cada element de la matriu representa un pixel a pintar, i cada string 
     *  diferent està mapejada a la paleta amb el color que li correspon.
     */
    typedef std::vector<std::vector<std::vector<std::string>>> Font;

    /**
     * @brief Mapa de strings a colors
     */
    typedef std::map<std::string, int> Palette;
    /**
     * @brief Mapa de caràcters a l'índex de l'sprite de la font que li correspon
     */
    typedef std::map<char, int> Charset;

    /**
     * @brief Carrega un fitxer de text com a 'stream'
     * 
     * @param fname Nom del fitxer
     */
    std::ifstream read_file(std::string fname);
    
    /**
     * @brief Genera una paleta de colors a partir d'un fitxer de text
     * 
     * @param stream Stream del fitxer
     */
    Palette read_colors(std::ifstream &stream);
    
    /**
     * @brief Genera una font (vector de sprites de tots els caràcters) a partir d'un fitxer de text
     * Els fitxers de tipus font tenen la següent estructura:
     * A la primera línia hi ha 3 'int' amb 'count' (nombre de sprites), 'height' i 'width' (dels sprites)
     * A continuació hi ha tots els sprites amb els caràcters 
     * 
     * @param stream Stream del fitxer
     */
    Font read_sprites(std::ifstream &stream);
    
    /**
     * @brief Carrega el charset (els caràcters disponibles i l'ordre corresponent) de la font a partir d'un fitxer de text
     * 
     * @param stream Stream del fitxer
     */
    Charset read_charset(std::ifstream &stream);

    /**
     * @brief Pinta el caràcter de la font amb una paleta de colors
     * 
     * @param sprite Sprite del caràcter amb els templates del color
     * @param colors Paleta de colors
     */
    Sprite color_sprite(const std::vector<std::vector<std::string>> &sprite, const Palette &colors);
    

    /**
     * @brief Pinta a la pantalla un caràcter amb una posició i tamany
     * 
     * @param window Finestra a on dibuixar
     * @param pos    Posició a on dibuixar
     * @param sprite Sprite del caràcter pintat a dibuixar
     * @param size   Gruix amb el que es dibuixarà el caràcter
     */
    void paint_char(Window& window, Pt& pos, Sprite sprite, int& size);

    /**
     * @brief Separa un string multilínia (separades per '\n') en un vector de strings per cada línia
     * 
     * @param text Text a dividir
     */
    std::vector<std::string> split_lines(std::string text);

    /**
     * @class TextWriter
     * 
     * S'encarrega d'emmagatzemar la font, paleta i charset carregats i dibuixar text a la pantalla 
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
             * @brief Retorna el sprite del caràcter pintat amb la paleta. 
             * Si el caràcter no existeix a la font retorna un sprite amb el caràcter NULL (últim caràcter de la font)
             * 
             * @param ch Caràcter
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
             * @brief Dibuixa un string com a text a la pantalla
             * 
             * @param window Finestra a on dibuixar
             * @param orig   Coordenades d'origen del text (coordenada esquerre superior)
             * @param text   String amb el text a dibuixar
             * @param space_between_chars Espai que es deixarà entre caràcters
             * @param size   Tamany (gruix) del text
             * @param alignment Determina com estarà alineat el text: {x_align, y_align}
             *      x_align i y_align poden tenir valors [0,1,2] que equivalen [left/top, centre, right/bottom]. 
             *      Per exemple amb align {0,0}, tindrà a orig la cantonada esquerra superior del text
             */
            void write_text(Window& window, const Pt& orig, const std::string& text, int space_between_chars=1, int size=4, Pt alignment={0,0});
        };
    }
#endif