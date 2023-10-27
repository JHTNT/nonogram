#ifndef LINE_SOLVE
#define LINE_SOLVE
#include <bits/stdc++.h>

using namespace std;

bool fix(string_view s, const vector<short> &d, short i, short j);
bool fix0(string_view s, const vector<short> &d, short i, short j);
bool fix1(string_view s, const vector<short> &d, short i, short j);

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

#endif