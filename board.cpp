#include "board.h"
#include <stack>

// Constructor
Board::Board(vector<Block> blocks_, int winRow_, int winCol_) : blocks(blocks_), winRow(winRow_), winCol(winCol_) { 
    spaces = vector<vector<Block*>>(rows, vector<Block*>(cols, nullptr));
    insertBlocks(); 
}

// Clone Constructor
Board::Board(const Board& b, Move m) : blocks(b.blocks), winRow(b.winRow), winCol(b.winCol) {
    spaces = vector<vector<Block*>>(rows, vector<Block*>(cols, nullptr));
    insertBlocks();
    moveBlock(spaces[m.getBlock().getRow()][m.getBlock().getCol()], m.getDirs());
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

vector<Dir> Board::getOpenDirs(Block b) {
    vector<Dir> dirs;
    int maxRow = b.getRow() + b.getNumRows() - 1, maxCol = b.getCol() + b.getNumCols() - 1;
    bool l = true, r = true, u = true, d = true;
    // handle horizontal moves
    for (int row = b.getRow(); row < maxRow + 1; row++) {
        if (l && (b.getCol() == 0 || spaces[row][b.getCol()-1])) { l = false; }
        if (r && (maxCol + 1 >= cols || spaces[row][maxCol + 1])) { r = false; }
    }
    if (l) { dirs.push_back(Left); }
    if (r) { dirs.push_back(Right); }
    // handle vertical moves
    for (int col = b.getCol(); col < maxCol + 1; col++) {
        if (u && (b.getRow() == 0 || spaces[b.getRow()-1][col])) { u = false; }
        if (d && (maxRow + 1 >= rows || spaces[maxRow + 1][col])) { d = false; }
    }
    if (u) { dirs.push_back(Up); }
    if (d) { dirs.push_back(Down); }
    return dirs;
}

vector<Move> Board::getMoves(Block* b) {
    vector<Move> moves; // initialize result vector
    vector<Dir> openDirs = getOpenDirs(*b); // get moves of distance 1
    for (int i = 0; i < openDirs.size(); i++) {
        stack<vector<Dir>> stack;
        stack.push({openDirs[i]});
        while (!stack.empty()) {
            vector<Dir> currDirs = stack.top(); // peek stack
            stack.pop(); // pop stack
            moves.push_back(Move(*b, {currDirs}));  // push move to result vector
            moveBlock(b, currDirs); // move block

            vector<Dir> nextOpenDirs = getOpenDirs(*b); // get next level of moves
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

vector<Move> Board::moves() {
    vector<Move> moves;
    for (int i = 0; i < blocks.size(); i++) {
        for (Move m : getMoves(&(blocks[i]))) { 
            moves.push_back(m); 
        }
    }
    return moves;
}

void Board::moveBlock(Block* b, vector<Dir> dirs) {
    for (int i = 0; i < dirs.size(); i++) {
        for (int row = b->getRow(); row < b->getRow() + b->getNumRows(); row++) {
            for (int col = b->getCol(); col < b->getCol() + b->getNumCols(); col++) {
                switch (dirs[i]) {
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
        b->move(dirs[i]);
    }
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