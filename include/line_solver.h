#ifndef LINE_SOLVE
#define LINE_SOLVE

#include <functional>
#include <string>
#include <string_view>
#include <vector>

#include "config.h"

class Line {
    char index;

   public:
    std::string pixels;
    Line(short i);
    Line(const Line& l);
    char get(short i);
    void set(short i, char c);
    short get_index();
    bool fix(const std::vector<short>& d, short i, short j);
    void paint(const std::vector<short>& d, short i, short j);
    static void merge(Line l, Line t, short n);

    struct Hash {
        std::size_t operator()(const Line& l) {
            return std::hash<std::string>()(l.pixels + l.index);
        }
    };

   private:
    bool fix0(const std::vector<short>& d, short i, short j);
    bool fix1(const std::vector<short>& d, short i, short j);
    void paint0(const std::vector<short>& d, short i, short j);
    void paint1(const std::vector<short>& d, short i, short j);
};

#endif