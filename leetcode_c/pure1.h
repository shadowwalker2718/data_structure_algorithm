//
// Created by root on 7/6/17.
//

#ifndef LEETCODE_C_PURE1_H
#define LEETCODE_C_PURE1_H

#include <henry.h>
#include <atomic>
#include <unistd.h> //sleep

namespace _pure1 {


  // input is r square; draw arc in the 1st half quadrant
  vector<pair<int,int>> draw_circle(int r2){
    vector<pair<int,int>> r;
    for(int x=1; x*x <= r2; ++x){
      for(int y=0;y<=x;++y)// y<=x in first half quadrant
        if(x*x+y*y==r2){
          r.push_back({x,y});
          break;
        }
    }
    int l=r.size();
    while(l--){
      int x=r[l].first, y=r[l].second;
      if(y) r.emplace_back(x,-y);
      if(x) r.emplace_back(-x,y);
      if(x && y) r.emplace_back(-x,-y);
      r.emplace_back(y,x);
      if(y) r.emplace_back(-y,x);
      if(x) r.emplace_back(y,-x);
      if(x && y) r.emplace_back(-y, -x);
    }
    return r;
  };

  vector<pair<int,int>> draw_circle2(int r2){
    vector<pair<int,int>> r;
    for(int x=1; x*x <= r2; ++x){
      int y0=0, y1=x, T=r2-x*x;
      while(y0<=y1){
        int m=y0+(y1-y0)/2, t=m*m;
        if(t==T){
          r.emplace_back(x,m);
          break;
        }else if(t<T)
          y0=m+1;
        else y1=m-1;
      }
    }
    int l=r.size();
    while(l--){
      int x=r[l].first, y=r[l].second;
      if(y) r.emplace_back(x,-y);
      if(x) r.emplace_back(-x,y);
      if(x && y) r.emplace_back(-x,-y);
      r.emplace_back(y,x);
      if(y) r.emplace_back(-y,x);
      if(x) r.emplace_back(y,-x);
      if(x && y) r.emplace_back(-y, -x);
    }
    return r;
  };


  vector<int> dnf_min_swap(vector<int> v){
    vector<pair<int,int>> k={{2,0},{1,0},{2,1}};
    int count=0;
    for(auto pr: k){
      int L=(int)v.size(), i=0, j=L-1;
      while(i<j){
        while(i<L and v[i]!=pr.first) i++;
        while(j>i and v[j]!=pr.second) j--;
        if(j>i){ swap(v[i],v[j]); count++;}
      }
    }
    cout << count << endl;
    return v;
  }


  static const int BATCHNUM=10;
  mutex m;
  condition_variable cv;
  vector<int> buf(BATCHNUM*2);
  atomic<int> cur{-1};
  atomic<short> update{0};

  void get_ids(int num_of_id, int* b){
    static int start=0;
    iota(b, b+num_of_id, start);
    start+=BATCHNUM;
    sleep(1);
  }
  void fill_ids(){ // one thread to write
    while(1){
      if(cur==-1){
        get_ids(BATCHNUM, &buf.front()); // 1 second
        get_ids(BATCHNUM, &buf.front()+BATCHNUM); // 1 second
        cur=0;
        cv.notify_all();
      }else{
        unique_lock<mutex> ul(m);
        while(update==0)
          cv.wait(ul); // unlock ul/m
        int* t=NULL;
        if(update>0){
          t=&buf.front()+(update-1)*BATCHNUM;
          update=0, cv.notify_all(), ul.unlock();
        }
        get_ids(BATCHNUM, t); // 1 second
      }
    }
  }
  int get_call_id(){ // multiple threads to read
    unique_lock<mutex> ul(m);
    while(cur==-1) cv.wait(ul);
    if(cur==BATCHNUM) update=1, cv.notify_one();
    if(cur==BATCHNUM*2) cur=0, update=2, cv.notify_one();
    while(update) cv.wait(ul);
    return buf[cur++];
  }

  int print_ids(){
    while(usleep(2e5)==0){
      cout << "1:" << get_call_id() << endl;
    }
  }

  void test(){

    thread t1(fill_ids);
    thread t2(print_ids);
    /*while(!usleep(1e4))
      cout << "0:" << get_call_id() << endl;
    */
    t1.join(), t2.join();


    vector<int> v= {2,0,1,0,1,2,2,0,1,0,1,2,2,0,1,0,1,2};
    v=dnf_min_swap(v);
    copy(v.begin(),v.end(),ostream_iterator<int>(cout,","));cout << endl;
    v=dnf_min_swap({2,0,1,0,1,2});
    copy(v.begin(),v.end(),ostream_iterator<int>(cout,","));cout << endl;

    assert(dnf_min_swap({}) == vector<int>({}));
    assert(dnf_min_swap({0}) == vector<int>({0}));
    assert(dnf_min_swap({1}) == vector<int>({1}));
    assert(dnf_min_swap({2}) == vector<int>({2}));
    assert(dnf_min_swap({1,1}) == vector<int>({1,1}));
    assert(dnf_min_swap({2,1,1}) == vector<int>({1,1,2}));
    assert(dnf_min_swap({1,2,1}) == vector<int>({1,1,2}));
    assert(dnf_min_swap({0,1,2}) == vector<int>({0,1,2}));

    int r2=1000000;
    auto r=draw_circle(r2);
    assert(r.size()==28);
    assert(r==draw_circle2(r2));
  }

}







#endif //LEETCODE_C_PURE1_H
