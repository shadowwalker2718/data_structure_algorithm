//
// Created by root on 8/13/17.
//

#ifndef LEETCODE_C_660_REMOVE_9_H
#define LEETCODE_C_660_REMOVE_9_H

#include <henry.h>

namespace _660{

  class Solution {
  public:
    int newInteger(int n) {
      long long res = 0, s = 1;
      while (n) {
        res += n % 9LL * s;
        n /= 9;
        s *= 10;
      }
      return res>INT_MAX?INT_MAX:res;
    }
  };

  string chinese2decimal(string s){
    map<char,char> m={{'5','4'},{'6','5'},{'7','6'},{'8','7'},{'9','8'}};
    string r;
    for(char c: s){ // map from chinese to nonary
      if(c == '4') return "illegal";
      r += m.count(c)?m[c]:c;
    }
    int t=stoi(r), w=1, n=0, BASE=9;
    while(t)
      n += (t%10)*w, w*=BASE, t/=10;
    return to_string(n);
  }



  void test(){
    assert(chinese2decimal("15") == "13");

    Solution sln;
    assert(sln.newInteger(100)==121);
    cout << sln.newInteger(900000000) << endl;
  }


}

#endif //LEETCODE_C_660_REMOVE_9_H
