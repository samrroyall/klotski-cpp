#ifndef MOVE_H
#define MOVE_H 

#include "block.h"
#include "dir.h"
#include <iostream>

using namespace std;

class Move {
private:
    Dir dir;
    Block block;
public:
    Move() : block(Block()), dir(None) {}
    Move(Block block_, Dir dir_) : block(block_), dir(dir_) {}

    Dir getDir() { return dir; }
    Block getBlock() { return block; }
};

inline ostream& operator<<(ostream& os, Move m) {
    return os << "Move " << m.getBlock() << " " << m.getDir();
}

#endif