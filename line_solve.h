#ifndef LINE_SOLVE
#define LINE_SOLVE
#include <bits/stdc++.h>

#include "config.h"

using namespace std;

bool fix(string_view s, const vector<short> &d, short i, short j);
bool fix0(string_view s, const vector<short> &d, short i, short j);
bool fix1(string_view s, const vector<short> &d, short i, short j);
string paint(string_view s, const vector<short> &d, short i, short j);
string paint0(string_view s, const vector<short> &d, short i, short j);
string paint1(string_view s, const vector<short> &d, short i, short j);
string merge(string_view s, string_view t);

bool fix(string_view s, const vector<short> &d, short i, short j) {
    if (i == 0 && j == 0) return true;
    if (i == 0 && j >= 1) return false;
    return fix0(s, d, i, j) || fix1(s, d, i, j);
}

bool fix0(string_view s, const vector<short> &d, short i, short j) {
    if (s[i - 1] == '0' || s[i - 1] == 'u') return fix(s, d, i - 1, j);
    return false;
}

bool fix1(string_view s, const vector<short> &d, short i, short j) {
    if (j >= 1 && i >= d[j - 1] + 1 && s[i - d[j - 1] - 1] == '0') {
        for (int k = i - d[j - 1]; k < i; k++)
            if (s[k] == '0') return false;
        return true;
    }
    return false;
}

string paint(string_view s, const vector<short> &d, short i, short j) {
    if (i == 0) return "";

    bool f0 = fix0(s, d, i, j), f1 = fix1(s, d, i, j);
    if (f0 && !f1) {
        return paint0(s, d, i, j);
    } else if (!f0 && f1) {
        return paint1(s, d, i, j);
    } else {
        return merge(paint0(s, d, i, j), paint1(s, d, i, j));
    }
}

string paint0(string_view s, const vector<short> &d, short i, short j) {
    return paint(s, d, i - 1, j) + '0';
}

string paint1(string_view s, const vector<short> &d, short i, short j) {
    return paint(s, d, i - d[j - 1] - 1, j - 1) + '0' + string(d[j - 1], '1');
}

string merge(string_view s, string_view t) {
    string m = "";
    for (int k = 0; k < s.size(); k++) {
        if (s[k] == '0' && t[k] == '0')
            m += '0';
        else if (s[k] == '1' && t[k] == '1')
            m += '1';
        else
            m += 'u';
    }
    return m;
}

#endif