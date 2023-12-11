#include "line_solver.h"

using namespace std;

Line::Line(short i) : index{i}, pixels{string(SIZE, 'u')} {}

Line::Line(const Line& l) { *this = l; }

char Line::get(short i) { return this->pixels[i - 1]; }

void Line::set(short i, char c) { this->pixels[i - 1] = c; }

short Line::get_index() { return index; }

bool Line::fix(const vector<short>& d, short i, short j) {
    if (i == 0 || i == -1) {
        if (j == 0) return true;
        return false;  // j >= 1
    }
    return fix0(d, i, j) || fix1(d, i, j);
}

bool Line::fix0(const vector<short>& d, short i, short j) {
    if (this->get(i) != '1') return fix(d, i - 1, j);
    return false;
}

bool Line::fix1(const vector<short>& d, short i, short j) {
    if (j >= 1 && i >= d[j - 1]) {
        for (int k = i - d[j - 1] + 1; k <= i; k++)
            if (this->get(k) == '0') return false;
        if (i - d[j - 1] == 0 || this->get(i - d[j - 1]) != '1')
            return fix(d, i - d[j - 1] - 1, j - 1);
        else
            return false;
    }
    return false;
}

void Line::paint(const vector<short>& d, short i, short j) {
    if (i <= 0) return;

    bool f0 = fix0(d, i, j), f1 = fix1(d, i, j);
    if (f0 && !f1) {
        paint0(d, i, j);
    } else if (!f0 && f1) {
        paint1(d, i, j);
    } else {
        Line t = Line(*this);
        this->paint0(d, i, j);
        t.paint1(d, i, j);
        merge(*this, t, i);
    }
}

void Line::paint0(const vector<short>& d, short i, short j) {
    paint(d, i - 1, j);
    this->set(i, '0');
}

void Line::paint1(const vector<short>& d, short i, short j) {
    if (i == d[j - 1]) {
        for (int k = 0; k < i; k++) this->set(k, '1');
    } else {
        this->set(i - d[j - 1], '0');
        for (int k = i - d[j - 1] + 1; k <= i; k++) this->set(k, '1');
        paint(d, i - d[j - 1] - 1, j - 1);
    }
}

void Line::merge(Line l, Line t, short n) {
    for (int k = 1; k <= n; k++) {
        if (l.get(k) == '0' && t.get(k) == '0')
            l.set(k, '0');
        else if (l.get(k) == '1' && t.get(k) == '1')
            l.set(k, '1');
        else
            l.set(k, 'u');
    }
}
