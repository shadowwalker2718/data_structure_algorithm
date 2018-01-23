//
// Created by root on 8/27/17.
//

#ifndef LEETCODE_C_667_BEAUTIFUL_ARRANGEMENT_II_H
#define LEETCODE_C_667_BEAUTIFUL_ARRANGEMENT_II_H

#include <henry.h>

namespace _667{

  namespace _1{
    class Solution {
    public:
      vector<int> constructArray(int n, int k) {
        // 1, n, 2, n-1,3
        int L = 2; int R = n;
        vector<int> res = {1};
        bool left = false;
        // 6, 4
        // 1,6,2,5,4
        for(int i=1; i<k; ++i) {
          if (left) {
            res.push_back(L++);
          } else {
            res.push_back(R--);
          }
          left = !left;
        }
        if (!left) {
          for(int i=L; i<=R; ++i) res.push_back(i);
        } else {
          for(int i=R; i>=L; --i) res.push_back(i);
        }
        return res;
      }
    };
  }


  namespace _2{
    class Solution {
    public:
      vector<int> constructArray(int n, int k) {
        vector<int> ret;
        ret.push_back(1);
        for(int i=2,j=n;i<=j;i++,j--) {
          ret.push_back(j);
          if(i!=j) ret.push_back(i);
        }
        sort(ret.begin()+(k-1), ret.end());
        if(k>1 && ret[k-2]<=n/2) {
          reverse(ret.begin()+(k-1), ret.end());
        }
        return ret;
      }
    };
  }



  void test(){
    _2::Solution sln;
    auto r=sln.constructArray(6,4);
    for(auto i: r) cout << i << ","; cout << endl;
  }

}




#endif //LEETCODE_C_667_BEAUTIFUL_ARRANGEMENT_II_H
