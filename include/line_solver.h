#ifndef LINE_SOLVE
#define LINE_SOLVE

#include <string>
#include <string_view>
#include <vector>

#include "config.h"

bool fix(std::string_view s, const std::vector<short> &d, short i, short j);
bool fix0(std::string_view s, const std::vector<short> &d, short i, short j);
bool fix1(std::string_view s, const std::vector<short> &d, short i, short j);
std::string paint(std::string_view s, const std::vector<short> &d, short i, short j);
std::string paint0(std::string_view s, const std::vector<short> &d, short i, short j);
std::string paint1(std::string_view s, const std::vector<short> &d, short i, short j);
std::string merge(std::string_view s, std::string_view t);

#endif