#include "board.h"
#include <stack>

// Constructor
Board::Board(vector<Block> blocks_, int winRow_, int winCol_) : blocks(blocks_), winRow(winRow_), winCol(winCol_) { 
    this->spaces = vector<vector<Block*>>(rows, vector<Block*>(cols, nullptr));
    this->insertBlocks(); 
    Block* bp = this->spaces[this->winRow][this->winCol];
    this->isSolved = (bp && 
                      bp->getSize() == 4 && 
                      bp->getRow() == this->winRow && 
                      bp->getCol() == this->winCol);
    this->setMoves();
}

// Clone Constructor
Board::Board(const Board& b, Move m) : blocks(b.blocks), winRow(b.winRow), winCol(b.winCol) {
    this->spaces = vector<vector<Block*>>(rows, vector<Block*>(cols, nullptr));
    this->insertBlocks();
    moveBlock(this->spaces[(m.getBlock()).getRow()][(m.getBlock()).getCol()], m.getDirs());
    Block* bp = this->spaces[this->winRow][this->winCol];
    this->isSolved = (bp && 
                      bp->getSize() == 4 && 
                      bp->getRow() == this->winRow && 
                      bp->getCol() == this->winCol);
    this->setMoves();
}

void Board::insertBlocks() {
    int numFourBlocks = 0;
    for (int i = 0; i < this->blocks.size(); i++) {
        Block* b = &(this->blocks[i]);
        // ensure block only covers available spaces
        if (!isValid(b)) {
            cout << "There was an error regarding block positioning." << endl; // TO-DO: throw error
            return;
        }
        // set pointer to singular FourBlock
        if (b->getSize() == 4) {
            if (numFourBlocks != 0) { 
                cout << "Two or more FourBlocks detected." << endl; // TO-DO: throw error
                return;
            } else { 
                numFourBlocks++; 
            }
        }
    }
    // ensure FourBlock pointer is set
    if (numFourBlocks == 0) { 
        cout << "No FourBlocks detected." << endl; // TO-DO: throw error
        return;
    } 
}

bool Board::isValid(Block* b) {
    // handle out of bounds blocks
    int maxRow = b->getRow() + b->getNumRows() - 1, maxCol = b->getCol() + b->getNumCols() - 1; 
    if (b->getRow() < 0 || b->getCol() < 0 || maxRow > this->rows - 1 || maxCol > this->cols - 1) 
    {
        cout << "Block row or column is out of bounds." << endl; // TO-DO: THROW ERROR
        return false;
    }
    // check all spaces
    for (int row = b->getRow(); row < maxRow + 1; row++) {
        for (int col = b->getCol(); col < maxCol + 1; col++) {
            if (this->spaces[row][col]) return false;
            else this->spaces[row][col] = b;
        }
    }
    return true;
}

vector<Dir> Board::getBlockOpenDirs(Block b) {
    vector<Dir> dirs;
    int maxRow = b.getRow() + b.getNumRows() - 1, maxCol = b.getCol() + b.getNumCols() - 1;
    bool l = true, r = true, u = true, d = true;
    // handle horizontal moves
    for (int row = b.getRow(); row < maxRow + 1; row++) {
        if (l && (b.getCol() == 0 || this->spaces[row][b.getCol()-1])) { l = false; }
        if (r && (maxCol + 1 >= this->cols || this->spaces[row][maxCol + 1])) { r = false; }
    }
    if (l) { dirs.push_back(Left); }
    if (r) { dirs.push_back(Right); }
    // handle vertical moves
    for (int col = b.getCol(); col < maxCol + 1; col++) {
        if (u && (b.getRow() == 0 || this->spaces[b.getRow()-1][col])) { u = false; }
        if (d && (maxRow + 1 >= this->rows || this->spaces[maxRow + 1][col])) { d = false; }
    }
    if (u) { dirs.push_back(Up); }
    if (d) { dirs.push_back(Down); }
    return dirs;
}

vector<Move> Board::getBlockMoves(Block* b) {
    vector<Move> moves; // initialize result vector
    vector<Dir> openDirs = getBlockOpenDirs(*b); // get moves of distance 1
    for (int i = 0; i < openDirs.size(); i++) {
        stack<vector<Dir>> stack;
        stack.push({openDirs[i]});
        while (!stack.empty()) {
            vector<Dir> currDirs = stack.top(); // peek stack
            stack.pop(); // pop stack
            moves.push_back(Move(*b, {currDirs}));  // push move to result vector
            moveBlock(b, currDirs); // move block

            vector<Dir> nextOpenDirs = getBlockOpenDirs(*b); // get next level of moves
            for (int j = 0; j < nextOpenDirs.size(); j++) { 
                // if next dir is not a move backward, push new
                // sequence of dirs to stack
                if (nextOpenDirs[j] != oppositeDir(currDirs[currDirs.size()-1])) { 
                    vector<Dir> nextDirs{currDirs};
                    nextDirs.push_back(nextOpenDirs[j]);
                    stack.push(nextDirs); 
                }
            }

            moveBlock(b, oppositeDirs(currDirs)); // unmove block
        }
    }
    return moves;
}

void Board::setMoves() {
    if (!(this->isSolved)) {
        for (int i = 0; i < this->blocks.size(); i++) {
            for (Move m : getBlockMoves(&(this->blocks[i]))) { 
                this->moves.push_back(m); 
            }
        }
    }
}

void Board::moveBlock(Block* b, vector<Dir> dirs) {
    for (int i = 0; i < dirs.size(); i++) {
        for (int row = b->getRow(); row < b->getRow() + b->getNumRows(); row++) {
            for (int col = b->getCol(); col < b->getCol() + b->getNumCols(); col++) {
                switch (dirs[i]) {
                    case Left: {
                        this->spaces[row][col] = nullptr;
                        this->spaces[row][col-1] = b;
                        break;
                    } case Right: {
                        if (col == b->getCol()) {
                            this->spaces[row][col] = nullptr;
                            this->spaces[row][col+1] = b;
                        } else {
                            this->spaces[row][col+1] = b;
                        }
                        break;
                    } case Up: {
                        this->spaces[row][col] = nullptr;
                        this->spaces[row-1][col] = b;
                        break;
                    } case Down: {
                        if (row == b->getRow()) {
                            this->spaces[row][col] = nullptr;
                            this->spaces[row+1][col] = b;
                        } else {
                            this->spaces[row+1][col] = b;
                        }
                        break;
                    } case None: {
                        break;
                    }
                }
            }
        }
        b->move(dirs[i]);
    }
}

string Board::hash() {
    string boardString;
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            Block* b = this->spaces[i][j];
            boardString += ((b) ? to_string(b->getSize()) : "0");
        }
    }
    return boardString;
}

void Board::print(ostream& os) {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            Block* b = this->spaces[i][j];
            os << ((b) ? to_string(b->getSize()): "0");
        }
        os << endl;
    }
}

ostream& operator<<(ostream& os, Board& b) {
    b.print(os);
    return os;
}