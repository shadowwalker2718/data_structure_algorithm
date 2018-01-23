//
// Created by root on 9/2/17.
//

#ifndef LEETCODE_C_FB_AMAZING_NUMBER_H
#define LEETCODE_C_FB_AMAZING_NUMBER_H

#include <henry.h>

namespace _fb_amazing_number{
  //http://shirleyisnotageek.blogspot.com/2016/11/amazing-number.html

  namespace _1{
    int GetAmazingNumber(vector<int> v){
      vector<pair<int,int>> intervals;
      int L=v.size();
      for(int i=0;i<L;++i){
        if(v[i]>=L) continue;
        int start=(i+1) % L, end=(i-v[i]+L) % L;
        intervals.emplace_back(start, end);
      }
      vector<int> cnt(L);
      for(auto pr: intervals){
        cnt[pr.first]++;
        if(pr.first>pr.second) cnt[0]++;
        if(pr.second+1<L) cnt[pr.second+1]--;
      }
      partial_sum(cnt.begin(), cnt.end(), cnt.begin());
      return max_element(cnt.begin(), cnt.end())-cnt.begin();
    }
  }


  namespace _2{
    int GetAmazingNumber(vector<int> v){
      int L=v.size(), r=0;
      for(int i=0;i<L;++i){
        int c=0, t=L, j=i, k=0;
        while(t--)
          if(v[(j++)%L] <= k++) c++;
        r=max(r,c);
      }
      return r;
    }
  }



  void test(){
    assert(_2::GetAmazingNumber({3,0,1,0}) == 1);
    assert(_1::GetAmazingNumber({3,0,1,0}) == 1);
  }

}



#endif //LEETCODE_C_FB_AMAZING_NUMBER_H
