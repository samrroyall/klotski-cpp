#ifndef BOARD_H
#define BOARD_H

#include "move.h"
#include <iostream> 
#include <vector> 

class Board {
private:
    int rows = 5, cols = 4;
    int winRow, winCol;
    Block* fourBlock = nullptr;
    vector<Block> blocks;
    vector<vector<Block*>> spaces; 

    bool isValid(Block* b);
    vector<Move> getMoves(Block b);
    void insertBlocks();
    void moveBlock(Block* b, Dir d);
public:
    Board(vector<Block> blocks, int winRow_, int winCol_);
    Board(const Board& b, Move m);

    bool solved();
    string hash();
    vector<Move> moves();
    void print(ostream& os); 
};

ostream& operator<<(ostream& os, Board& b);

#endif