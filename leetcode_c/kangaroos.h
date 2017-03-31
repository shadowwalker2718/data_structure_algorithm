#pragma once

#include "henry.h"

namespace _kangaroos {
  
  bool istarget(const string& s) {
    int L = s.size();
    if (s[L / 2] != '_') return false;
    for (int i = 0; i < L / 2; ++i) if (s[i] != '<') return false;
    for (int i = L / 2 + 1; i < L; ++i) if (s[i] != '>') return false;
    return true;
  }

  bool alive(const string& s, int i) {
    bool r;
    if (i > s.size() / 2)
      r = (i - 2 >= 0 && s[i - 2] == '>') || (i - 1 >= 0 && s[i - 1] == '>');
    else if (i < s.size() / 2)
      r = (i + 1 < s.size() && s[i + 1] == '<') || (i + 2 < s.size() && s[i + 2] == '<');
    else
      r = true;// istarget(s); //cout << s << "," <<r<< endl;
    return r;
  }

  bool dfs(vector<string>& r, const string& s, int i) {
    if (istarget(s)) {
      r.push_back(s);
      return true;
    }
    for (int j = i-2; j>=0 && j < i; ++j) {
      if (j>=0 && s[j] == '>') {
        string t = s;
        swap(t[i], t[j]);
        if (alive(t,j) && dfs(r, t, j)) {
          r.push_back(s);
          return true;
        }
      }
    }
    for (int j = i+2; j > i; --j) {
      if (j<s.size() && s[j] == '<') {
        string t = s;
        swap(t[i], t[j]);
        if (alive(t, j) && dfs(r, t, j)) {
          r.push_back(s);
          return true;
        }
      }
    }
    return false;
  }

  // ">_<" ==> "<_>"
  void path(string& s) {
    int L = s.size();
    vector<string> r;
    if (dfs(r, s, L / 2)) {
      cout << "found path after " << r.size() << " steps moving." << endl;
    }
  }

  void test() {
    for (int i = 2; i < 100; ++i) {
      string s = string(i, '>') + "_" + string(i, '<');
      path(s);
    }
  }

}








