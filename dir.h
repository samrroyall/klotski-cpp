#ifndef DIR_H
#define DIR_H

#include <iostream>
#include <vector>

enum Dir {Left, Right, Up, Down, None};

inline Dir oppositeDir(const Dir& d) {
    Dir oppDir = None;
    switch (d) {
        case Left: {
            oppDir = Right;
            break;
        } case Right: {
            oppDir = Left;
            break;
        } case Up: {
            oppDir = Down;
            break;
        } case Down: {
            oppDir = Up;
            break;
        } case None: {
            oppDir = None;
            break;
        } default: {
            oppDir = None;
            break;
        }
    }
    return oppDir;
}

inline std::vector<Dir> oppositeDirs(const std::vector<Dir>& dirs) {
    std::vector<Dir> oppDirs(dirs.size());
    for (int i = 0; i < dirs.size(); i++) {
        oppDirs[dirs.size()-1-i] = oppositeDir(dirs[i]);
    }
    return oppDirs;
}

inline std::ostream& operator<<(std::ostream& os, const Dir& dir) {
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