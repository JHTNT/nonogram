#include "file_io.h"

using namespace std;

void get_testcase(ifstream &in, vector<vector<short>> &clues) {
    short n, i = SIZE;
    char c;
    while (i < SIZE * 2) {
        in >> n;
        clues[i].push_back(n);
        in.get(c);
        if (c == '\n') i++;
    }
    i = 0;
    while (i < SIZE) {
        in >> n;
        clues[i].push_back(n);
        in.get(c);
        if (c == '\n') i++;
    }
}