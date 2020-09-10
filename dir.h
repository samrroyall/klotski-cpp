#ifndef DIR_H
#define DIR_H

#include <iostream>

using namespace std;

enum Dir {Left, Right, Up, Down, None};

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
            os << "None";
            break;
        }
    } 
    return os;
}

#endif