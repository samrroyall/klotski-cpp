#ifndef BOARD_H
#define BOARD_H

#include "move.h"
#include <string>

using namespace std;

class Board {
private:
    bool isSolved;
    int rows = 5, cols = 4;
    int winRow, winCol;
    vector<Block> blocks;
    vector<Move> moves;
    vector<vector<Block*>> spaces; 

    bool isValid(Block* b);
    void insertBlocks();
    vector<Move> getBlockMoves(Block* b);
    vector<Dir> getBlockOpenDirs(Block b);
    void setMoves();
    void moveBlock(Block* b, vector<Dir> dirs);
public:
    Board(vector<Block> blocks, int winRow_, int winCol_);
    Board(const Board& b, Move m);

    bool solved() {return this->isSolved; }
    vector<Move> getMoves() { return this->moves; }

    string hash();
    string nextHash(Move m);
    void print(ostream& os); 
};

ostream& operator<<(ostream& os, Board& b);

#endif