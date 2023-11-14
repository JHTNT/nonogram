#include <bits/stdc++.h>

#include "board_solver.h"
#include "config.h"
#include "file_io.h"

int main(int argc, char *argv[]) {
    in.open((string) argv[1] + ".in");
    out.open((string) argv[1] + ".out");

    string testcase;

    while (!in.fail() && in >> testcase) {
        vector<vector<short>> clues(SIZE * 2);
        Board board(SIZE * 2, string(SIZE + 1, 'u'));
        for (int i = 0; i < SIZE * 2; i++) board[i][0] = i;

        Status status = INCOMPLETE;
        out << testcase << "\n";
        get_testcase(clues);

        clock_t s, e;
        s = clock();
        backtracking(board, clues, status);
        e = clock();

        for (int i = 0; i < SIZE; i++) {
            for (int j = 1; j <= SIZE; j++) {
                out << board[i][j] << ' ';
            }
            out << '\n';
        }
        out << "Time used: " << (double) (e - s) / CLOCKS_PER_SEC << " s\n" << flush;
        if (status == SOLVED)
            cout << testcase << ": \033[92mSOLVED\033[0m\n";
        else
            cout << testcase << ": \033[91m" << const_status[status] << "\033[0m\n";
    }
    in.close();
    out.close();
    return 0;
}