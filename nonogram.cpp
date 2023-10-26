#include <bits/stdc++.h>

#include "config.h"
#include "file_io.h"

int main() {
    in.open("data/one_testcase.in");
    out.open("data/one_testcase.out");

    string testcase;
    vector<vector<short>> clues(SIZE * 2);

    while (!in.fail() && in >> testcase) {
        out << testcase << "\n";
        get_testcase(clues);
        for (auto c : clues) {
            for (short i : c) out << i << " ";
            out << "\n";
        }
    }
    in.close();
    out.close();
    return 0;
}