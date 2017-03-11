#pragma once

#include "henry.h"

namespace K_th_Smallest_in_Lexicographical_Order{

  struct Solution {
    int findKthNumber(int n, int k) {
      int cur = 1;
      --k;
      while (k) {
        int steps = calsteps(n, cur, cur + 1);
        if (steps <= k)
          ++cur, k -= steps;
        else
          cur *= 10, --k;
      }
      return cur;
    }
    int calsteps(int n, long n1, long n2) {////
      int steps = 0;
      while (n1 <= n) {
        steps += min(n + 1L, n2) - n1;
        n1 *= 10, n2 *= 10;
      }
      return steps;
    }
  };


  void test() {
    Solution s;
    assert(s.findKthNumber(13, 8) == 4);
    assert(s.findKthNumber(13, 2) == 10);
  }

}







