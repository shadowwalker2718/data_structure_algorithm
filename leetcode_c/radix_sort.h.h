//
// Created by root on 8/12/17.
//

#ifndef LEETCODE_C_RADIX_SORT_H_H
#define LEETCODE_C_RADIX_SORT_H_H

#include <henry.h>



namespace __radix_sort{
  class Solution2 {
  public:
    vector<int> findClosestElements(vector<int>& v, int k, int x) {
      auto f=[&x](int i, int j){return abs(i-x)<abs(j-x);};
      partial_sort(v.begin(),v.begin()+k, v.end(), f);
      sort(v.begin(), v.begin()+k);
      return vector<int>(v.begin(), v.begin()+k);
    }
  };


  class Solution {
    //vector<bool> m;
  public:
    bool isPossible(vector<int>& n) {
      int L=n.size();
      vector<bool> m(L,true);
      return dfs(n, m);
    }
    bool dfs(vector<int>& n, vector<bool> m){
      int start=INT_MIN, count=0;
      for(int i=0;i<n.size();++i){
        if(m[i]){
          if(start==INT_MIN)
            start=n[i], count=1, m[i]=0; //1
          else if(n[i]==start+1){
            start++, count++, m[i]=0;
            if(count>=3 && dfs(n, m))
              return true;
          }
        }
      }
      return 0;
    }
  };



}

#endif //LEETCODE_C_RADIX_SORT_H_H
