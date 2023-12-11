#include <iostream>

#include "board_solver.h"
#include "config.h"
#include "file_io.h"

using namespace std;

static std::ifstream fin;
static std::ofstream fout;

int main(int argc, char *argv[]) {
    fin.open((string) argv[1] + ".in");
    fout.open((string) argv[1] + ".out");

    string testcase;

    while (!fin.fail() && fin >> testcase) {
        vector<vector<short>> clues(SIZE * 2);
        Board board(SIZE * 2, string(SIZE + 1, 'u'));
        for (int i = 0; i < SIZE * 2; i++) board[i][0] = i;

        State status = INCOMPLETE;
        fout << testcase << "\n";
        get_testcase(fin, clues);

        clock_t s, e;
        s = clock();
        backtracking(board, clues, status);
        e = clock();

        for (int i = 0; i < SIZE; i++) {
            for (int j = 1; j <= SIZE; j++) {
                fout << board[i][j] << ' ';
            }
            fout << '\n';
        }
        fout << "Time used: " << (double) (e - s) / CLOCKS_PER_SEC << " s\n" << flush;
        if (status == SOLVED)
            cout << testcase << ": \033[92mSOLVED\033[0m";
        else
            cout << testcase << ": \033[91m" << const_status[status] << "\033[0m";
        cout << " (" << (double) (e - s) / CLOCKS_PER_SEC << "s)\n";
    }
    fin.close();
    fout.close();
    return 0;
}