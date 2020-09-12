#ifndef BOARD_H
#define BOARD_H

#include "move.h"
#include <string>

class Board {
private:
    bool isSolved;
    int rows = 5, cols = 4;
    int winRow, winCol;
    std::vector<Block> blocks;
    std::vector<Move> moves;
    std::vector<std::vector<Block*>> spaces; 

    bool isValid(Block& b);
    void insertBlocks();
    void setMoves();
    void moveBlock(Block* b, const std::vector<Dir>& dirs);
    std::vector<Move> getBlockMoves(Block* b);
    std::vector<Dir> getBlockOpenDirs(const Block& b) const;
public:
    Board(std::vector<Block> blocks, int winRow_, int winCol_);
    Board(const Board& b, const Move& m);

    bool solved() const {return this->isSolved; }
    std::vector<Move> getMoves() const { return this->moves; }

    std::string hash() const;
    std::string nextHash(const Move& m);
    void print(std::ostream& os) const; 
};

std::ostream& operator<<(std::ostream& os, const Board& b);

#endif