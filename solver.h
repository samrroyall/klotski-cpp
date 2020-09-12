#ifndef SOLVER_H
#define SOLVER_H

#include "board.h"
#include <unordered_set>
#include <queue>

class MoveTree {
private:
    Board board;
    Move move;
    MoveTree* parent;
    int headDist;
public:
    MoveTree(Board& board_) : 
        board(board_), move(Move()), parent(nullptr), headDist(0) {}
    MoveTree(Board& board_, const Move& move_, MoveTree* parent_) : 
        board(board_), move(move_), parent(parent_) 
    {
        headDist = (this->parent)->getDist() + 1;
    }

    Board& getBoard() { return this->board; }
    const Move& getMove() const { return this->move; }
    MoveTree* getParent() const { return this->parent; }
    std::string getHash() const { return (this->board).hash(); }
    int getDist() const { return this->headDist; }
};


class Solver {
private:
    MoveTree* head = nullptr;
    MoveTree* winningTail = nullptr;
public:
    Solver() {}

    int getDist() const { return (this->winningTail) ? this->winningTail->getDist() : -1 ;}

    bool solve(Board b);
    std::vector<Move> getMoves();
};

#endif