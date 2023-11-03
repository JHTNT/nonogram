#ifndef FILE_IO
#define FILE_IO
#include <fstream>

#include "config.h"

using namespace std;

ifstream in;
ofstream out;

void get_testcase(vector<vector<short>> &clues) {
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

#endif
