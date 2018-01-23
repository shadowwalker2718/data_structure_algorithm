//
// Created by root on 8/24/17.
//

#ifndef LEETCODE_C_POJ_3608_BRIDGE_ACROSS_ISLANDS_H
#define LEETCODE_C_POJ_3608_BRIDGE_ACROSS_ISLANDS_H

#include <henry.h>

namespace poj_3608{
  struct solution{
    vector<Point> l, r;
    void getinput(){
      int m, n;
      cin >> m >> n;
      int x,y;
      while(m--) cin >> x >> y, l.emplace_back(x,y);
      while(n--) cin >> x >> y, r.emplace_back(x,y);
    }
  };
};

struct Solution { // 64.18 %
  vector<string> removeInvalidParentheses(string s) {
    unordered_set<string> res;
    int left = 0, right = 0;
    for (char c : s)
      if(c=='(')  left++; else if(c==')') left>0 ? left-- : right++;
    dfs(s, 0, 0, left, right, "", res);
    return vector<string>(res.begin(), res.end());
  }
  void dfs(string& s, int i, int cl, int l, int r, string p, unordered_set<string>&res) {
    if(cl<0) return;
    if (i == s.size()) {
      if (0 == l && 0 == r) res.insert(p);
      return;
    }
    if ('(' == s[i]) {
      if (l>0) dfs(s, i+1, cl, l-1, r, p, res); // remove (
      dfs(s, i+1, cl+1, l, r, p+s[i], res);
    } else if (')' == s[i]) {
      if (r>0) dfs(s, i+1, cl, l, r-1, p, res); // remove )
      dfs(s, i+1, cl-1, l, r, p+s[i], res);
    } else dfs(s, i+1, cl, l, r, p+s[i], res);
  }
};

#endif //LEETCODE_C_POJ_3608_BRIDGE_ACROSS_ISLANDS_H
