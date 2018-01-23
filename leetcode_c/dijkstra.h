//
// Created by root on 12/28/17.
//

#ifndef LEETCODE_C_DIJKSTRA_H
#define LEETCODE_C_DIJKSTRA_H

#pragma once

#include "henry.h"


namespace _dijkstra{
  // not dijkstra

  /*
    8,9,7,6,9,
    2,7,8,2,3,
    3,0,3,4,9,
    7,9,1,5,2,
    9,8,5,9,5,
    */

  static int BSIZE=5;
  static vector<vector<int>> board(BSIZE);



  vector<pair<int,int>> dirs={
    {1,0},{0,1},{-1,0},{0,-1}
  };
  int effort(const vector<vector<int>>& v){
    if (v.empty() || v[0].empty()) return 0;
    int R=v.size(), C=v[0].size();
    vector<vector<int>> t(R, vector<int>(C, INT_MAX));
    t[0][0]=0;
    for(int i=0;i<R;++i){
      for(int j=0;j<C;++j){
        for(auto p: dirs){
          int ni=i+p.first, nj=j+p.second;
          if(ni>0 && ni<R && nj>0 && nj<C){
            t[ni][nj] = min(t[i][j] + abs(v[ni][nj]-v[i][j]), t[ni][nj]);
          }
        }
      }
    }
    return t[R-1][C-1];
  }

  bool test2(){
    for(int i=0;i<BSIZE;i++){
      srand(i+time(0));
      for(int j=0;j<BSIZE;++j){
        board[i].push_back(rand()%10);
      }
    }

    for(int i=0;i<BSIZE;i++){
      for(int j=0;j<BSIZE;++j){
        cout << board[i][j] << ",";
      }
      cout << endl;
    }

    cout << effort(board) << endl;
  }

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
  int minDistance(vector<int>& dist, vector<bool>& sptSet) {
    int min_ = INT_MAX, min_index = -1, sz = dist.size();
    for (int v = 0; v < sz; v++)
      if (!sptSet[v] && dist[v] <= min_)
        min_ = dist[v], min_index = v;
    return min_index;
  }
// A utility function to print the constructed distance array
  int printSolution(vector<int>& dist, int n) {
    printf("Vertex Distance from Source:\n");
    for (int i = 0; i < dist.size(); i++)
      printf("%d -> %d\n", i, dist[i]);
  }
// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
  void dijkstra(vector<vector<int>>& graph, int src) {
    int sz = graph.size();
    vector<int> dist(sz, INT_MAX);
    vector<bool> sptSet(sz, false);// shortest path tree
    // Distance of source vertex from itself is always 0
    dist[src] = 0;
    // Find shortest path for all vertices
    for (int count = 0; count < sz - 1; count++) {
      // Pick the minimum distance vertex from the set of vertices not
      // yet processed. u is always equal to src in first iteration.
      int u = minDistance(dist, sptSet);
      // Mark the picked vertex as processed
      sptSet[u] = true;
      // Update dist value of the adjacent vertices of the picked vertex.
      for (int v = 0; v < sz; v++)
        // Update dist[v] only if is not in sptSet, there is an edge from
        // u to v, and total weight of path from src to  v through u is
        // smaller than current value of dist[v]
        if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
            && dist[u] + graph[u][v] < dist[v])
          dist[v] = dist[u] + graph[u][v];
    }
    // print the constructed distance array
    printSolution(dist, sz);
  }
  // driver program to test above function
  int test() {
    /* Let us create the example graph discussed above */
    vector<vector<int>> graph =
      {{0, 4, 0, 0, 0, 0, 0, 8, 0},
       {4, 0, 8, 0, 0, 0, 0, 11, 0},
       {0, 8, 0, 7, 0, 4, 0, 0, 2},
       {0, 0, 7, 0, 9, 14,0, 0, 0},
       {0, 0, 0, 9, 0, 10, 0, 0, 0},
       {0, 0, 4, 14, 10, 0, 2, 0, 0},
       {0, 0, 0, 0, 0, 2, 0, 1, 6},
       {8, 11, 0, 0, 0, 0, 1, 0, 7},
       {0, 0, 2, 0, 0, 0, 6, 7, 0}
      };
    dijkstra(graph, 0);
    return 0;
  }

}

#endif //LEETCODE_C_DJKISTRA_H
