//
// Created by root on 8/6/17.
//

#ifndef LEETCODE_C_656_COIN_PATH_H
#define LEETCODE_C_656_COIN_PATH_H

#include <henry.h>

namespace _656{

  struct Solution {
    vector<int> cheapestJump(vector<int>& A, int B) {
      if(A.empty() || !B) return {};
      if(A.size()==1 && B>=1) return {1};
      vector<vector<int>> r;
      vector<int> p={1};
      int gsum=INT_MAX;
      for(int i=1; i<A.size()&&i<=B; ++i)
        if(A[i]!=-1)
          dfs(A, B, r, p, i, gsum, A[0]);
      if(r.size()==1) return r.back();
      if(r.empty()) return {};
      sort(r.begin(), r.end(), [](const vector<int>& lhs, const vector<int>& rhs){
        int M = lhs.size(), N = rhs.size();
        for(int i = 0; i < min(M,N); i++)
          if(lhs[i] != rhs[i]) return lhs[i] < rhs[i];
        return M < N;
      });
      return r[0];
    }
    void dfs(vector<int>& a, int b, vector<vector<int>>& r, vector<int>& p,
             int i, int& gsum, int csum)
    {
      if(gsum<csum) return;
      if(i>=a.size()){
        if(r.empty()){
          r.push_back(p), gsum=csum;
        }else{
          if(gsum == csum){
            if(r.back()!=p)r.push_back(p);
          }else if(gsum > csum){
            r.clear(), r.push_back(p), gsum=csum;
          }
        }
        return;
      }
      for(int j=i; j<a.size() && j<i+b; j++){
        if(a[j]==-1) continue;
        if(!p.empty() && p.back()+b<j) continue; //
        p.push_back(j+1);
        dfs(a,b,r,p,j+1,gsum,csum+a[j]);
        p.pop_back();
      }
    }
  };


  bool operator<(const vector<int>& l, const vector<int>& r){
    int m=l.size(), n=r.size();
    for(int i=0;i<min(m,n);++i)
      if(l[i]!=r[i]) return l[i]<r[i];
    return m<n;
  }
  struct Solution2 {
    vector<int> cheapestJump(vector<int>& A, int B) {
      int L=A.size();
      vector<int> dp(L+1, INT_MAX);
      vector<vector<int>> pa(L+1, vector<int>()); //
      dp[0]=0, dp[1]=A[0], pa[1]={1}; // dp[x] min cost from 1 to x, pa[x] - path from 1 to x
      for (int i=2; i<L+1; ++i) {
        if (A[i-1]==-1) continue;
        for (int j=1; j<=B; j++) {
          if (i-j<=0 || dp[i-j]==INT_MAX) continue;
          int t=dp[i-j] + A[i-1];
          if(dp[i] > t){
            dp[i] = dp[i-j] + A[i-1];
            pa[i] = pa[i-j], pa[i].push_back(i);
          }else if(dp[i] == t){
            auto tp = pa[i-j];
            tp.push_back(i);
            if(tp < pa[i]){
              pa[i]=tp;
            }
          }
        }
      }
      return pa[L];
    }
  };

  void test(){
    {
      Solution sln;
      vector<int> v={36,33,18,55,98,14,77,43,6,97,49,72,62,48,68,65,22,18,63,44,14,4,99,52,52,23,47};
      auto r=sln.cheapestJump(v, 63);
      for(auto i: r) cout << i << endl;
    }

    {
      Solution2 sln;
      vector<int> vi={1,2,4,-1,2};
      auto r=sln.cheapestJump(vi, 2);
      for(auto i: r) cout << i << endl;
    }

  }
}

#endif //LEETCODE_C_656_COIN_PATH_H
