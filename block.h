#ifndef BLOCK_H
#define BLOCK_H

#include "dir.h"

class Block {
private:
    int row, col, numRows, numCols;
public:
    Block() : row(-1), col(-1), numRows(0), numCols(0) {}
    Block(int _row, int _col, int _numRows) : 
        row(_row), col(_col), numRows(_numRows), numCols(_numRows) {}
    Block(int _row, int _col, int _numRows, int _numCols) : 
        row(_row), col(_col), numRows(_numRows), numCols(_numCols) {}

    int getSize() const { return this->numRows*this->numCols; }
    int getRow() const { return this->row; }
    int getNumRows() const { return this->numRows; }
    int getCol() const { return this->col; }
    int getNumCols() const { return this->numCols; }
    
    inline void move(const Dir& d) {
        switch (d) {
            case Left: {
                this->col--;
                break;
            } case Right: {
                this->col++;
                break;
            } case Up: {
                this->row--;
                break;
            } case Down: {
                this->row++;
                break;
            } case None: {
                break;
            }
        }
    }

    inline void print(std::ostream& os) const { 
        std::string blockName;
        switch (this->numRows*this->numCols) {
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
        os << blockName << " at (" << this->row << "," << this->col << ")";
    }
};

inline std::ostream& operator<<(std::ostream& os, const Block& b) {
    b.print(os);
    return os;
}   

inline bool operator==(const Block& b1, const Block& b2) {
    return (b1.getRow() == b2.getRow() &&  
            b1.getCol() == b2.getCol() && 
            b1.getNumRows() == b2.getNumRows() &&
            b1.getNumCols() == b2.getNumCols());
}   

#endif