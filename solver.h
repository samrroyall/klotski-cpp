#ifndef SOLVER_H
#define SOLVER_H

#include "board.h"
#include <unordered_set>
#include <queue>

using namespace std;

class MoveTree {
private:
    Board board;
    Move move;
    MoveTree* parent;
    string hash;
    int headDist;
public:
    MoveTree(Board board_) : 
        board(board_), move(Move()), parent(nullptr), headDist(0)
    {
        hash = (this->board).hash();
    }
    MoveTree(Board board_, Move move_, MoveTree* parent_) : 
        board(board_), move(move_), parent(parent_) 
    {
        headDist = (this->parent)->getDist() + 1;
        hash = (this->board).hash();
    }

    Move getMove() { return this->move; }
    Board getBoard() { return this->board; }
    MoveTree* getParent() { return this->parent; }
    string getHash() { return this->hash; }
    int getDist() { return this->headDist; }
};


class Solver {
private:
    MoveTree* head = nullptr;
    MoveTree* winningTail = nullptr;
public:
    Solver() {}

    int getDist() { return (this->winningTail) ? this->winningTail->getDist() : -1 ;}

    bool solve(Board b);
    vector<Move> getMoves();
};

#endif