#ifndef DIR_H
#define DIR_H

#include <iostream>
#include <vector>

using namespace std;

enum Dir {Left, Right, Up, Down, None};

inline Dir oppositeDir(Dir d) {
    switch (d) {
        case Left: {
            return Right;
        } case Right: {
            return Left;
        } case Up: {
            return Down;
        } case Down: {
            return Up;
        } case None: {
            return None;
        } default: {
            return None;
        }
    }
}

inline vector<Dir> oppositeDirs(vector<Dir> dirs) {
    vector<Dir> oppDirs(dirs.size());
    for (int i = 0; i < dirs.size(); i++) {
        oppDirs[dirs.size()-1-i] = oppositeDir(dirs[i]);
    }
    return oppDirs;
}

inline ostream& operator<<(ostream& os, const Dir& dir) {
    switch (dir) {
        case Left: {
            os << "Left";
            break;
        } case Right: {
            os << "Right";
            break;
        } case Up: {
            os << "Up";
            break;
        } case Down: {
            os << "Down";
            break;
        } case None: {
            os << "Nowhere";
            break;
        }
    } 
    return os;
}

#endif