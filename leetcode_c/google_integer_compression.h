//
// Created by root on 7/5/17.
//

#ifndef LEETCODE_C_GOOGLE_INTEGER_COMPRESSION_H
#define LEETCODE_C_GOOGLE_INTEGER_COMPRESSION_H

#include <henry.h>

namespace _google_int_compress{

  vector<char> _serialize(int i){
    int k=4;
    while(k){
      if((i >> k*7)!=0) break;
      k--;
    }
    if(k==0) return {0};
    vector<char> r(k+1, 1<<7);
    r[0] = 0;
    for(int j=0;j<=k;++j)
      r[j] |= ((i & (127<<j*7)) >> j*7);
    reverse(r.begin(), r.end());
    return r;
  }

  vector<char> serialize(vector<int> is){
    vector<char> r;
    for(int i: is){
      vector<char> t=_serialize(i);
      r.insert(r.end(), t.begin(), t.end());
    }
    return r;
  }

  vector<int> deserialize(vector<char> v){
    vector<int> r;
    int i=0;
    for(char c: v){
      i <<= 7, i |= (c & 127);
      if(!(c & 128)){
        r.push_back(i), i=0;
      }
    }
    return r;
  }

  void test(){
    srand(time(0));
    vector<int> v;
    while(v.size()<10000){
      //v.push_back(rand()%10000*((v.size()&1)?-1:1));
      v.push_back(rand()%10000);
    }
    vector<char> o=serialize(v);
    assert(deserialize(o) == v);
    assert(serialize({0b10000000}) == vector<char>({(char)(0b10000001), '\0'}));
    assert(serialize({0b0}) == vector<char>({'\0'}));
    assert(deserialize(serialize({128,1212312,-1})) == vector<int>({128,1212312,-1}));
  }

}



#endif //LEETCODE_C_GOOGLE_INTEGER_COMPRESSION_H
