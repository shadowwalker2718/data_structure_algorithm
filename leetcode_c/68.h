#pragma once

#include "henry.h"

namespace _68_2 {

  vector<string> fullJustify(vector<string>& words, int maxWidth) {
    vector<string> r;
    
    int k = 0;
    while (k <= words.size()) {
      int l = 0;
      int i = k;
      string t;
      while (l <= maxWidth)
        l += words[k].size()+1, k++;
      l -= words[--k].size()-1;
      int spaces = maxWidth - l;
      int gap = k - i - 1;
      for (int j=0; j<gap; j++)
        t += words[i];

    }
    return r;
  }


  void test() {
    vector<string> vs = { "This", "is", "an", "example", "of", "text", "justification." };
    auto r=fullJustify(vs, 16);
    for (auto s : r) {
      cout << s << endl;
    }
  }

}