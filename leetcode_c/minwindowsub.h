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

    void test() {
        Solution sln;
        assert(sln.minWindow("acbbaca","aba")=="baca");
    }
}

