#ifndef FILE_IO
#define FILE_IO

#include <fstream>
#include <vector>

#include "config.h"

// static std::ifstream fin;
// static std::ofstream fout;

void get_testcase(std::ifstream &in, std::vector<std::vector<short>> &clues);

#endif