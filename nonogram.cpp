#include <bits/stdc++.h>

#include "config.h"
#include "file_io.h"
#include "line_solve.h"

int main() {
    in.open("data/one_testcase.in");
    out.open("data/one_testcase.out");

    string testcase;
    vector<vector<short>> clues(SIZE * 2);
    vector<vector<char>> board(SIZE, vector<char>(SIZE, 'u'));

    while (!in.fail() && in >> testcase) {
        out << testcase << "\n";
        get_testcase(clues);
    }
    in.close();
    out.close();
    return 0;
}