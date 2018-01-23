//
// Created by root on 8/13/17.
//

#ifndef LEETCODE_C_273_INTEGER_TO_ENGLISH_WORDS_H
#define LEETCODE_C_273_INTEGER_TO_ENGLISH_WORDS_H

#include <henry.h>

namespace _273{
  struct Solution {// 3ms
    vector<string> _1_19 = { "One", "Two", "Three", "Four", "Five", "Six",
                             "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve",
                             "Thirteen", "Fourteen", "Fifteen", "Sixteen",
                             "Seventeen", "Eighteen", "Nineteen" };
    vector<string> _10_90 = { "Ten", "Twenty", "Thirty", "Forty", "Fifty",
                              "Sixty", "Seventy", "Eighty", "Ninety" };

    string rec(int n) {
      if (n >= 1e9) {
        return rec(n / 1e9) + " Billion" + rec(n % (int)1e9);
      } else if (n >= 1e6) {
        return rec(n / 1e6) + " Million" + rec(n % (int)1e6);
      } else if (n >= 1000) {
        return rec(n / 1000) + " Thousand" + rec(n % 1000);
      } else if (n >= 100) { // 100-999
        return rec(n / 100) + " Hundred" + rec(n % 100);
      } else if (n >= 20) { // 20-99
        return  " " + _10_90[n / 10 - 1] + rec(n % 10);
      } else if (n >= 1) { // 1-19
        return " " + _1_19[n - 1];
      } else {
        return "";
      }
    }
    string numberToWords(int num) {
      if (num == 0) return "Zero";
      string r = rec(num);
      r.erase(r.begin());
      return r;
    }
  };
}

#endif //LEETCODE_C_273_INTEGER_TO_ENGLISH_WORDS_H
