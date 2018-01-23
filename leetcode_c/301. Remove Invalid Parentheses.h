//
// Created by root on 8/26/17.
//

#ifndef LEETCODE_C_301_REMOVE_INVALID_PARENTHESES_H
#define LEETCODE_C_301_REMOVE_INVALID_PARENTHESES_H

//#include "301. Remove Invalid Parentheses.h"
#include <henry.h>

namespace _301{
  class Solution { // 63.43 %
    bool isValid(string s) {
      int sum = 0;
      for(char &c : s) {
        if(c == '(') ++sum; else if(c == ')') --sum;
        if(sum < 0) return false;
      }
      return sum == 0;
    }
  public:
    vector<string> removeInvalidParentheses(string s) {
      int left = 0, right = 0;
      for (char c : s)
        if(c=='(')  left++; else if(c==')') left>0 ? left-- : right++;
      vector<string> r;
      dfs(s, 0, left, right, r);
      return r;
    }
    void dfs(string s, int begin, int left, int right, vector<string> &r) {
      if(left == 0 && right == 0){
        if(isValid(s)) r.push_back(s);
        return;
      }
      for(int i = begin; i < s.size(); i++) {
        string t = s;
        if(right > 0 && t[i] == ')' || left > 0 && t[i] == '(') {
          if(i>begin && t[i]==t[i-1]) continue;
          t.erase(i, 1);// Optimized a little bit here
          if (right > 0) dfs(t, i, left, right - 1, r);
          else if (left > 0) dfs(t, i, left - 1, right, r);
        }
      }
    }
  };

  struct Solution2 { // 64.18 %
    vector<string> removeInvalidParentheses(string s) {
      unordered_set<string> res;
      int left = 0, right = 0;
      for (char c : s)
        if(c=='(')  left++; else if(c==')') left>0 ? left-- : right++;
      dfs(s, 0, 0, left, right, "", res);
      return vector<string>(res.begin(), res.end());
    }
    void dfs(string& s, int i, int cl, int l, int r, string p, unordered_set<string>&res) {
      if(cl<0 || l<0) return; // the parentheses is invalid
      if(i == s.size()) { if (0==l && 0==r) res.insert(p); return; }
      if('(' == s[i]) {
        int j=1; // number of consecutive '('
        while(i+j<s.size() && s[i+j]=='(') j++;
        int t=min(j,l);
        if(l>0) dfs(s, i+t, cl, l-t, r, p, res); // remove '('
        string u=p;
        dfs(s, i+t, cl+t, l, r, u.append(t,'('), res);
      } else if (')' == s[i]) {
        if (r>0) dfs(s, i+1, cl, l, r-1, p, res); // remove ')'
        dfs(s, i+1, cl-1, l, r, p+s[i], res);
      } else dfs(s, i+1, cl, l, r, p+s[i], res);
    }
  };

  struct Solution3 { // 36%
    vector<string> removeInvalidParentheses(string s) {
      if(s.empty()) return {""};
      int left = 0, right = 0;
      for (char c : s)
        if(c=='(')  left++; else if(c==')') left>0 ? left-- : right++;
      unordered_set<string> rs, visited;
      queue<pair<string,pair<int,int>>> q;
      q.push({s,{left,right}});
      if(valid(s)) rs.insert(s);
      visited.insert(s);
      while(!q.empty() && rs.empty()){ // break if r is not empty
        int count=q.size();
        while(count--){
          auto f = q.front(); q.pop();
          string& t=f.first;
          bool found=0;
          for(int i=0; i<t.size(); ++i){
            int l=f.second.first, r=f.second.second;
            if(t[i]=='(' || t[i]==')'){
              if(t[i]=='(')l--; else if(t[i]==')') r--;
              string ns=t.substr(0,i)+t.substr(i+1);
              if(l==0 && r==0 && valid(ns)) rs.insert(ns), found=1;
              if(!visited.count(ns))
                q.push({ns,{l,r}}), visited.insert(ns);
            }
          }
          if(found) break;
        }
      }
      return vector<string>(rs.begin(), rs.end());
    }
    bool valid(const string& s){
      int l=0;
      for(char c: s){
        if(c=='(') ++l; else if(c==')') --l;
        if(l<0) return false;
      }
      return l==0;
    }
  };

  void test(){
    Solution3 sln;
    sln.removeInvalidParentheses(")))(()")[0] == "()";
  }

}





#endif //LEETCODE_C_301_REMOVE_INVALID_PARENTHESES_H
