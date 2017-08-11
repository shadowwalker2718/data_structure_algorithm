#include <henry.h>
#include "main.h"

int Longest_Arithmetic_Progression(vector<int> &A) {
  int L=A.size(), len=2;
  if(L<=2) return L;
  vector<vector<int>> dp(L,vector<int>(L, 2));
  for(int j=L-2; j>=1; --j){
    int i=j-1, k=j+1;
    while(i>=0 && k<=L-1){
      if(A[i]-A[j]+A[k] < A[j]) k++;
      else if(A[i]-A[j]+A[k] > A[j]) dp[i][j]=2, i--;
      else{
        dp[i][j] = dp[j][k]+1;
        len=max(len, dp[i][j]);
        i--, k++;
      }
    }
    while(i>=0){ dp[i][j]=2, i--; }
  }
  return len;
}



int main(int argc, char** argv) {
  _621::test();
  _621::test2();
  _632::test();
  _sort_color2::test();
  _pure1::test();
  _google_int_compress::test();
  _630::test();
  _lnkd_totalcovered_length::test();
  _shortest_non_substring::test();
  _RLEIterator::test();
  _frequent_element::test();
  minwindowsub::test();
  _68_2::test();
  _comb_sum::test();
  _canPlaceFlower::test();
  _winner_tree::test();
  _reverse_string::test();
  _sparsematrix::test();
  _kangaroos::test();
  _254::test();
  _concurrent_hashmap::test();
  _find_dup::test();
  _knighttour::test();
  segregate_even_odd_ll::test();
  blowoff_leaf::test();
  _minmaxstack::test();
  K_th_Smallest_in_Lexicographical_Order::test();
  bbg_encode_list_with_dups::test();
  _multi_dimension_array::test();
  _lnkd_is_intersected::test();
  _lfu::test();
  justify_text_line::test();
  _delayqueue::test();
  _print_matrix::test();
  _allLPS::test();
  _h2o::mainthread2();
  _h2o::test();
  _34::test();
  deadlock::test();
  _linkedin::test();
  _149::test();
  _skiplist::test();
  _indexheap::test();
  _indexheap::test2();
  google::test();
  _lnkd_is_serialized_tree::test();
  _midstack::test();
  _65::test();
  _68::test();
  _214::test();
  _361::test();
  _42::test();
  _42::test2();
  _208::test();
  _208_ext::test();
  _391::test();
  _394::test();
  _388::test();
  _307::test();
  _425::test();
  _425::test2();
  _425::test3();
  _422::test();
  _407::test();
  _bzoj1090::test();
  _ksum::test();
  _hdu_1254::test();
  return 0;
}





