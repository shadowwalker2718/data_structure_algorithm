#pragma once

#include "henry.h"

namespace _lnkd_totalcovered_length {
    struct Intervals_ { // if all values are positive
        vector<int> v;

        void addInterval(int from, int to) {
            v.emplace_back(from), v.emplace_back(-to);
        }

        int getTotalCoveredLength() {
            sort(v.begin(), v.end(), [](int i, int j) {return abs(i) < abs(j); });
            int r = 0, count = 0;
            stack<int> stk; // max size are 2
            for (int i = 0; i < v.size(); i++) {
                if (stk.empty()) { stk.push(v[i]); }
                if (v[i]>0) count++; else count--;
                if (count == 0) { r += abs(v[i]) - stk.top(); stk.pop(); }
            }
            return r;
        }
    };

    struct Intervals {
        vector<pair<int, bool>> intervals;

        void addInterval(int from, int to) {
            intervals.emplace_back(from, 1);
            intervals.emplace_back(to, 0);
        }

        int getTotalCoveredLength() {
            sort(intervals.begin(), intervals.end());
            int r = 0, count = 0;
            stack<int> stk; // max size are 2
            for (int i = 0; i < intervals.size(); i++) {
                if (stk.empty()) { stk.push(intervals[i].first); }
                if (intervals[i].second) count++; else count--;
                if (count == 0) { r += intervals[i].first - stk.top(); stk.pop(); }
            }
            return r;
        }
    };

    struct Intervals2 { // if all values are positive
        list<pair<int, int>> l;
        int sz = 0; // total length

        void addInterval(int from, int to) {
            bool merged = false;
            auto it = l.begin();
            while (it != l.end()) {
                if (to < it->first) {
                    if (!merged) {
                        l.insert(it, { from,to });
                        sz += to - from;
                        merged = true;
                        break;
                    }
                } else if (from > it->second) {
                } else {
                    from = min(from, it->first), to = max(to, it->second);
                    sz -= (it->second - it->first);// +(to - from);
                    it = l.erase(it); //https://goo.gl/gqhnT
                    continue;
                }
                it++;
            }
            if (!merged) { l.push_back({ from,to }); sz += to - from; }
        }

        int getTotalCoveredLength() {
            return sz;
        }
    };

    struct raindrop{
        list<pair<double, double>> l;
        const double RAIN_LEN=0.01;
        const pair<double,double> ROAD{-0.01,1};
        double sz=0.0;
        bool fullycovered(){
            return sz>=1.0; //return abs(sz-1.0)<1e-10;
        }
        bool drop(double start, double end){
            bool merged=false;
            list<pair<double, double>>::iterator it=l.begin();
            while(it != l.end()){
                if(it->first > end){
                    if(!merged){
                        l.insert(it,{start, end});
                        sz += end-start;
                        merged=true;
                        break;
                    }else{}
                }else if(it->second<start){
                }else{ // overlap
                    start=min(start,it->first), end=max(end, it->second);
                    sz -= (it->second - it->first);
                    it = l.erase(it);
                    continue;
                }
                ++it;
            }
            if(!merged){
                sz += end-start;
                l.push_back({start, end});
            }
            return fullycovered();
        }
        // >>> math.log(101)* 101 == 466.1271722009672
        int simulate(){
            srand(time(NULL));
            int r=0;
            double start;
            do{
                r++;
                // be careful start should be {-0.01, 1-0.01=0.99}
                start = (rand()%101 -1)/100.0;// generate x=(0-100) then (x-1)/100.0
            }while(!drop(start, start+RAIN_LEN));
            return r;
        }
    };

    void test() {

        raindrop rd;
        cout << "How many times:" << rd.simulate() << endl;

        for (int x = 0; x < 100; ++x) {
            srand(time(0));
            int i = rand() % (1000 - 100) + 100;//100-1000
            vector<pair<int, int>> ps;
            while (i--) {
                int from = (rand()%1000), to = (rand()%1000) % 100;
                while(to==0) to = rand() % 200;
                while(from == 0) from = rand()%1001;
                ps.push_back({ from, from + to });
            }

            Intervals v;
            Intervals2 v2;
            for (auto pr : ps) {
                v.addInterval(pr.first, pr.second);
                v2.addInterval(pr.first, pr.second);
            }
            cout << v.getTotalCoveredLength() << endl;
            cout << v2.getTotalCoveredLength() << endl;
            assert(v.getTotalCoveredLength() == v2.getTotalCoveredLength());
        }
        
        {
            Intervals v;
            v.addInterval(3, 6);
            v.addInterval(8, 9);
            v.addInterval(1, 5);
            assert(v.getTotalCoveredLength() == 6);
        }

        {
            Intervals2 v;
            v.addInterval(3, 6);
            v.addInterval(8, 9);
            v.addInterval(1, 5);
            assert(v.getTotalCoveredLength() == 6);
        }
    }
}