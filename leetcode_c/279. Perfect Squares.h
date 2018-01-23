//
// Created by root on 8/14/17.
//

#ifndef LEETCODE_C_279_PERFECT_SQUARES_H
#define LEETCODE_C_279_PERFECT_SQUARES_H

#include "henry.h"

namespace _279{

  class Solution {
  public:
    int numSquares(int n) { // 2
      static vector<int> dp(n+1,-1); //
      if(dp[n]!=-1) return dp[n];
      if(isps(n)) return dp[n]=1;
      int r=INT_MAX;
      for(int i=1;i<n;++i)
        if(isps(i))
          dp[i]=1, r=min(r, 1+numSquares(n-i));
      return dp[n]=(r==INT_MAX?1:r);
    }

    bool isps(int x){ // 1
      static vector<short> ps(x+1,-1);
      if(ps[x]!=-1) return ps[x];
      int h=1, t=(x+1)/2;
      while(h<=t){
        long long m=h+(t-h)/2, p=m*m;
        if(p>x) t=m-1;
        else if(p<x) h=m+1;
        else
          return ps[x]=1;
      }
      return ps[x]=0;
    }
  };

  class Solution2 {
  public:
    int numSquares(int n) {
      int res = n, num = 2;
      while (num * num <= n) {
        int a = n / (num * num), b = n % (num * num);
        res = min(res, a + numSquares(b));
        ++num;
      }
      return res;
    }
  };

  void test(){
    Solution2 sln;
    cout << sln.numSquares(133334) << endl;
  }

}






#endif //LEETCODE_C_279_PERFECT_SQUARES_H
