#pragma once
#include "henry.h"

namespace _68 {

    struct Solution { // 0ms
        vector<string> fullJustify(vector<string>& words, int maxWidth) {
            vector<string> result;
            for (int i = 0, m, n; i< words.size(); i += m) {//n:该行单词长度和，m:该行单词数目
                for (m = 0, n = 0; i + m<words.size() && m + n + words[i + m].size() <= maxWidth; m++)
                    n += words[i + m].size();
                string str = words[i];
                int gib = m - 1, spaces = maxWidth - n, lastline = 0;//gib:gap_in_between, spaces:需要填的空格的数目
                for (int j = 0; j < gib; j++) {
                    if (i + m >= words.size()) //last line
                        str.append(" "), lastline = 1;
                    else
                        str.append(spaces / gib + (j<spaces%gib), ' ');
                    str += words[i + j + 1];
                }
                if (gib == 0 || lastline) str.append(maxWidth - str.size(), ' ');// for gib==0 or lastline
                result.push_back(str);
            }
            return result;
        }
    };

    void test() {
        Solution sln;
        vector<string> v({ "This", "is", "an", "example", "of", "text", "justification."});
        assert(sln.fullJustify(v, 16) ==
            vector<string>({"This    is    an",
                            "example  of text",
                            "justification.  " }));

    }
}