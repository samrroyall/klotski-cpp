#include "solver.h"

int main() {
    // create block vector
    vector<Block> blocks = {
        // FourBlock
        Block(0,1,2),
        // TwoBlocks
        Block(0,0,2,1),
        Block(2,0,2,1),
        Block(0,3,2,1),
        Block(2,3,2,1),
        Block(2,1,1,2),
        // OneBlocks
        Block(3,1,1), 
        Block(3,2,1), 
        Block(4,0,1), 
        Block(4,3,1)
    };
    int winning_row = 3, winning_col = 1; // set winning coords
    Solver s = Solver(); // instantiate solver
    s.solve(Board(blocks, winning_row, winning_col)); // generate tree and find optimal path
    // vector<Move> optimalMoves = s.getMoves(); // get moves
    s.printMoves(); // print moves
}