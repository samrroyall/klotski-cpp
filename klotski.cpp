#include "solver.h"
#include <fstream>

using namespace std;

vector<int> getInts(string s) {
    vector<int> res;
    string::iterator it = s.begin();
    while (*it == ' ' && it != s.end()) { it++; } // handle leading spaces
    while (it != s.end()) {
        string chars;
        while (*it != ' ' && it != s.end()) { chars += *(it++); };
        res.push_back(stoi(chars));
        while (*it == ' ' && it != s.end()) { it++; } // handle trailing spaces
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
    cout << "Finding successful path..." << endl;
    Board initialConfig = Board(blocks, winning_row, winning_col);
    bool success = s.solve(initialConfig); // generate tree and find successful path

    // return moves on path
    if (success) {
        cout << "Path of length " << s.getDist() << " found!" << endl;
        vector<Move> moves = s.getMoves(); // get moves
        cout << "Type 'next' for next move. Type 'exit' to exit shell." << endl;
        // start shell
        int i = 0;
        while (i < moves.size()) {
            cout << "> ";
            string input;
            getline(cin, input); 
            if (input == "next") {
                cout << i+1 << ". " << moves[i++] << endl;
            } else if (input == "exit") {
                break;
            }
        }
    }
    return success;
}