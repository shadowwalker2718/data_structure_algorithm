#pragma once

#include "henry.h"

namespace minwindowsub {
    struct Solution {
        string minWindow(string s, string t) {
            unordered_map<char, int> mp;
            for (char now : t) mp[now] ++; // counter

            int count = mp.size(); // unique char #
            int j = 0, ans = INT_MAX;
            string res;
            for (int i = 0; i < s.size(); i++) { // loop through s
                if (mp.count(s[i]) == 0) { continue; }
                while (count && j < s.size()) {
                    if (mp.count(s[j]) == 0) {
                        j++; continue;
                    }
                    mp[s[j]]--;
                    if (mp[s[j]] == 0) count--;
                    j++;
                    if (count == 0) break;
                }
                if (count == 0)
                    if (j - i< ans)
                        ans = j - i, res = s.substr(i, ans);
                if (mp[s[i]] == 0)
                    count++;
                mp[s[i]]++;
            }
            return res;
        }
    };

    struct Solution2 {
      string minWindow(string s, string t) {
        int m[128] = {};
        //unordered_map<char, int> m;
        for (auto c : t) m[c]++; // m is a dynamic counter
        int counter = t.size(), head = 0, cur = 0, len = INT_MAX, h = 0;
        while (cur<s.size()) {
          if (m[s[cur]]>0)
            counter--; //in t
          m[s[cur]]--;
          //cur++;
          while (counter == 0) { //valid window is found
            if (cur - head < len) {
              h = head;
              len = cur - head + 1;
            }
            //开始挪窗口的起始点
            if (m[s[head]] == 0) {
              counter++;  //make it invalid
            }
            m[s[head]]++;
            head++;
          }
          cur++;
        }
        return len == INT_MAX ? "" : s.substr(h, len);
      }
    };

    void test() {
        Solution2 sln2;
        assert(sln2.minWindow("xacbbaxca", "aba") == "baca");
        Solution sln;
        assert(sln.minWindow("acbbaca","aba")=="baca");
    }
}

