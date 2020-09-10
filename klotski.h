#ifndef KLOTSKI_H
#define KLOTSKI_H

#include "board.h"
#include <iostream>
#include <unordered_set>
#include <vector>
#include <queue>

using namespace std;

class MoveTree {
private:
    Board board;
    Move move;
    MoveTree* parent;
    //unordered_set<string> boardConfigs;
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
        //boardConfigs = parent->getConfigs();
        //boardConfigs.emplace(parent->getHash());
        headDist = parent->getDist() + 1;
        hash = board.hash();
    }

    Move getMove() { return move; }
    Board getBoard() { return board; }
    MoveTree* getParent() { return parent; }
    //unordered_set<string> getConfigs() { return boardConfigs; }
    string getHash() { return hash; }
    int getDist() { return headDist; }
};


class Klotski {
private:
    //Stack* stack;
    unordered_set<string> configs;
    queue<MoveTree*> queue;
    MoveTree* head;
    MoveTree* winningTail = nullptr;
public:
    Klotski() {}
    void solve(Board b);
    vector<Move> printMoves();
};

#endif