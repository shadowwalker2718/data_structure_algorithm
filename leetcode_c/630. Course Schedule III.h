//
// Created by root on 7/3/17.
//

#ifndef LEETCODE_C_630_COURSE_SCHEDULE_III_H
#define LEETCODE_C_630_COURSE_SCHEDULE_III_H

#include <henry.h>

namespace _630{
  class Solution {
  public:
    int scheduleCourse(vector<vector<int>>& courses) {
      sort(courses.begin(), courses.end(), [](vector<int>& l,vector<int>& r){
        return l[1]<r[1];
      });
      priority_queue<int> q;
      int time=0;
      for(auto c: courses){
        if(time+c[0] <= c[1])
          q.push(c[0]), time+=c[0];
        else if(!q.empty() && q.top()>c[0])
          time+=c[0]-q.top(), q.pop(), q.push(c[0]);
      }
      return q.size();
    }
  };

  void test(){
    vector<vector<int>> v={{100, 200}, {200, 1300}, {1000, 1250}, {2000, 3200}};
    Solution sln;
    assert(sln.scheduleCourse(v)==3);

    v={{100, 200}, {200, 1300}, {1000, 1250}, {500, 3200}};
    assert(sln.scheduleCourse(v)==4);
  }
}

#endif //LEETCODE_C_630_COURSE_SCHEDULE_III_H
