#ifndef BOARD_SOLVER
#define BOARD_SOLVER

#include <string>
#include <vector>
#include <unordered_set>

#include "line_solver.h"

typedef std::vector<std::string> Board;
typedef std::vector<std::vector<short>> Clues;
typedef std::unordered_set<short> UpdateSet;

enum Status { INCOMPLETE, CONFLICT, PAINTED, SOLVED };
static std::string const_status[] = {"INCOMPLETE", "CONFLICT", "PAINTED", "SOLVED"};

bool check_all_painted(const std::vector<std::string> &G);
UpdateSet propagate(Board &G, const Clues &d, Status &status);
short probe(Board &G, const Clues &d, char row, char col, Status &status);
void backtracking(Board &G, const Clues &d, Status &status);

#endif