#ifndef BLOCK_HH
#define BLOCK_HH

#include <vector>
#include <iostream>
#include "window.hh"
#include "geometry.hh"
#include "utils.hh"


class Block {
 private:
    pro2::Pt pos_;

    int block_type_; // 0 si és tipus totxo, 1 interrogant, 2 activat
    int has_object_; // 1 si té una moneda, 2 si té un bolet

	static const std::vector<std::vector<int>> platform_texture_;

 public:
    Block(pro2::Pt pos = {0,0}, int type = 0, int has_object = 0) : pos_(pos), block_type_(type), has_object_(has_object) {}

    Block(const Block& other)
        : pos_(other.pos_), block_type_(other.block_type_) {}
    
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
        case 3:
            return sprites[5];
        default:
            return sprites[0];
        }
    }

    /**
     * @brief Retorna:
     * 
     * - 0 si no passa res
     * 
     * - 1 si s'ha de trencar el bloc
     * 
     * - 2 si s'ha de crear una moneda (sense trencar)
     * 
     * - 3 si s'ha de crear un bolet (sense trencar)
     */
    int check_bumped(int state) {
        if (block_type_ == 0) {
            if (has_object_ == 1 and state == 1) {
                block_type_ = 2;
                return 2;
            }
            else {
                if (state == 1) return 1;
                else {
                    return 0;
                } 
            }
        }
        else if (block_type_ == 1) {
            block_type_ = 2;
            if (has_object_ == 1) return 2;
            else if (has_object_ == 2) return 3;
            else return 0;
        }
        else return 0;
    }

    static const std::vector<std::vector<std::vector<int>>> sprites;
 private:
    static const int sz_h;
    static const int sz_w;

    static const std::vector<int> animation;
};


#endif