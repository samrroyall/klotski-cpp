// Klotski Solver in C++

#include "solver.h"

bool Solver::solve(Board b) {
    Solver::head = new MoveTree(b); // create MoveTree head
    Solver::queue.push(head); // push initial board to queue
    Solver::configs.emplace(Solver::head->getHash());
    while (!Solver::queue.empty()) {
        MoveTree* mt = Solver::queue.front(); // peek MoveTree from queue
        // if board is solved, check how many steps it took, update 
        if ((mt->getBoard()).solved()) { 
            Solver::winningTail = mt;
            return true;
        } 
        vector<Move> moves = (mt->getBoard()).getMoves(); // grab available moves for current board
        // push valid boards following from moves to queue
        for (int i = 0; i < moves.size(); i++) {
            Board newBoard = Board(
                mt->getBoard(), // previous board
                moves[i] // move
            );
            // ensure board configuration has not been seen on current branch
            //unordered_set<string> prevConfigs = mt->getConfigs();
            if (Solver::configs.find(newBoard.hash()) == Solver::configs.end()) { 
                MoveTree* newMT = new MoveTree(
                    newBoard, // new board
                    moves[i], // move
                    mt // parent 
                );
                Solver::configs.emplace(newMT->getHash());
                Solver::queue.push(newMT); // push new tree to queue
            }
        }
        Solver::queue.pop();
    }
    return false;
}

vector<Move> Solver::getMoves() {
    // ensure winningTail has been found
    if (!Solver::winningTail) {
        cout << "winningTail has not been found yet" << endl; // TO-DO: throw exception
        return vector<Move>();
    }
    int dist = Solver::winningTail->getDist();
    vector<Move> res = vector<Move>(dist);
    // taverse the tree from the winning tail to the head, storing the corresponding
    // moves into a vector
    MoveTree* mt = Solver::winningTail;
    for(mt; mt != Solver::head; mt = mt->getParent()) {
        res[mt->getDist() - 1] = mt->getMove();
    }
    return res;
}