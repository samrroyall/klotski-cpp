// Klotski Solver in C++

#include "klotski.h"
#include <iostream>
#include <vector>

void Klotski::solve(Board b) {
    Klotski::head = new MoveTree(b); // create MoveTree head
    Klotski::queue.push(head); // push initial board to queue
    Klotski::configs.emplace(Klotski::head->getHash());
    while (!Klotski::queue.empty()) {
        MoveTree* mt = Klotski::queue.front(); // peek MoveTree from queue
        // if board is solved, check how many steps it took, update 
        if (mt->getBoard().solved()) { 
            Klotski::winningTail = mt;
            return;
        } 
        vector<Move> moves = mt->getBoard().moves(); // grab available moves for current board
        // push valid boards following from moves to queue
        for (int i = 0; i < moves.size(); i++) {
            Board newBoard = Board(
                mt->getBoard(), // previous board
                moves[i] // move
            );
            // ensure board configuration has not been seen on current branch
            //unordered_set<string> prevConfigs = mt->getConfigs();
            if (Klotski::configs.find(newBoard.hash()) == Klotski::configs.end()) { 
                MoveTree* newMT = new MoveTree(
                    newBoard, // new board
                    moves[i], // move
                    mt // parent 
                );
                Klotski::configs.emplace(newMT->getHash());
                Klotski::queue.push(newMT); // push new tree to queue
            }
        }
        Klotski::queue.pop();
    }
}

vector<Move> Klotski::printMoves() {
    // ensure winningTail has been found
    if (!Klotski::winningTail) {
        cout << "winningTail has not been found yet" << endl; // TO-DO: throw exception
        return vector<Move>();
    }
    int dist = Klotski::winningTail->getDist();
    cout << "Optimal path contains " << dist << " moves!" << endl;
    vector<Move> res = vector<Move>(dist);
    MoveTree* mt = Klotski::winningTail;
    // taverse the tree from the winning tail to the head, storing the corresponding
    // moves into a vector
    while (mt != Klotski::head) {
        res[mt->getDist() - 1] = mt->getMove();
        mt = mt->getParent();
    }
    return res;
}

int main() {
    int winning_row = 3, winning_col = 1;
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
    Klotski k = Klotski();
    k.solve(Board(blocks, winning_row, winning_col));
    vector<Move> optimalMoves = k.printMoves();
    for (int i = 0; i < optimalMoves.size(); i++) {
        cout << i+1 << ". " << optimalMoves[i] << endl;
    }
}