#include "block.hh"


const int _ = -1;
const int b = 0x8E500E;
const int k = 0x000000;
const int y = 0xD8A22E;
const int o = 0x8C540E;
const int d = 0x421D03;
const int w = 0xF5D0C6;

const int Block::sz_w = 16;
const int Block::sz_h = 16;

// clang-format off
const std::vector<std::vector<std::vector<int>>> Block::sprites = {
    {
        {b,b,b,b,b,b,b,k,b,b,b,b,b,b,b,k},
        {b,b,b,b,b,b,b,k,b,b,b,b,b,b,b,k},
        {b,b,b,b,b,b,b,k,b,b,b,b,b,b,b,k},
        {k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k},
        {b,b,b,k,b,b,b,b,b,b,b,k,b,b,b,b},
        {b,b,b,k,b,b,b,b,b,b,b,k,b,b,b,b},
        {b,b,b,k,b,b,b,b,b,b,b,k,b,b,b,b},
        {k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k},
        {b,b,b,b,b,b,b,k,b,b,b,b,b,b,b,k},
        {b,b,b,b,b,b,b,k,b,b,b,b,b,b,b,k},
        {b,b,b,b,b,b,b,k,b,b,b,b,b,b,b,k},
        {k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k},
        {b,b,b,k,b,b,b,b,b,b,b,k,b,b,b,b},
        {b,b,b,k,b,b,b,b,b,b,b,k,b,b,b,b},
        {b,b,b,k,b,b,b,b,b,b,b,k,b,b,b,b},
        {k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k},
    },
    {
        {_,k,k,k,k,k,k,k,k,k,k,k,k,k,k,_},
        {k,b,b,b,b,b,b,b,b,b,b,b,b,b,b,k},
        {k,b,k,b,b,b,b,b,b,b,b,b,b,k,b,k},
        {k,b,b,b,b,b,b,b,b,b,b,b,b,b,b,k},
        {k,b,b,b,b,b,b,b,b,b,b,b,b,b,b,k},
        {k,b,b,b,b,b,b,b,b,b,b,b,b,b,b,k},
        {k,b,b,b,b,b,b,b,b,b,b,b,b,b,b,k},
        {k,b,b,b,b,b,b,b,b,b,b,b,b,b,b,k},
        {k,b,b,b,b,b,b,b,b,b,b,b,b,b,b,k},
        {k,b,b,b,b,b,b,b,b,b,b,b,b,b,b,k},
        {k,b,b,b,b,b,b,b,b,b,b,b,b,b,b,k},
        {k,b,b,b,b,b,b,b,b,b,b,b,b,b,b,k},
        {k,b,b,b,b,b,b,b,b,b,b,b,b,b,b,k},
        {k,b,k,b,b,b,b,b,b,b,b,b,b,k,b,k},
        {k,b,b,b,b,b,b,b,b,b,b,b,b,b,b,k},
        {_,k,k,k,k,k,k,k,k,k,k,k,k,k,k,_},
    },
    {
        {_,b,b,b,b,b,b,b,b,b,b,b,b,b,b,_},
        {b,y,y,y,y,y,y,y,y,y,y,y,y,y,y,k},
        {b,y,k,y,y,y,y,y,y,y,y,y,y,k,y,k},
        {b,y,y,y,y,b,b,b,b,b,y,y,y,y,y,k},
        {b,y,y,y,b,b,k,k,k,b,b,y,y,y,y,k},
        {b,y,y,y,b,b,k,y,y,b,b,k,y,y,y,k},
        {b,y,y,y,b,b,k,y,y,b,b,k,y,y,y,k},
        {b,y,y,y,y,k,k,y,b,b,b,k,y,y,y,k},
        {b,y,y,y,y,y,y,b,b,k,k,k,y,y,y,k},
        {b,y,y,y,y,y,y,b,b,k,y,y,y,y,y,k},
        {b,y,y,y,y,y,y,y,k,k,y,y,y,y,y,k},
        {b,y,y,y,y,y,y,b,b,y,y,y,y,y,y,k},
        {b,y,y,y,y,y,y,b,b,y,y,y,y,y,y,k},
        {b,y,k,y,y,y,y,y,k,k,y,y,y,k,y,k},
        {b,y,y,y,y,y,y,y,y,y,y,y,y,y,y,k},
        {k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k}
    },
    {
        {_,b,b,b,b,b,b,b,b,b,b,b,b,b,b,_},
        {b,o,o,o,o,o,o,o,o,o,o,o,o,o,o,k},
        {b,o,k,o,o,o,o,o,o,o,o,o,o,k,o,k},
        {b,o,o,o,o,b,b,b,b,b,o,o,o,o,o,k},
        {b,o,o,o,b,b,k,k,k,b,b,o,o,o,o,k},
        {b,o,o,o,b,b,k,o,o,b,b,k,o,o,o,k},
        {b,o,o,o,b,b,k,o,o,b,b,k,o,o,o,k},
        {b,o,o,o,o,k,k,o,b,b,b,k,o,o,o,k},
        {b,o,o,o,o,o,o,b,b,k,k,k,o,o,o,k},
        {b,o,o,o,o,o,o,b,b,k,o,o,o,o,o,k},
        {b,o,o,o,o,o,o,o,k,k,o,o,o,o,o,k},
        {b,o,o,o,o,o,o,b,b,o,o,o,o,o,o,k},
        {b,o,o,o,o,o,o,b,b,o,o,o,o,o,o,k},
        {b,o,k,o,o,o,o,o,k,k,o,o,o,k,o,k},
        {b,o,o,o,o,o,o,o,o,o,o,o,o,o,o,k},
        {k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k}
    },
    {
        {_,b,b,b,b,b,b,b,b,b,b,b,b,b,b,_},
        {b,d,d,d,d,d,d,d,d,d,d,d,d,d,d,k},
        {b,d,k,d,d,d,d,d,d,d,d,d,d,k,d,k},
        {b,d,d,d,d,b,b,b,b,b,d,d,d,d,d,k},
        {b,d,d,d,b,b,k,k,k,b,b,d,d,d,d,k},
        {b,d,d,d,b,b,k,d,d,b,b,k,d,d,d,k},
        {b,d,d,d,b,b,k,d,d,b,b,k,d,d,d,k},
        {b,d,d,d,d,k,k,d,b,b,b,k,d,d,d,k},
        {b,d,d,d,d,d,d,b,b,k,k,k,d,d,d,k},
        {b,d,d,d,d,d,d,b,b,k,d,d,d,d,d,k},
        {b,d,d,d,d,d,d,d,k,k,d,d,d,d,d,k},
        {b,d,d,d,d,d,d,b,b,d,d,d,d,d,d,k},
        {b,d,d,d,d,d,d,b,b,d,d,d,d,d,d,k},
        {b,d,k,d,d,d,d,d,k,k,d,d,d,k,d,k},
        {b,d,d,d,d,d,d,d,d,d,d,d,d,d,d,k},
        {k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k}
    },
    {
        {b,w,w,w,w,w,w,w,w,w,w,w,w,w,w,k},
        {w,b,w,w,w,w,w,w,w,w,w,w,w,w,k,k},
        {w,w,b,w,w,w,w,w,w,w,w,w,w,k,k,k},
        {w,w,w,b,w,w,w,w,w,w,w,w,k,k,k,k},
        {w,w,w,w,b,b,b,b,b,b,b,b,k,k,k,k},
        {w,w,w,w,b,b,b,b,b,b,b,b,k,k,k,k},
        {w,w,w,w,b,b,b,b,b,b,b,b,k,k,k,k},
        {w,w,w,w,b,b,b,b,b,b,b,b,k,k,k,k},
        {w,w,w,w,b,b,b,b,b,b,b,b,k,k,k,k},
        {w,w,w,w,b,b,b,b,b,b,b,b,k,k,k,k},
        {w,w,w,w,b,b,b,b,b,b,b,b,k,k,k,k},
        {w,w,w,w,b,b,b,b,b,b,b,b,k,k,k,k},
        {w,w,w,k,k,k,k,k,k,k,k,k,b,k,k,k},
        {w,w,k,k,k,k,k,k,k,k,k,k,k,b,k,k},
        {w,k,k,k,k,k,k,k,k,k,k,k,k,k,b,k},
        {k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,b},
    }
};
// clang-format on

const std::vector<int> Block::animation {
    2,2,2,2,2,2,
    3,3,3,3,3,3,
    4,4,4,4,4,4
};

void Block::paint(pro2::Window& window, int anim_frame) const {
    pro2::paint_sprite(window, pos_, get_sprite(anim_frame), false);
}
