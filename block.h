#ifndef BLOCK_H
#define BLOCK_H

#include "dir.h"

using namespace std;

class Block {
private:
    int row, col, numRows, numCols;
public:
    Block() : row(-1), col(-1), numRows(0), numCols(0) {}
    Block(int _row, int _col, int _numRows) : row(_row), col(_col), numRows(_numRows), numCols(_numRows) {}
    Block(int _row, int _col, int _numRows, int _numCols) : row(_row), col(_col), numRows(_numRows), numCols(_numCols) {}

    int getSize() { return numRows*numCols; }
    int getRow() { return row; }
    int getNumRows() { return numRows; }
    int getCol() { return col; }
    int getNumCols() { return numCols; }
    
    inline void move(Dir d) {
        switch (d) {
            case Left: {
                col--;
                break;
            } case Right: {
                col++;
                break;
            } case Up: {
                row--;
                break;
            } case Down: {
                row++;
                break;
            } case None: {
                break;
            }
        }
    }

    inline void print(ostream& os) { 
        string blockName;
        switch (this->getSize()) {
            case 1: {
                blockName = "OneBlock";
                break;
            } case 2: {
                if (this->numCols == 1) {
                    blockName = "Vertical TwoBlock";
                } else {
                    blockName = "Horizontal TwoBlock";
                }
                break;
            } case 4: {
                blockName = "FourBlock";
                break;
            } default: {
                blockName = "NoBlock";
                break;
            }
        }
        os << blockName << " at (" << this->getRow() << "," << this->getCol() << ")";
    }
};

inline ostream& operator<<(ostream& os, Block& b) {
    b.print(os);
    return os;
}   

inline bool operator==(Block& b1, Block& b2) {
    return (b1.getRow() == b2.getRow() &&  
            b1.getCol() == b2.getCol() && 
            b1.getNumRows() == b2.getNumRows() &&
            b1.getNumCols() == b2.getNumCols());
}   

#endif