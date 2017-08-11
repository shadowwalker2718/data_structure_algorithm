//
// Created by root on 7/20/17.
//

#ifndef LEETCODE_C_632_H
#define LEETCODE_C_632_H

#include <henry.h>

namespace _632{

  using PII=pair<int,int>; // <value, vec row index>
  struct cmp{ bool operator()(PII& p1, PII& p2){return p1.first>p2.first;} };
  struct Solution {
    vector<int> smallestRange(vector<vector<int>>& nums) {
      priority_queue<PII, vector<PII>, cmp> q;
      int ROW=nums.size(), count=0, r=INT_MAX;
      for(int i=0;i<ROW;++i)
        for(int j=0;j<nums[i].size();++j)
          q.push({nums[i][j], i});
      vector<int> m(ROW), rr; // counter
      list<PII> dq;
      while (!q.empty()){
        auto t = q.top();
        dq.push_back(t), q.pop();
        if(m[t.second]++ == 0) count++;
        while(count == ROW){
          const PII &y=dq.back(), &x=dq.front();
          int k=y.first-x.first;
          if(k<r) r=k, rr={x.first, y.first};
          m[x.second]--, dq.pop_front();
          if(m[x.second]==0) count--;
        }
      }
      return rr;
    }
  };

  void test(){
    Solution sln;
    vector<vector<int>> v={{4,10,15,24,26},{0,9,12,20},{5,18,22,30}};
    auto r=sln.smallestRange(v);
    copy(r.begin(), r.end(), ostream_iterator<int>(cout, " ")); cout << endl;
  }
}




#endif //LEETCODE_C_632_H
