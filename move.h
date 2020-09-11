#ifndef MOVE_H
#define MOVE_H 

#include "block.h"

using namespace std;

class Move {
private:
    vector<Dir> dirs;
    Block block;
public:
    Move() : block(Block()), dirs{None} {}
    Move(Block block_, vector<Dir> dirs_) : block(block_), dirs(dirs_) {}

    vector<Dir> getDirs() { return dirs; }
    Block getBlock() { return block; }
};

inline ostream& operator<<(ostream& os, Move m) {
    os << "Move " << m.getBlock() << " ";
    vector<Dir> dirs = m.getDirs();
    for (int i = 0; i < dirs.size(); i++) { 
        if (i < dirs.size() - 1) {
            os << dirs[i] << ", "; 
        } else {
            os << dirs[i];
        }
    }
    return os;
}

#endif