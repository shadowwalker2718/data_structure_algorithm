//
// Created by root on 7/25/17.
//
#include <henry.h>

#ifndef LEETCODE_C_621_TASK_SCHEDULER_H
#define LEETCODE_C_621_TASK_SCHEDULER_H

namespace _621{

  struct Solution {
    int leastInterval(vector<char> tasks, int n) {
      vector<int> v(26);
      for(char c: tasks) v[c-'A']++;
      sort(v.begin(), v.end());
      int r=0;
      while (v[25]) {
        int i=0;
        while(i <= n){
          if(v[25]==0)
            return r+accumulate(v.begin(), v.end(), 0);
          if(25-i>=0 && v[25-i]) v[25-i]--;
          r++, i++;
        }
        sort(v.begin(), v.end());
      }
      return r;
    }
  };

  class Solution2 {
  public:
    int leastInterval(vector<char> tasks, int n) {
      int v[26]={};
      for(char c: tasks) v[c-'A']++;
      sort(v, v+26); // O(1)
      int mx=v[25]-1, idle=mx*n;
      for(int i=24; i>=0 && v[i]>0; i--)
        idle -= min(v[i], mx);
      return idle>0 ? idle+tasks.size() : tasks.size();
    }
  };

  struct Solution3 {
    int leastInterval(vector<char>& tasks, int n) {
      int v[26]={};
      for(char c: tasks) v[c-'A']++;
      priority_queue<int> q;
      for(int i=0;i<26;++i)
        if(v[i]) q.push(v[i]);
      int r=0;
      vector<int> buf;
      while(!q.empty()){
        int i=n+1;
        while(i--){ // do it n times
          if(!q.empty()){
            if(q.top()>1) buf.push_back(q.top()-1);
            q.pop();
          }else{
            if(buf.empty()) break;
          }
          r++;
        }
        for(int k: buf) q.push(k);
        //for_each(buf.begin(), buf.end(), [&q](int k){ if(k>0) q.push(k); });
        buf.clear();
      }
      return r;
    }
  };

  struct SolutionX{
    string get_task_list(string s, int n){
      string r;
      map<char, int> m;
      for(int i=0, j=0;i<s.size();++i, ++j){
        char c=s[i];
        if(m.count(c))
          if(m[c]+n < j)
            r+=c, m[c]=j;
          else
            r+='*', i--;
        else
          r+=c, m[c]=j;
      }
      return r;
    }
    int get_task_nums(string s, int n){
      int r;
      map<char, int> m;
      for(int i=0, j=0;i<s.size();++i, ++j){
        char c=s[i];
        if(m.count(c))
          if(m[c]+n < j)
            r++, m[c]=j;
          else
            r++, i--;
        else
          r++, m[c]=j;
      }
      return r;
    }
  };

  class SolutionXX {
  public:
    int maxSubArrayLen(vector<int>& n, int k) {
      map<int, set<int>> c2i; // cumulative sum to index
      c2i[n.front()].insert(0);
      for(int i=1; i<n.size(); ++i)
        n[i]+=n[i-1], c2i[n[i]].insert(i);
      int r=0;
      if(c2i.count(k))
        r=*c2i[k].rbegin();
      for(int i=0;i<n.size();i++){
        if(c2i.count(n[i]+k)){
          r=max(r, *c2i[n[i]+k].rbegin()-i);
        }
      }
      return r;
    }
  };

  void test(){
    /*SolutionXX slnx;
    cout << (slnx.run("1121",2)=="1**12*1") << endl;
    cout << (slnx.run("123123",3)=="123*123") << endl;
    cout << (slnx.run("123456246124",6)=="123456**2*4*61*2*4") << endl;*/

    vector<char> v1(7,'A'),v2(7,'B'),v3(7,'C'),v4(7,'D'),v5(7,'E'),
      v6(7,'F'), v7(7,'G'), v8(6,'H'), v9(5,'I'), v10(4,'J');
    vector<char> v11(4,'K'), v12(2,'L'), v13(2,'M'), v14(1,'N'), v15(1,'O');
    v1.insert(v1.end(), v2.begin(), v2.end());
    v1.insert(v1.end(), v3.begin(), v3.end());
    v1.insert(v1.end(), v4.begin(), v4.end());
    v1.insert(v1.end(), v5.begin(), v5.end());
    v1.insert(v1.end(), v6.begin(), v6.end());
    v1.insert(v1.end(), v7.begin(), v7.end());
    v1.insert(v1.end(), v8.begin(), v8.end());
    v1.insert(v1.end(), v9.begin(), v9.end());
    v1.insert(v1.end(), v10.begin(), v10.end());
    v1.insert(v1.end(), v11.begin(), v11.end());
    v1.insert(v1.end(), v12.begin(), v12.end());
    v1.insert(v1.end(), v13.begin(), v13.end());
    v1.insert(v1.end(), v14.begin(), v14.end());
    v1.insert(v1.end(), v15.begin(), v15.end());
    Solution sln;
    cout << sln.leastInterval(v1, 5) << endl;
    Solution2 sln2;
    cout << sln2.leastInterval(v1, 5) << endl;
    Solution3 sln3;
    cout << sln3.leastInterval(v1, 5) << endl;
  }
  void test2(){
    vector<char> v1(7,'A'),v2(7,'B'),v3(6,'C'),v4(6,'D'),v5(6,'E');
    v1.insert(v1.end(), v2.begin(), v2.end());
    v1.insert(v1.end(), v3.begin(), v3.end());
    v1.insert(v1.end(), v4.begin(), v4.end());
    v1.insert(v1.end(), v5.begin(), v5.end());
    Solution sln;
    cout << sln.leastInterval(v1, 5) << endl;
    Solution2 sln2;
    cout << sln2.leastInterval(v1, 5) << endl;
  }
}

class Solution {
public:
  int maxSubArrayLen(vector<int>& n, int k) {
    if(n.empty()) return 0;
    map<int, set<int>> c2i; // cumulative sum to index
    c2i[n.front()].insert(0);
    for(int i=1; i<n.size(); ++i)
      n[i]+=n[i-1], c2i[n[i]].insert(i);
    int r=0;
    if(c2i.count(k))
      r=*c2i[k].rbegin()+1;
    for(int i=0;i<n.size();i++){
      if(c2i.count(n[i]+k)){
        r=max(r, *c2i[n[i]+k].rbegin()-i);
      }
    }
    return r;
  }
};


#endif //LEETCODE_C_621_TASK_SCHEDULER_H
