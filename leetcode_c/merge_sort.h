//
// Created by root on 9/7/17.
//

#ifndef LEETCODE_C_MERGE_SORT_H
#define LEETCODE_C_MERGE_SORT_H

#include <henry.h>

namespace _merge_sort{

// merge the two haves v[l..m] and v[m+1..r] of vector v
  void sub_merge(vector<int>& v, int l, int m, int r){
    int L=m-l+1;
    vector<int> t(L);
    for(int i=0; i<L; ++i)
      t[i] = v[l+i];
    int i=0, j=m+1;
    while(i<L && j<=r)
      if(v[j]<t[i]) v[l++]=v[j++]; else v[l++]=t[i++];
    while(i<L)
      v[l++]=t[i++];
  }

  void mergeSort_iterative(vector<int>& v){
    int L=v.size();
    for(int len=1; len<L; len<<=1){ // understand len<L
      for(int hd=0; hd<L; hd+=2*len){
        int mi=hd+len-1, tl=min(mi+len, L-1);
        sub_merge(v, hd, mi, tl);
      }
    }
  }

  void mergeSort_recursive(vector<int>& v, int l=0, int r=-1){
    if (r==-1 || l < r){
      if(r<0) r=v.size()-1;
      int m = l+(r-l)/2; //Same as (l+r)/2 but avoids overflow for large l & h
      mergeSort_recursive(v, l, m);
      mergeSort_recursive(v, m+1, r);
      sub_merge(v, l, m, r);
    }
  }

  void test(){
    vector<int> v={4,5,1,258,66,75,12,8,65,4,87,63,53,8,99,54,12,34};
    {
      auto t=v, t2=t;
      mergeSort_iterative(t);
      sort(t2.begin(), t2.end());
      assert(t==t2);
    }

    {
      auto t=v, t2=t;
      mergeSort_recursive(t);
      sort(t2.begin(), t2.end());
      assert(t==t2);
    }

  }
}

#endif //LEETCODE_C_MERGE_SORT_H
