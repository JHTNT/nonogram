#include "board_solver.h"

using namespace std;

Board::Board() : state{INCOMPLETE} {
    lines = vector<Line>(SIZE * 2);
    for (int i = 0; i < SIZE * 2; i++) lines[i] = Line(i);
    for (int i = 1; i <= SIZE; i++) {
        for (int j = 1; j <= SIZE; j++) {
            unpainted.insert(i * 100 + j);
        }
    }
}

Board::Board(const Board &G) { *this = G; }

bool Board::check_all_painted(const std::vector<std::string> &G) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j <= SIZE; j++)
            if (G[i][j] == 'u') return false;
    return true;
}

bool Board::is_painted(short i, short j) {
    if 
}

UpdateSet Board::propagate(const Clues &d, State &status) {
    UpdateSet PI;                            // set of updated pixels
    unordered_set<Line, Line::Hash> list_G;  // set of lines to be checked

    for (int i = 0; i < SIZE; i++) {
        list_G.insert(this->get_line(i));
    }

    while (!list_G.empty()) {
        // auto front = list_G.begin();
        // std::string_view s = *front;
        Line s = *list_G.begin();
        char index = s.get_index();

        if (!s.fix(d[index], SIZE, d[index].size())) {
            status = State::CONFLICT;
            return UpdateSet();
        }

        s.paint(d[index], SIZE, d[index].size());
        for (int j = 0; j < SIZE; j++) {
            if (!is_painted(index, j)) {
                PI.insert(index * 100 + j);
                if (index < SIZE) {
                    lines[j + SIZE].set(index + 1, s.get(j));
                    list_G.insert(G[j + SIZE]);
                } else {
                    lines[j].set(index - SIZE + 1, s.get(j));
                    list_G.insert(G[j]);
                }
            }
        }
        list_G.erase(s);
    }

    if (check_all_painted(G))
        status = State::SOLVED;
    else
        status = State::INCOMPLETE;
    return PI;
}

short Board::probe(Board &G, const Clues &d, char row, char col, State &status) {
    State status_gp0 = State::INCOMPLETE;
    State status_gp1 = State::INCOMPLETE;
    std::vector<std::string> G_p0(G);
    std::vector<std::string> G_p1(G);

    G_p0[row][col] = '0';
    UpdateSet pi_gp0 = propagate(G_p0, d, status_gp0);
    G_p1[row][col] = '1';
    UpdateSet pi_gp1 = propagate(G_p1, d, status_gp1);

    if (status_gp0 == State::CONFLICT && status_gp1 == State::CONFLICT) {
        status = State::CONFLICT;
        return 0;  // size of pi
    }

    UpdateSet pi;
    Board *src = &G_p0;
    if (status_gp0 == State::CONFLICT) {
        pi = pi_gp1, src = &G_p1;
    } else if (status_gp1 == State::CONFLICT) {
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
        status = State::PAINTED;
    } else {
        status = State::INCOMPLETE;
    }
    return pi.size();
}

short Board::fp1(Board &G, const Clues &d, State &status) {
    short pi_cnt, choosed_p = 1, tmp;
    do {
        pi_cnt = 0;
        propagate(G, d, status);
        if (status == CONFLICT || status == SOLVED) {
            return choosed_p;
        }

        std::unordered_set<short> unpaint;
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

void Board::backtracking(Board &G, const Clues &d, State &status) {
    fp1(G, d, status);
    if (status == CONFLICT || status == SOLVED) return;

    State status_gp0 = State::INCOMPLETE;
    State status_gp1 = State::INCOMPLETE;
    std::vector<std::string> G_p0(G);
    std::vector<std::string> G_p1(G);

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