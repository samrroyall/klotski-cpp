// Klotski Solver in C++

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Block {
protected:
    Block(int row, int col, int s) : topLeft{row, col}, size(s) {}
public:
    const int size;
    int topLeft[2];

    void move(char dir) {
        switch (dir) {
            case 'L':
                topLeft[1]--; // decrement current column
            case 'R':
                topLeft[1]++; // increment current column
            case 'U':
                topLeft[0]--; // decrement current row
            case 'D':
                topLeft[0]++; // increment current row
            default:
                return;
        }
        return;
    }

    vector<char> virtual getMoves(vector<vector<bool>> spaces, int numRows, int numCols) {
        int row = topLeft[0], col = topLeft[1];
        vector<char> moves;
        // handle horizontal moves
        bool l = true, r = true;
        for (int r = row; r < r + sqrt(size); r++) {
            if (col == 0 || !spaces[r][col-1]) l = false; // left
            if (col == numCols - 1 || !spaces[r][col+1]) r = false; // right
        }
        if (l) moves.push_back('L');
        if (r) moves.push_back('R');
        // handle vertical moves
        bool u = true, d = true;
        for (int c = col; c < c + sqrt(size); c++) {
            if (row == 0 || !spaces[row-1][c]) u = false; // up
            if (row == numRows - 1 || !spaces[row+1][c]) d = false; // down
        }
        if (u) moves.push_back('U');
        if (d) moves.push_back('D');

        return moves;
    }
};

 // overloading < operator in order to use the Block class in maps
 inline bool operator<(const Block& b1, const Block& b2) {
     return b1.size < b2.size;
 }

class OneBlock : public Block {
public:
    OneBlock(int row, int col) : Block{row, col, 1} {}
};


class TwoBlock : public Block {
public:
    bool horizontal;
    TwoBlock(int row, int col, bool h) : Block{row, col, 2}, horizontal(h) {}

    vector<char> getMoves(vector<vector<bool>> spaces, int numRows, int numCols) {
        vector<char> moves;
        int row = topLeft[0], col = topLeft[1];
        // handle moves for horizontal TwoBlock
        if (horizontal) {
            // handle horizontal moves
            if (col > 0 && spaces[row][col-1]) moves.push_back('L'); // left
            if (col < numCols - 1 && spaces[row][col+1]) moves.push_back('R'); // right
            // handle vertical moves
            bool u = true, d = true;
            for (int c = col; c < c + size; c++) {
                if (row == 0 || !spaces[row-1][c]) u = false; // up
                if (row == numRows - 1 || !spaces[row+1][c]) d = false; // down
            }
            if (u) moves.push_back('U');
            if (d) moves.push_back('D');
        // handle moves for vertical TwoBlock
        } else {
            // handle vertical moves
            if (row > 0 && spaces[row-1][col]) moves.push_back('U'); // up
            if (row < numRows - 1 && spaces[row+1][col]) moves.push_back('D'); // down
            // handle horizontal moves
            bool l = true, r = true;
            for (int r = row; r < r + size; r++) {
                if (col == 0 || !spaces[r][col-1]) l = false; // left
                if (col == numCols - 1 || !spaces[r][col+1]) r = false; // right
            }
            if (l) moves.push_back('L');
            if (r) moves.push_back('R');
        }
        return moves;
    }
};


class FourBlock : public Block {
public:
    FourBlock(int row, int col) : Block{row, col, 4} {}
};


class Board {
private:
    const int rows = 5, cols = 4;
    const int numBlocks, winning_row, winning_col;
    Block* fourBlock = nullptr;
    Block** blocks;
    vector<vector<bool>> spaces;
public:
    Board(Block** b, int n, int wr, int wc) : 
        blocks{b}, numBlocks(n), winning_row(wr), winning_col(wc)
    { 
        // initialize a board with all available spaces
        vector<vector<bool>> s(rows, vector<bool>(cols, true));
        spaces = s;
        // insert blocks into board
        insertBlocks();
    }

    void insertBlocks() {
        for (int i = 0; i < numBlocks; i++) {
            Block* b = blocks[i];
            // ensure block covers all valid spaces
            if (!isValid(b)) {
                // TO-DO: throw error
                cout << "There was an error regarding block positioning." << endl;
            }
            // set pointer to singular FourBlock
            if (!fourBlock && dynamic_cast<FourBlock*>(b)) {
                fourBlock = b;
            } else if (fourBlock && dynamic_cast<FourBlock*>(b)) {
                // TO-DO: throw error
                cout << "Two or more FourBlocks detected." << endl;
            }
        }
        // ensure FourBlock pointer is set
        if (!fourBlock) {
            // TO-DO: throw error
            cout << "No FourBlocks detected." << endl;
        }
    }

    bool isValid(Block* b) {
        int row = b->topLeft[0], col = b->topLeft[1], size = b->size;
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            // TO-DO: THROW ERROR
            return false;
        }
        // handle blocks of size 2
        if (TwoBlock* tb = dynamic_cast<TwoBlock*>(b)) {
            // check top/left space
            if (!spaces[row][col]) return false;
            else spaces[row][col] = false;
            // check right space
            if (tb->horizontal) {
                if (!spaces[row][col+1]) return false;
                else spaces[row][col+1] = false;
            // check bottom space
            } else {
                if (!spaces[row+1][col]) return false;
                else spaces[row+1][col] = false;
            }
        // handle all other blocks 
        } else {
            // check all spaces
            for (row; row < row + sqrt(size); row++) {
                for (col; col < col + sqrt(size); col++) {
                    if (!spaces[row][col]) return false;
                    else spaces[row][col] = false;
                }
            }
        }
        return true;
    }

    map<Block, vector<char>> currentMoves() {
        map<Block, vector<char>> moves;
        for (int i = 0; i < numBlocks; i++) {
            Block* b = blocks[i];
            moves[*b] = b->getMoves(spaces, rows, cols);
        }
        return moves;
    }

    bool isSolved() {
        return  fourBlock->topLeft[0] == winning_row && fourBlock->topLeft[1] == winning_col;
    }
};

class Klotski {
public:
    Board* board;
    Klotski(Board* b) : board(b) {}
};

int main() {
    return 0;
}