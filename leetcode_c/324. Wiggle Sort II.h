//
// Created by root on 8/5/17.
//

#ifndef LEETCODE_C_324_WIGGLE_SORT_II_H
#define LEETCODE_C_324_WIGGLE_SORT_II_H

#include <henry.h>

namespace _324{
  class Solution {
  public:
    void wiggleSort(vector<int>& nums) {
#define A(i) nums[(1 + 2 * i) % (n | 1)]
      int n = nums.size(), i = 0, j = 0, k = n - 1;
      auto midptr = nums.begin() + n / 2;
      nth_element(nums.begin(), midptr, nums.end());
      int mid = *midptr;
      while (j <= k) {
        if (A(j) > mid)
          swap(A(i++), A(j++));
        else if (A(j) < mid)
          swap(A(j), A(k--));
        else
          ++j;
      }
    }
  };

  bool iswiggle(vector<int>& v){
    for(int i=1;i<v.size();++i){
      if(i%2==0 && v[i]>v[i-1]) return 0;
      if(i%2 && v[i]<v[i-1]) return 0;
    }
    return 1;
  }

  void test(){
    Solution sln;
    vector<int> vi={1, 3, 2, 2, 3, 1};
    sln.wiggleSort(vi);
    cout << iswiggle(vi) << endl;
  }
};

#endif //LEETCODE_C_324_WIGGLE_SORT_II_H
