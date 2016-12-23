#pragma once

#include "henry.h"



namespace _knn {
    struct point {
        int x;
        int y;
        point(int x_, int y_):x(x_),y(y_) {}
    };

    point* knn(vector<point>& ps, int k) { // O(N)
        if (ps.size() <= k) return NULL;
        nth_element(ps.begin(), ps.begin() + k - 1, ps.end(), [](point& p1,point& p2) {
            (p1.x*p1.x + p1.y*p1.y) < (p2.x*p2.x + p2.y*p2.y);
        });
        return &ps[k - 1];
    }


}