#include "board.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Constructor
Board::Board(vector<Block> blocks_, int winRow_, int winCol_) : blocks(blocks_), winRow(winRow_), winCol(winCol_) { 
    spaces = vector<vector<Block*>>(rows, vector<Block*>(cols, nullptr));
    insertBlocks(); 
}

// Clone Constructor
Board::Board(const Board& b, Move m) : blocks(b.blocks), winRow(b.winRow), winCol(b.winCol) {
    spaces = vector<vector<Block*>>(rows, vector<Block*>(cols, nullptr));
    insertBlocks();
    moveBlock(spaces[m.getBlock().getRow()][m.getBlock().getCol()], m.getDir());
}

void Board::insertBlocks() {
    for (int i = 0; i < blocks.size(); i++) {
        Block* b = &(blocks[i]);
        // ensure block only covers available spaces
        if (!isValid(b)) {
            cout << "There was an error regarding block positioning." << endl; // TO-DO: throw error
            return;
        }
        // set pointer to singular FourBlock
        if (b->getSize() == 4) {
            if (!fourBlock) { 
                fourBlock = b; 
            } else { 
                cout << "Two or more FourBlocks detected." << endl; // TO-DO: throw error 
                return;
            }
        }
    }
    // ensure FourBlock pointer is set
    if (!fourBlock) { 
        cout << "No FourBlocks detected." << endl; // TO-DO: throw error
        return;
    } 
}

bool Board::isValid(Block* b) {
    // handle out of bounds blocks
    int maxRow = b->getRow() + b->getNumRows() - 1, maxCol = b->getCol() + b->getNumCols() - 1; 
    if (b->getRow() < 0 || b->getCol() < 0 || maxRow > rows - 1 || maxCol > cols - 1) 
    {
        cout << "Block row or column is out of bounds." << endl; // TO-DO: THROW ERROR
        return false;
    }
    // check all spaces
    for (int row = b->getRow(); row < maxRow + 1; row++) {
        for (int col = b->getCol(); col < maxCol + 1; col++) {
            if (spaces[row][col]) return false;
            else spaces[row][col] = b;
        }
    }
    return true;
}

vector<Move> Board::getMoves(Block b) {
    vector<Move> moves;
    int maxRow = b.getRow() + b.getNumRows() - 1, maxCol = b.getCol() + b.getNumCols() - 1;
    bool l = true, r = true, u = true, d = true;
    // handle horizontal moves
    for (int row = b.getRow(); row < maxRow + 1; row++) {
        if (l && (b.getCol() == 0 || spaces[row][b.getCol()-1])) { l = false; }
        if (r && (maxCol + 1 >= cols || spaces[row][maxCol + 1])) { r = false; }
    }
    if (l) { moves.push_back( Move(b, Left) ); }
    if (r) { moves.push_back( Move(b, Right) ); }
    // handle vertical moves
    for (int col = b.getCol(); col < maxCol + 1; col++) {
        if (u && (b.getRow() == 0 || spaces[b.getRow()-1][col])) { u = false; }
        if (d && (maxRow + 1 >= rows || spaces[maxRow + 1][col])) { d = false; }
    }
    if (u) { moves.push_back( Move(b, Up) ); }
    if (d) { moves.push_back( Move(b, Down) ); }
    return moves;
}

vector<Move> Board::moves() {
    vector<Move> moves;
    for (Block b : blocks) {
        for (Move m : getMoves(b)) { 
            moves.push_back(m); 
            // check if there are any other moves for this block
            // after making this move
        }
    }
    return moves;
}

void Board::moveBlock(Block* b, Dir d) {
    for (int row = b->getRow(); row < b->getRow() + b->getNumRows(); row++) {
        for (int col = b->getCol(); col < b->getCol() + b->getNumCols(); col++) {
            switch (d) {
                case Left: {
                    spaces[row][col] = nullptr;
                    spaces[row][col-1] = b;
                    break;
                } case Right: {
                    if (col == b->getCol()) {
                        spaces[row][col] = nullptr;
                        spaces[row][col+1] = b;
                    } else {
                        spaces[row][col+1] = b;
                    }
                    break;
                } case Up: {
                    spaces[row][col] = nullptr;
                    spaces[row-1][col] = b;
                    break;
                } case Down: {
                    if (row == b->getRow()) {
                        spaces[row][col] = nullptr;
                        spaces[row+1][col] = b;
                    } else {
                        spaces[row+1][col] = b;
                    }
                    break;
                } case None: {
                    break;
                }
            }
        }
    }
    b->move(d);
}

string Board::hash() {
    string boardString;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Block* b = spaces[i][j];
            boardString += ((b) ? to_string(b->getSize()) : "0");
        }
    }
    return boardString;
}

bool Board::solved() {
    return fourBlock->getRow() == winRow && fourBlock->getCol() == winCol;
}

void Board::print(ostream& os) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Block* b = spaces[i][j];
            os << ((b) ? to_string(b->getSize()): "0");
        }
        os << endl;
    }
}

ostream& operator<<(ostream& os, Board& b) {
    b.print(os);
    return os;
}