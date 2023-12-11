#ifndef BOARD_SOLVER
#define BOARD_SOLVER

#include <string>
#include <unordered_set>
#include <vector>

#include "line_solver.h"

// typedef std::vector<std::string> Board;
typedef std::vector<std::vector<short>> Clues;
typedef std::unordered_set<short> UpdateSet;

enum State { INCOMPLETE, CONFLICT, PAINTED, SOLVED };
static std::string const_status[] = {"INCOMPLETE", "CONFLICT", "PAINTED", "SOLVED"};

class Board {
    State state;
    vector<Line> lines;
    std::unordered_set<short> unpainted;

   public:
    Board();
    Board(const Board &G);
    bool is_painted(short i, short j);
    const bool check_all_painted(const std::vector<std::string> &G);
    UpdateSet propagate(const Clues &d, State &status);
    short probe(Board &G, const Clues &d, char row, char col, State &status);
    void backtracking(Board &G, const Clues &d, State &status);
    Line get_line(short i);
};

#endif