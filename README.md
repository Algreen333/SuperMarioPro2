# SuperMarioPro2

This is a project for a 1st year university subject. We were given a simple recreation of the original Super Mario Bros game. Our task was to add new classes and functionalities to the game.

## Build instructions
The source files of the game are in the directory `src`. The game can be built with the `Makefile`:
```bash
make MODE=release
```
To clean the files after the compilation run:
```bash
make clean
```

## Documentation
The documentation of the code (automatically generated with Doxygen) can be found in ``docs``. It can be viewed as an html or as a pdf generated with latex. There already is a compiled pdf.

## The new classes

Two main classes have been added: 'Block' and 'Interactable'.

### class Block
The 'Block' class adds new blocks from the original SMB, such as the question mark block. The player can interact with the blocks by jumping into them from below.

### class Interactable
The 'Interactable' class adds a variety of objects which interact with the player. It adds: coins that are created from activating blocks, the mushrooms and 'goombas' from the original SMB, as well as the finish flag.

Some of these objects appear when interacting with blocks and others are already spawned with the level.

## Additional modifications
A main menu has been added, which can be accessed by pressing the ``Escape`` key, when Mario dies or by touching the finish flag.

Many more modifications have been made to the original code given and a new level has been created which recreates the original SMB's 1-1 level.

***

Having explained these new classes and modifications, there is one other new feature I want to highlight.

## New module: `text.hh`

This module allows for drawing text onto the screen using already made font bitmaps.
The fonts are loaded from text files, with a list of arrays of strings, which represent each character's 'sprite'. Then, the spritescan be painted with a color palette (a dictionary that maps strings to colors) and finally draw them.

There are two fonts that have already been converted to the correct formats:
- ``assets/6x6rounded.txt``  
- ``assets/6x10rounded.txt`` (The one used in the game).

There is also an already made color palette and the charset (list of characters in the same order in which they appear in the font file).

For the correct exectuion of the game, the folder `assets` should be in the same directory as the executable, as the files are read each time the game runs.

The tools and python scripts i made to convert the images of the font bitmaps into the text fonts automatically have are also available in `additional_tools`.

## Demonstration video
Finally, I have also included a demonstration video, ``video_demo.mov``, showing the how the game works and showcasing all of the new features I have added.