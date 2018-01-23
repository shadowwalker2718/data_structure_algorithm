#pragma once

#include "henry.h"

namespace _indexheap {

#define PAR(i) ((i-1)/2) // 2n-2
#define LEF(i) (i*2+1) // 2n+1, 1->3, 1->4
#define RIG(i) (i*2+2) // 2n+2, 2->5, 2->6

  struct index_priority_queue {
    vector<int> volumes; // 100 items
    unordered_map<int, string> index2ticker;
    unordered_map<string, int> ticker2index;
    int _size = 0;

    index_priority_queue(int hsize = 100) { volumes.resize(hsize); }
    void push(string s, int v) { // O(LogN)
      volumes[_size] = v;
      index2ticker[_size] = s;
      ticker2index[s] = _size;
      int cindex = _size;
      int pindex = PAR(_size);
      while (pindex >= 0 && volumes[pindex]<volumes[cindex]) {
        __swap(cindex, pindex);// swap with its parent
        cindex = pindex;
        pindex = PAR(pindex);
      }
      ++_size;
    }
    // ix - index1, iy - index2
    void __swap(int ix, int iy) {
      std::swap(volumes[ix], volumes[iy]);
      std::swap(ticker2index[index2ticker[ix]], ticker2index[index2ticker[iy]]);
      std::swap(index2ticker[ix], index2ticker[iy]);
    }
    // update can be decrease or increase ??
    void update(string ticker, int new_volume) { // O(LogN)
      if (ticker2index.find(ticker) == ticker2index.end()) {
        push(ticker, new_volume);
        return;
      }
      int cur_idx = ticker2index[ticker]; // current index
      volumes[cur_idx] = new_volume;
      // 1. increment - swap with its parent (sift update)
      int pindex = PAR(cur_idx);
      while (pindex >= 0 && volumes[pindex] < volumes[cur_idx]) { // LogN
        __swap(cur_idx, pindex);
        cur_idx = pindex;
        pindex = PAR(pindex);
      }
      // 2. decrement - swap with the bigger of its children (sift down)
      int greater_lc_rc = -1;
      while (1) { // LogN
        int lc = LEF(cur_idx), rc = RIG(cur_idx);
        if (rc<_size) {
          greater_lc_rc = (volumes[lc] > volumes[rc]) ? lc : rc;
        } else if (rc == _size) {
          greater_lc_rc = lc;
        } else break;
        if (greater_lc_rc>0 && volumes[cur_idx]<volumes[greater_lc_rc]) {
          __swap(cur_idx, greater_lc_rc);
          cur_idx = greater_lc_rc;
        } else break;
      }
    }
    // Get topK from heap with help of a new size-k heap in O(KLogK)
    void topK(int k) { // O(KLogK) where K==10
      vector<pair<string, int>> vp;
      priority_queue<pair<int,int>> pq; // pair of {volume, index}
      pq.push({volumes[0],0});
      while (k-- && !pq.empty()) {
        auto pr = pq.top(); pq.pop(); // LogK
        vp.emplace_back(index2ticker[pr.second],volumes[pr.second]);
        int lc = LEF(pr.second), rc = RIG(pr.second);
        if (lc<_size) pq.emplace(volumes[lc], lc); // LogK
        if (rc<_size) pq.emplace(volumes[rc], rc);
      }
      for_each(vp.begin(), vp.end(), [](const pair<string, int>& p) {
        if (p.first.empty()) return;
        cout << p.first << "-" << p.second << endl;
      });
    }
  };

  struct stock {
    string ticker;
    int volume;
  };

  class index_heap {
    vector<stock> stocks;// heap core data
    unordered_map<string, int> ticker2index;

    void __swap(int x, int y) {
      std::swap(ticker2index[stocks[x].ticker],
                ticker2index[stocks[y].ticker]);
      std::swap(stocks[x], stocks[y]);
    }
    void __sift_up_old(int idx) { // iterative
      if (idx >= stocks.size()) return;
      int pidx = (idx-1)/2;
      while (pidx >= 0 && stocks[pidx].volume < stocks[idx].volume) {
        __swap(idx, pidx);
        idx = pidx, pidx = (idx-1)/2;
      }
    }
    void __sift_up(int idx) { // iterative
      if (idx >= stocks.size()) return;
      stock t=stocks[idx];
      while (idx > 0 && stocks[(idx-1)/2].volume < t.volume) {
        stocks[idx] = stocks[(idx-1)/2], ticker2index[stocks[idx].ticker]=idx;
        idx = (idx-1)/2;
      }
      stocks[idx] = t, ticker2index[stocks[idx].ticker]=idx;
    }
    void __sift_down(int idx) { // recursive
      if (idx >= stocks.size()) return;
      int lchild = 2 * idx + 1, rchild = 2 * idx + 2;
      if (stocks.size() > rchild) {
        if (stocks[lchild].volume > stocks[rchild].volume) {
          if(stocks[idx].volume < stocks[lchild].volume){
            __swap(idx, lchild), __sift_down(lchild);
          }
        } else {
          if(stocks[idx].volume < stocks[rchild].volume){
            __swap(idx, rchild), __sift_down(rchild);
          }
        }
      } else if (stocks.size() > lchild) {
        if(stocks[idx].volume < stocks[lchild].volume){
          __swap(idx, lchild), __sift_down(lchild);
        }
      } else return;
    }
  public:
    index_heap(){}
    index_heap(const vector<stock>& s){
      stocks=s;
      for(int i=0;i<s.size();++i)
        ticker2index[stocks[i].ticker]=i;
      for (int tmp=(stocks.size()+1)/2; tmp>=0; tmp--)
        __sift_down(tmp);
    }
    void push(const stock& s) {
      stocks.push_back(s);
      ticker2index[s.ticker] = stocks.size() - 1;
      __sift_up(stocks.size() - 1);
    }
    void increase_volume(const string& t, int vol) {
      stocks[ticker2index[t]].volume += vol;
      __sift_up(ticker2index[t]);
    }
    void decrease_volume(const string& t, int vol) {
      stocks[ticker2index[t]].volume -= vol;
      __sift_down(ticker2index[t]);
    }
    vector<stock> topK(int k) {
      vector<stock> r;
      if (stocks.empty()) return r;
      auto comp = [&](stock& s1, stock& s2) { return
        stocks[ticker2index[s1.ticker]].volume
        < stocks[ticker2index[s2.ticker]].volume; };
      priority_queue<stock,vector<stock>, decltype(comp)> pq(comp);//!!
      pq.push(stocks[0]);
      while (k-- && !pq.empty()){
        stock tmp = pq.top(); pq.pop();
        r.push_back(tmp);
        int lchild = 2 * ticker2index[tmp.ticker] + 1,
          rchild = 2 * ticker2index[tmp.ticker] + 2;
        if (lchild<stocks.size()) pq.push(stocks[lchild]);
        if (rchild<stocks.size()) pq.push(stocks[rchild]);
      }
      return r;
    }
    // https://goo.gl/Vg64Pi
    friend ostream& operator<<(ostream& os, const index_heap& ih){
      int i=0;
      for(auto& pr: ih.ticker2index)
        os << i++ << ". "<< pr.first << "-" << pr.second << endl;
      return os;
    }
  };

  int test() {
    index_priority_queue h;
    vector<pair<string, int>> data = { { "FB",102 }, { "GOOG", 101 },
                                       { "AMZ", 103 },{ "IBM", 100 },
                                       { "UB", 105 }, { "LNKD", 104 },
                                       { "BIDU", 106 },{ "BBG",210 },
                                       { "MSFT",321 },{ "UBER", 268 },
                                       { "YHOO",12 },{ "AAPL",234 },
                                       { "TWTR",160 },{"EBAY",89} };
    for (auto& pr : data) h.push(pr.first, pr.second);
    h.topK(20);
    cout << "******************" << endl;
    h.topK(5);
    cout << "******************" << endl;
    h.update("FB", 2500);
    h.topK(3);
    cout << "******************" << endl;
    h.update("FB", 20);
    h.topK(3);
    cout << "******************" << endl;
    h.update("BBG", 2000);
    h.topK(3);
    cout << "******************" << endl;
    return 0;
  }


  void test2() {
    vector<stock> data = { { "FB",102 },{ "GOOG", 101 },
                           { "AMZ", 103 },{ "IBM", 100 },
                           { "UB", 105 },{ "LNKD", 104 },
                           { "BIDU", 106 },{ "BBG",210 },
                           { "MSFT",321 },{ "UBER", 268 },
                           { "YHOO",12 },{ "AAPL",234 },
                           { "TWTR",160 },{ "EBAY",89 } };
    index_heap ih(data);
    cout << ih;
    auto r = ih.topK(5);
    for (auto s : r) { cout << s.ticker << "-" << s.volume << endl; }
    cout << "******************" << endl;
    ih.increase_volume("FB",2500-102);
    r = ih.topK(5);
    for (auto s : r) { cout << s.ticker << "-" << s.volume << endl; }
    cout << "******************" << endl;
    ih.increase_volume("BBG",2000-210);
    r = ih.topK(5);
    for (auto s : r) { cout << s.ticker << "-" << s.volume << endl; }
  }
}
