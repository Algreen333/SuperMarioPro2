#ifndef BLOCK_HH
#define BLOCK_HH

#include <vector>
#include "window.hh"
#include "geometry.hh"
#include "utils.hh"


class Block {
 private:
    pro2::Pt pos_;

    int block_type_;

	static const std::vector<std::vector<int>> platform_texture_;

 public:
    Block(int type) : pos_({0,0}), block_type_(type) {}

    Block(const Block& other)
        : pos_(other.pos_), block_type_(other.block_type_) {}

    Block(int type, pro2::Pt pos)
        : pos_(pos), block_type_(type) {}
    
    void paint(pro2::Window& window, int anim_frame) const;

    pro2::Pt pos() const {return pos_;}

    /**
     * @brief Retorna el tipus de bloc que és
     * 
     * @returns
     *  - 0 si és un bloc de 'totxo'
     * 
     *  - 1 si és un bloc 'interrogant'
     * 
     *  - 2 si és un bloc 'activat'
    */    
    int block_type() const {return block_type_;}
    
    inline pro2::Rect get_rect() const {
        return {pos_.x, pos_.y, pos_.x + sz_w, pos_.y + sz_h};
    }

    /**
     * @brief Retorna la matriu del sprite del frame de l'animació corresponent
     */
    inline std::vector<std::vector<int>> get_sprite(int anim_frame) const {
        switch (block_type_)
        {
        case 0:
            return sprites[0];
        case 1: 
            return sprites[animation[anim_frame]];
        case 2:
            return sprites[1];
        default:
            return sprites[0];
        }
    }

    static const std::vector<std::vector<std::vector<int>>> sprites;
 private:
    static const int sz_h;
    static const int sz_w;

    static const std::vector<int> animation;
};


#endif