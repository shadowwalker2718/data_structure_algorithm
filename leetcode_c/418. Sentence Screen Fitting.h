//
// Created by root on 8/14/17.
//

#ifndef LEETCODE_C_418_SENTENCE_SCREEN_FITTING_H
#define LEETCODE_C_418_SENTENCE_SCREEN_FITTING_H

#include "henry.h"

namespace _418{

  struct Solution {
    int wordsTyping(vector<string>& s, int ro, int co) {
      int r=0, i=0, j=0, L=s.size(), k=0;
      while(i<=ro*co){
        while(i<=ro*co && j<L){
          int x=i+s[j].size()+(i%co!=0), y=(k+1)*co;
          if(x <= y){ i=x, j++; }else{ i=y, k++; }
        }
        if(i >ro*co) return r;
        if(i==ro*co) return r+(j==L);
        if(j==L)
          r++, j=0;
      }
      return r;
    }
  };

  class Solution2 {
/* ["a", "bcd", "e"] 3 6 */
  public:
    int wordsTyping(vector<string>& sentence, int rows, int cols) {
      unordered_map<int, int> umap;
      int num = 0, n = sentence.size();
      for(int i = 0; i < rows; i++){
        int start = num % n;
        if(umap.count(start) == 0){
          int cnt = 0, len = 0;
          for(int i = start; len < cols; i = (i+1) % n, cnt++){
            if(len + sentence[i].size() > cols)
              break;
            len += sentence[i].size() + 1;
          }
          num += cnt;
          umap.emplace(start, cnt);
        }
        else
          num += umap[start];
      }
      return num / n;
    }
  };


  void test(){
    {
      Solution sln;
      vector<string> v={"a", "bcd", "e"};
      cout << sln.wordsTyping(v,3,6) << endl;
    }

    {
      Solution2 sln;
      vector<string> v={"a", "bcd", "e"};
      cout << sln.wordsTyping(v,30,6) << endl;
    }
  }
}




#endif //LEETCODE_C_418_SENTENCE_SCREEN_FITTING_H
