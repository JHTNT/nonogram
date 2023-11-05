#ifndef BOARD_SOLVER
#define BOARD_SOLVER
#include "line_solver.h"

typedef vector<string> Board;
typedef vector<vector<short>> Clues;
typedef unordered_set<short> UpdateSet;

enum Status { INCOMPLETE, CONFLICT, PAINTED, SOLVED };
static string const_status[] = {"INCOMPLETE", "CONFLICT", "PAINTED", "SOLVED"};

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
        string_view s = *front;
        char index = s[0];

        if (!fix(s, d[index], SIZE, d[index].size())) {
            status = Status::CONFLICT;
            return UpdateSet();
        }

        string p = paint(s, d[index], SIZE, d[index].size());
        s = s.substr(1);
        for (int i = 0; i < SIZE; i++) {
            if (s[i] == 'u' && p[i] != s[i]) {
                PI.insert(index * 100 + i);
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
        list_G.erase(front);
    }

    if (check_all_painted(G))
        status = Status::SOLVED;
    else
        status = Status::INCOMPLETE;
    return PI;
}

short probe(Board &G, const Clues &d, char row, char col, Status &status) {
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
        return 0;  // size of pi
    }

    UpdateSet pi;
    Board *src = &G_p0;
    if (status_gp0 == Status::CONFLICT) {
        pi = pi_gp1, src = &G_p1;
    } else if (status_gp1 == Status::CONFLICT) {
        pi = pi_gp0;
    } else {
        for (short p : pi_gp0) {
            if (G_p0[p / 100][p % 100 + 1] == G_p1[p / 100][p % 100 + 1]) pi.insert(p);
        }
        for (short p : pi_gp1) {
            if (G_p0[p / 100][p % 100 + 1] == G_p1[p / 100][p % 100 + 1]) pi.insert(p);
        }
    }

    if (!pi.empty()) {
        for (short p : pi) {
            char r = p / 100, c = p % 100;
            G[r][c + 1] = (*src)[r][c + 1];
            if (r < SIZE)
                G[c + SIZE][r + 1] = (*src)[r][c + 1];
            else
                G[c][r - SIZE + 1] = (*src)[r][c + 1];
        }
        status = Status::PAINTED;
    } else {
        status = Status::INCOMPLETE;
    }
    return pi.size();
}

short fp1(Board &G, const Clues &d, Status &status) {
    short pi_cnt, choosed_p = 1, tmp;
    do {
        pi_cnt = 0;
        propagate(G, d, status);
        if (status == CONFLICT || status == SOLVED) {
            return choosed_p;
        }

        unordered_set<short> unpaint;
        for (char i = 0; i < SIZE; i++) {
            for (char j = 1; j <= SIZE; j++) {
                if (G[i][j] == 'u') unpaint.insert(i * 100 + j);
            }
        }

        for (short p : unpaint) {
            char row = p / 100, col = p % 100;
            tmp = probe(G, d, row, col, status);
            if (tmp > pi_cnt) {
                pi_cnt = tmp;
                choosed_p = p;
            }
            if (status == CONFLICT || status == SOLVED) return choosed_p;
            if (status == PAINTED) break;
        }
    } while (pi_cnt > 0);
    return choosed_p;
}

void backtracking(Board &G, const Clues &d, Status &status) {
    fp1(G, d, status);
    if (status == CONFLICT || status == SOLVED) return;

    Status status_gp0 = Status::INCOMPLETE;
    Status status_gp1 = Status::INCOMPLETE;
    vector<string> G_p0(G);
    vector<string> G_p1(G);

    char row, col;
    for (char i = 0; i < SIZE; i++) {
        for (char j = 1; j <= SIZE; j++) {
            if (G[i][j] == 'u') row = i, col = j;
        }
    }

    G_p0[row][col] = '0';
    backtracking(G_p0, d, status_gp0);
    if (status_gp0 == SOLVED) {
        G = G_p0, status = status_gp0;
        return;
    }
    G_p1[row][col] = '1';
    backtracking(G_p1, d, status_gp1);
    if (status_gp1 == SOLVED) G = G_p1, status = status_gp1;
}

#endif