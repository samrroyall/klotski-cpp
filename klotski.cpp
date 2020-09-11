#include "solver.h"
#include <iostream>
#include <fstream>

vector<int> getInts(string s) {
    vector<int> res;
    string::iterator it = s.begin();
    while (*it == ' ' && it != s.end()) { it++; } // handle leading spaces
    while (it != s.end()) {
        string chars;
        while (*it != ' ' && it != s.end()) { chars += *(it++); };
        res.push_back(stoi(chars));
        while (*it == ' ' && it != s.end()) { it++; } // handle trailing spacesk
    }
    return res;
}

int main() {
    // get block configuration from 'blocks.txt'
    vector<Block> blocks;
    int winning_row = -1, winning_col = -1;
    fstream blockFile;
    blockFile.open("blocks.txt", ios::in);
    if (blockFile.is_open()) {
        string line;
        while (getline(blockFile, line)) {
            vector<int> vals = getInts(line);
            switch (vals.size()) {
                case 2: {
                    winning_row = vals[0];
                    winning_col = vals[1];
                    break;
                } case 3: {
                    blocks.push_back(Block(vals[0], vals[1], vals[2]));
                    break;
                } case 4: {
                    blocks.push_back(Block(vals[0], vals[1], vals[2], vals[3]));
                    break;
                } default: {
                    cout << "error in 'blocks.txt'" << endl; // TO-DO: throw error
                    return 0;
                }
            }
        }
        if (winning_col == -1 || winning_col == -1) {
            cout << "'blocks.txt' does not contain the winning row and/or column!" << endl; 
            return 0;
        }
        blockFile.close();
    } else {
        cout << "'blocks.txt' could not be opened for reading!" << endl;
        return 0;
    }

    // solve the Klotski puzzle
    Solver s = Solver(); // instantiate solver
    cout << "Finding optimal path..." << endl;
    bool success = s.solve(Board(blocks, winning_row, winning_col)); // generate tree and find optimal path
    cout << "Optimal path of length " << s.getDist() << " found!" << endl;
    vector<Move> optimalMoves = s.getMoves(); // get moves

    // start shell
    if (success) {
        cout << "Type 'next' for next move. Type 'exit' to exit shell." << endl;
        int i = 0;
        while(i < optimalMoves.size()) {
            cout << "> ";
            string input;
            getline(cin, input); 
            if (input == "next") {
                cout << i+1 << ". " << optimalMoves[i] << endl;
                i++;
            } else if (input == "exit") {
                break;
            }
        }
    }
    return success;
}