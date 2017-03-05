#pragma once

#include "henry.h"

namespace _minstack {

  class minstack {
    priority_queue<int,vector<int>,greater<int>> Q;
    list<int> l;
  public:

    minstack() {}

    void push(int i) {
      l.push_back(i);
      Q.push(i);
    }
    

  };

}