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
    UpdateSet PI;                  // set of updated pixels
    unordered_set<string> list_G;  // set of lines to be checked

    for (int i = 0; i < SIZE; i++) {
        list_G.insert(G[i]);
    }

    while (!list_G.empty()) {
        auto front = list_G.begin();
        string s = *front;
        char index = s[0];

        if (!fix(s, d[index], SIZE, d[index].size())) {
            status = Status::CONFLICT;
            return UpdateSet();
        }

        string p = paint(s, d[index], SIZE, d[index].size());
        s = s.substr(1);
        UpdateSet pi;
        for (int i = 0; i < SIZE; i++) {
            if (s[i] == 'u' && p[i] != s[i]) {
                pi.insert(index * 100 + i);
                G[index][i + 1] = p[i];
                if (index < SIZE) {
                    G[i + SIZE][index + 1] = p[i];
                    list_G.insert(G[i + SIZE]);
                } else {
                    G[i][index - SIZE + 1] = p[i];
                    list_G.insert(G[i]);
                }
            }
        }
        if (!pi.empty()) PI.insert(pi.begin(), pi.end());
        list_G.erase(front);
    }

    if (check_all_painted(G))
        status = Status::SOLVED;
    else
        status = Status::INCOMPLETE;
    return PI;
}

UpdateSet probe(Board &G, const Clues &d, char row, char col, Status &status) {
    Status status_gp0 = Status::INCOMPLETE;
    Status status_gp1 = Status::INCOMPLETE;
    vector<string> G_p0(G);
    vector<string> G_p1(G);

    G_p0[row][col] = '0';
    UpdateSet pi_gp0 = propagate(G_p0, d, status_gp0);
    G_p1[row][col] = '1';
    UpdateSet pi_gp1 = propagate(G_p1, d, status_gp1);

    if (status_gp0 == Status::CONFLICT && status_gp1 == Status::CONFLICT) {
        status = Status::CONFLICT;
        return UpdateSet();
    }

    UpdateSet pi;
    Board *src = &G_p0;
    if (status_gp0 == Status::CONFLICT)
        pi = pi_gp0;
    else if (status_gp1 == Status::CONFLICT)
        pi = pi_gp1, src = &G_p1;
    else
        set_intersection(pi_gp0.begin(), pi_gp0.end(), pi_gp1.begin(), pi_gp1.end(),
                         inserter(pi, pi.begin()));

    if (!pi.empty()) {
        for (short p : pi) {
            char r = p / 100, c = p % 100;
            G[r][c + 1] = (*src)[r][c + 1];
        }
        status = Status::PAINTED;
    } else {
        status = Status::INCOMPLETE;
    }
    return pi;
}

#endif