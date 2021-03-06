#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>
#include "tile.h"


// This class stores a grid of Tile pointers, which are NULL if the
// grid location does not (yet) contain a tile

class Board {
public:

  // CONSTRUCTOR
  // takes in the dimensions (height & width) of the board
  Board(int i, int j);

  // ACCESSORS
  int numRows() const { return board.size(); } 
  int numColumns() const { return board[0].size(); }
  Tile* getTile(int i, int j) const;

  // MODIFIERS
  void setTile(int i, int j, Tile* t);

  // FOR PRINTING
  void Print() const;

  //I realize that setting variables to public is usually a very bad idea,
  //But in my code I constantly manipulate these values in such a way that function
  //calls would have actually been more complicated
  int hMin, hMax, wMin, wMax;
private:

  // REPRESENTATION

  std::vector<std::vector<Tile*> > board;
};


#endif
/*
                      _                   _
                     / \                 / \
                    / _ \               / _ \
                   / /:| |             | |:\ \
                  | |..| |             | |..| |
                  | |..| |             | |..| |
                  | |..| |             | |..| |
                  | |..| |             | |..| |
                  | |..| |             | |..| |
                  |  \. /_______________\ ./  |
                   \ ________       ________ /
                    /|#######\_____/#######|\
                   / |########|   |########| \
                  (  |########| _ |########|  )
                   /  \######/ | | \######/  \
                  |            | |            |
                  |            | |            |
                  |        \__/   \__/        |
                  |                           |                   ,--.
                  |       ::::     ::::       |                   I  I
                   \       ___________       /                    I##I
                    |     (___________)     |                     I##I
                    |     (__|  |  |__)     |                     I  I
                    |        |  |  |        |                     I##I
                     \_      |__|__|      _/                      I  I
                       \_               _/                        I  I
                         \_           _/                          I  I_
                           \_________/                           /I /  )
                   ______,-_/      \_-.______                   / I/  /
                 _/#####|#| `--__--' |#|#####\_                /  /  /
                /#######|#|   /__\   |#|#######\              |  /  /
               /########|#|  /(__)\  |#|########\            /\    / I
              /#########|#|\/ /XX\ \/|#|#########\          /##\  /  I
             /##########|#|  |XXXX|  |#|##########\        /####\/I  I
            /###########|#|  |XXXX|  |#|###########\      /######\I  I
           |#######/#####\#\ |XXXX| /#/#####\#######\    /######/ `--'
           |######|#######|#||XXXX||#|#######\#######\  /######/
           |######|#######|#||XXXX||#|########\#######\/######/
           |######|#######|#||XXXX||#|########|\#############/
           |######|########\#\XXXX/#/#########| \###########/
           |######|#########\#\XX/#/##########|  \#########/
           |######|##########\#\/#/###########|    \#####/
           |######|###########\/#/############|
           |######|###########|#|#############|
           |######|###########|#|#############|   

       +---------------------------------------------------------------+
       |***************************************************************|
       |****************    _ **********   ********    _ **************|
       |************** .'|=| `. ****** .'| ****** .'|=| `. ************|
       |************ .'  | | .' **** .'  | **** .'  | | .' ************|
       |************ |   |=|'. ***** |   | **** |   |=|'. *************|
       |************ |   | |  | **** |   | **** |   | |  | ************|
       |************ |___|=|_.' **** |___| **** |___|=|_.' ************|
       |***************************************************************|
       |***************************************************************|
       |***  _                                    _           _    ****|
       |*** |_) | | |\ | |\ | \_/     |  |\ |    |_) |   /\  /  |/ ****|
       |*** |_) |_| | \| | \|  |      |  | \|    |_) |_ /--\ \_ |\ ****|
       |***                                                        ****|
       |***************************************************************|
       |***************************************************************|
       +---------------------------------------------------------------+

*/
