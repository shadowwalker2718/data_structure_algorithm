#include <henry.h>
#include "main.h"

vector<vector<long long>> multiply(const vector<vector<long long>>& l,
                                   const vector<vector<long long>>& r)
{
  vector<vector<long long>> res(2,vector<long long>(2));
  for(int i=0;i<2;++i)
    for(int j=0;j<2;++j)
        for(int k=0;k<2;++k)
          res[i][k]+=l[i][j]*r[j][k];
  return res;
}

vector<vector<long long>> matrix_power(int n){
  static vector<vector<long long>> l={{1,1},{1,0}};
  if(n==1){return l;}
  else if(n==2){
    return multiply(l, l);
  }else{
    auto res=matrix_power(n/2);
    if(n&1) {
      auto t = multiply(res, res);
      return multiply(t, l);
    }else
      return multiply(res, res);
  }
}

long long fib_BigOLogN(int n){
  if(n<3) return 1;
  vector<vector<long long>> r={{1,0}, {0,1}}; //identity matrix
  vector<vector<long long>> t={{1,1}, {1,0}}; // seed
  n-=2;
  while(n){
    if(n&1) r=multiply(r, t);
    t=multiply(t,t);
    n>>=1;
  }
  return r[0][0]+r[0][1];
}

long long fib_BigOLogN2(int n){
  if(n<3) return 1;
  auto m=matrix_power(n-2);
  return m[0][0]+m[0][1];
}

long long fib_BigON(int n){
  if(n<3) return 1;
  long long p=1LL, pp=1LL, r;
  for(int i=3; i<=n; ++i)
    r=p+pp, pp=p, p=r;
  return r;
}

///////////////////////////////////////////////////
void printDiamond(int n){
  int i=1, h=n;
  for(int i=0;i<n;++i) {
    int left=abs(h/2-i), mid=n-2*left, right=left;
    while(left--) cout << "_";
    for(int i=0;i<mid; ++i)
      if(i<=mid/2) cout<<i+1; else cout<< mid-i;
    while(right--) cout << "_";
    cout << endl;
  }
}

int NPeopleRank(int n){
  vector<vector<int>> dp(n+1, vector<int>(n+1));
  for(int i=1;i<=n;++i)
    dp[i][1]=1;
  for(int i=2;i<=n;++i)
    for(int j=2;j<=i;++j)
      dp[i][j] = (dp[i-1][j] + dp[i-1][j-1]) * j;
  int r=0;
  for(int k=1; k<=n; ++k)
    r+=dp[n][k];
  return r;
}

string getprobkey(map<string, int>& m, int t=INT_MAX){
  map<int,string> cm; //cumulative map
  int p=0;
  for(auto pr: m)
    cm[p+=pr.second]=pr.first;
  if(t==INT_MAX)
    t=rand()%p+1;
  return cm.lower_bound(t)->second;
}
void test_getprobkey(){
  map<string, int> m={{"apple",10},{"orange",20}};
  cout << getprobkey(m) << endl;
  cout << getprobkey(m, 10) << endl;
}

#define PII pair<int,int>
class Solutionx {
public:
  vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
    vector<PII> r, h;
    for(auto& b: buildings)
      h.emplace_back(b[0],-b[2])/*start*/, h.emplace_back(b[1],b[2])/*end*/;
    //sort(h.begin(), h.end());
    sort(h.begin(), h.end(), [](PII& x, PII& y){
      return x.first<y.first;
    });
    multiset<int,greater<int>> m={0};
    int prev=0;
    for(PII &p: h){
      if(p.second<0)
        m.insert(-p.second); // start... add height
      else
        m.erase(m.find(p.second)); //end...remove height
      int mx=*m.begin();
      if(prev!=mx)
        if(r.empty()||p.first<r.back().first)
          r.emplace_back(p.first, mx), prev=mx;
    }
    return r;
  }
};



int main(int argc, char** argv) {
  _indexheap::test();
  _indexheap::test2();
  
  _dijkstra::test();
  _sort_float::test();
  Solutionx sln;
  vector<vector<int>> v={{0,2,3},{2,5,3}};
  auto res=sln.getSkyline(v);
  test_getprobkey();
  _merge_sort::test();
  cout << NPeopleRank(2) << endl;
  cout << NPeopleRank(3) << endl;
  cout << NPeopleRank(4) << endl;
  printDiamond(1);
  printDiamond(3);
  printDiamond(5);

  int m=50;
  while(m--)
    cout << (fib_BigOLogN(m) == fib_BigOLogN2(m)) << endl;
  cout << (fib_BigOLogN(4)==3LL) << endl;
  cout << (fib_BigOLogN(90)==2880067194370816120LL) << endl;
  cout << (fib_BigON(90)==2880067194370816120LL) << endl;
  __llap::test();
  vector<int> vi={1,0,2,0};
  remove(vi.begin(), vi.end(), 0);
  _fb_amazing_number::test();
  _667::test();
/*_279::test();
  _418::test();
  Solutions sln;
  vector<int> v={1,2,3,3,4,5};
  cout <<(sln.isPossible(v)==1) << endl;
  _660::test();
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
  _hdu_1254::test();*/
  return 0;
}





