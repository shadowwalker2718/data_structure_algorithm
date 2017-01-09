#pragma once

#include "henry.h"

namespace _lnkd_totalcovered_length{
    struct Intervals { // if all values are positive
        vector<int> v;

        void addInterval(int from, int to) {
            v.emplace_back(from), v.emplace_back(-to);
        }

        int getTotalCoveredLength() {
            sort(v.begin(), v.end(), [](int i, int j) {return abs(i) < abs(j); });
            int r = 0, count = 0;
            stack<int> stk; // max size are 2
            for (int i = 0; i < v.size(); i++) {
                if (stk.empty()) { stk.push(v[i]); }
                if (v[i]>0) count++; else count--;
                if (count == 0) { r += abs(v[i]) - stk.top(); stk.pop(); }
            }
            return r;
        }
    };
    void test() {
        Intervals v;
        v.addInterval(3,6);
        v.addInterval(8, 9);
        v.addInterval(1, 5);
        assert(v.getTotalCoveredLength()==6);
    }
}