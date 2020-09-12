// Klotski Solver in C++

#include "solver.h"

bool Solver::solve(Board b) {
    Solver::head = new MoveTree(b); // create MoveTree head
    queue<MoveTree*> queue; // initialize queue
    queue.push(head); // push initial board to queue
    unordered_set<string> configs; // initialize board configs set
    configs.emplace(Solver::head->getHash());
    while (!queue.empty()) {
        MoveTree* mt = queue.front(); // peek MoveTree from queue
        // if board is solved, check distance to head, update accordingly
        if ((mt->getBoard()).solved()) { 
            Solver::winningTail = mt;
            return true;
        } 
        vector<Move> moves = (mt->getBoard()).getMoves(); // grab available moves for current board
        // push valid boards following from moves to queue
        int validChildren = 0;
        for (int i = 0; i < moves.size(); i++) {
            string nextHash = (mt->getBoard()).nextHash(moves[i]); // get hash of next move
            // ensure board configuration has not been seen
            if (configs.find(nextHash) == configs.end()) { 
                // create new tree from board created by current move
                Board newBoard = Board(
                    mt->getBoard(), // previous board
                    moves[i] // move
                );
                MoveTree* newMT = new MoveTree(
                    newBoard, // new board
                    moves[i], // move
                    mt // parent 
                );
                configs.emplace(nextHash); // add new board configuration hash to configs 
                queue.push(newMT); // push new tree to queue
                validChildren++;
            }
        }
        if (!validChildren) { delete mt; } // delete unsolved leaves
        queue.pop();
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