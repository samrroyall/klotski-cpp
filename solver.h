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
        hash = board.hash();
    }
    MoveTree(Board board_, Move move_, MoveTree* parent_) : 
        board(board_), move(move_), parent(parent_) 
    {
        headDist = parent->getDist() + 1;
        hash = board.hash();
    }

    Move getMove() { return move; }
    Board getBoard() { return board; }
    MoveTree* getParent() { return parent; }
    string getHash() { return hash; }
    int getDist() { return headDist; }
};


class Solver {
private:
    unordered_set<string> configs;
    queue<MoveTree*> queue;
    MoveTree* head;
    MoveTree* winningTail = nullptr;
public:
    Solver() {}
    void solve(Board b);
    vector<Move> getMoves();
    void printMoves();
};

#endif