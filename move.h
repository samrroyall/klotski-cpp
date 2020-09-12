#ifndef MOVE_H
#define MOVE_H 

#include "block.h"

class Move {
private:
    std::vector<Dir> dirs;
    Block block;
public:
    Move() : block(Block()), dirs{Dir::None} {}
    Move(Block block_, std::vector<Dir> dirs_) : block(block_), dirs(dirs_) {}

    std::vector<Dir> getDirs() const { return this->dirs; }
    Block getBlock() const { return this->block; }
};

inline std::ostream& operator<<(std::ostream& os, const Move& m) {
    os << "Move " << m.getBlock() << " ";
    std::vector<Dir> dirs = m.getDirs();
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