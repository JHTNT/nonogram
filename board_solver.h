#ifndef BOARD_SOLVER
#define BOARD_SOLVER
#include "line_solver.h"

typedef vector<string> Board;
typedef vector<vector<short>> Clues;
typedef unordered_set<short> UpdateSet;

enum Status { INCOMPLETE, CONFLICT, PAINTED, SOLVED };

bool check_all_painted(const vector<string> &G) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j <= SIZE; j++)
            if (G[i][j] == 'u') return false;
    return true;
}

UpdateSet propagate(Board &G, const Clues &d, Status &status) {
    UpdateSet PI;  // set of updated pixels
    queue<string> list_G;

    for (int i = 0; i < SIZE * 2; i++) {
        list_G.push(G[i]);
    }

    while (!list_G.empty()) {
        string_view s = list_G.front();
        char index = s[0];

        if (!fix(s, d[index], SIZE, d[index].size())) {
            status = Status::CONFLICT;
            return UpdateSet();
        }

        string p = paint(s, d[index], SIZE, d[index].size());
        s = s.substr(1);
        UpdateSet pi;
        for (int i = 0; i < SIZE; i++) {
            if (p[i] != s[i]) {
                pi.insert(index * 100 + (i - 1));
                G[index][i] = p[i];
                if (i <= SIZE) {
                    list_G.push(G[i + SIZE - 1]);
                } else {
                    list_G.push(G[i - SIZE - 1]);
                }
            }
        }
        PI.insert(pi.begin(), pi.end());
        list_G.pop();
    }

    if (check_all_painted(G))
        status = Status::SOLVED;
    else
        status = Status::INCOMPLETE;
    return PI;
}

#endif