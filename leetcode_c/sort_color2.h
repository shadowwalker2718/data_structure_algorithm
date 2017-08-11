//
// Created by root on 7/7/17.
//
#ifndef LEETCODE_C_SORT_COLOR2_H

#include <henry.h>
#include <climits>

namespace _sort_color2{

  // [2,5,5,5,5,5,3,3]
  void rainbow_sort(vector<int>& v){
    int i=0, t=0;
    while(i<v.size()){
      if(v[i]<0) ++i;
      else if(v[v[i]-1]>0){
        t=v[i], v[i]=v[t-1], v[t-1]=-1;
      }else if(v[v[i]-1]==INT_MIN){
        v[v[i]-1]=-1, v[i++]=INT_MIN;
      }else
        --v[v[i]-1], v[i++]=INT_MIN;
    }
    t=i=v.size()-1;
    while(i>=0){
      if(v[i]==INT_MIN) --i;
      else {
        int j = -v[i];
        while(j--) v[t--]=i+1;
        i=min(i,t);
      }
    }
    //copy(v.begin(),v.end(), ostream_iterator<int>(cout,","));
    //cout << endl;
  }
  void sortColors2(vector<int> &v, int k) {
    // write your code here
    int i=0, t=0;
    while(i<v.size()){
      if(v[i]<0) ++i;
      else if(v[v[i]-1]>0)
        t=v[i], v[i]=v[t-1], v[t-1]=-1;
      else if(v[v[i]-1]==INT_MIN)
        v[v[i]-1]=-1, v[i++]=INT_MIN;
      else
        --v[v[i]-1], v[i++]=INT_MIN;
    }
    t=i=v.size()-1;
    while(i>=0){
      if(v[i]!=INT_MIN){
        int j = -v[i];
        while(j--) v[t--]=i+1;
      }
      i--;
    }
  }


  class Solution2 {
  public:
    string solveEquation(string e) {
      int L=e.size();
      stack<int> s1, s2;
      string t;
      int hd=0;
      if(e.front()=='-') t="-",hd=1;
      else if(e.front()=='+') hd=1;
      int sign=1;
      for(int i=hd;i<L;++i){
        if(e[i]=='+' || e[i]=='-'||e[i]=='='){
          if(t.back()=='x'){
            t.pop_back();
            int k=0;
            if(t.empty()||t=="+") k=1*sign;
            else if(t=="-") k=-1*sign;
            else k=sign*stoi(t);

            if(s1.empty())
              s1.push(k);
            else{
              k+=s1.top();
              s1.pop(), s1.push(k);
            }
          }else{
            if(t==""){t=e[i]; continue;}
            int k=sign*stoi(t);
            if(s2.empty())
              s2.push(k);
            else{
              k+=s2.top();
              s2.pop(), s2.push(k);
            }
          }
          if(e[i]=='+' || e[i]=='-')
            t=e[i];
          else
            t="", sign=-1;
        }else
          t+=e[i];
      }
      //cout << t << endl;
      if(t.back()=='x'){
        t.pop_back();
        int k=0;
        if(t.empty()||t=="+") k=1*sign;
        else if(t=="-") k=-1*sign;
        else k=sign*stoi(t);

        if(s1.empty())
          s1.push(k);
        else{
          k+=s1.top();
          s1.pop(), s1.push(k);
        }
      }else if(!t.empty()){
        int k=sign*stoi(t);
        if(s2.empty())
          s2.push(k);
        else{
          k+=s2.top();
          s2.pop(), s2.push(k);
        }
      }

      if(s1.size() and s2.size() and s1.top()==0 and s2.top()==0)
        return "Infinite solutions";

      if(s1.size() and s1.top()){
        if(s2.empty())
          return "x=0";
        else return "x="+to_string(-s2.top()/s1.top());
      }else{
        if(s2.empty())
          return "Infinite solutions";
        else{
          return "No solution";
        }
      }
    }
  };

  class Solution3 {
  public:
    unordered_map<string,int> mp;
    int getnum(const string& s){
      if(mp.count(s)) return mp[s];
      if(s.size()==1){
        if(isdigit(s[0]) and s[0]!='0') return mp[s]=1;
        if(s[0]=='0') return mp[s]=0;
        if(s=="*") return mp[s]=9;
      } else if(s.size()==2){
        if(isdigit(s[0]) && isdigit(s[1])){
          int t=stoi(s);
          if(10<=t and t<=26) return mp[s]=1;
          else return mp[s]=0;
        }else{
          if(s=="**"){
            return mp[s]=15; // 9+6
          }else if(s[0]=='*'){
            if(7<=(s[1]-'0')) return mp[s]=1; else return mp[s]=2;
          }else if(s[1]=='*'){
            if(s[0]=='1') return mp[s]=9;
            if(s[0]=='2') return mp[s]=6;
            return mp[s]=0;
          }
        }
      }
      return mp[s]=0;
    }
    int getdp(string s, int l){
      if(dp[l]>0) return dp[l];
      if(l<=1) return dp[l]=getnum(s.substr(0,1));
      if(l==2) return dp[l]=(getnum(s.substr(0,2)) +
          getnum(s.substr(0,1)) * getnum(s.substr(1,1)));
      int i=getdp(s,l-2)*getnum(s.substr(l-2,2));
      int j=getdp(s,l-1);
      int k=getnum(s.substr(l-1,1));
      dp[l] = i+j*k;
      return dp[l];
    }

    vector<long long int> dp;
    int numDecodings(string s){
      int L=s.size();
      if(L==1) return (s=="*")?9:1;
      dp=vector<long long int>(L+1,1);
      if(s[0]=='*') dp[1]=9;
      for(int i=2;i<=L;++i){
        long long int j=dp[i-2]*getnum(s.substr(i-2,2));
        long long int k=dp[i-1]*getnum(s.substr(i-1,1));
        dp[i] = j+k;
      }
      return dp.back()%1000000007;
    }

  };

  class Solution {
  public:
    double findMaxAverage(vector<int>& nums, int k) {
      long long int sum=0, r=INT_MIN;
      vector<long long int> ss(nums.size());
      for(int i=0;i<nums.size();++i){
        if(i<=k-1){
          sum+=nums[i];
          if(i==k-1) ss[i]=r=sum;
        }else{
          sum+=nums[i]-nums[i-k], r=max(r,sum), ss[i]=sum;
        }
      }
      int i=k;
      double y=double(r)/k;
      while(i<nums.size()){
        long long int x=INT_MIN, t=ss[i-1], u;
        for(int j=i;j<nums.size();j++)
          u=ss[j], ss[j]=t + nums[j], x=max(x,ss[j]), t=u;
        if(double(x)/(i+1) > y) y = double(x)/(i+1);
        i++;
      }
      return y;
    }
  };

  struct AutocompleteSystem {
    AutocompleteSystem(const vector<string>& sentences, const vector<int>& times) {
      for (int i = 0, n = sentences.size(); i < n; ++i)
        table.emplace(sentences[i], times[i]);
    }
    vector<string> input(char c) {
      if (c == '#') {
        ++table[mystr], mystr.clear();
        return vector<string>();
      }
      mystr.push_back(c);
      string end = mystr + "~"; // ~ is the last in ascii table
      auto b = table.lower_bound(mystr), e = table.upper_bound(end); //
      map<int, set<string>, greater<int>> show;
      for (; b != e; ++b)
        show[b->second].insert(b->first);
      vector<string> r;
      for (auto& pr : show) {
        for (auto& s : pr.second) {
          r.push_back(s);
          if (r.size() >= 3) return r;
        }
      }
      return r;
    }
    string mystr;
    map<string, int> table;
  };


  class Solution22{
  public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
      vector<int> r(n);
      stack<pair<int, int>> stk;

      for(string s: logs){
        auto p=s.find_first_of(':');
        int idx=stoi(s.substr(0,p));
        s.erase(0,p+1);
        if(s[0]=='s'){
          s.erase(0,6);
          int tm=stoi(s);
          if(!stk.empty()){
            pair<int,int>& pr=stk.top();
            r[pr.first]+=tm-pr.second;
            pr.second=-1;
          }
          stk.push({idx,tm});
        }else{ // end
          s.erase(0,4);
          int tm=stoi(s);
          pair<int,int>& pr=stk.top();
          r[pr.first]+=tm-pr.second+1;
          stk.pop();
          if(!stk.empty()){
            stk.top().second = tm+1;
          }
        }
      }
      return r;
    }
  };

  struct AutocompleteSystem2 { // 193ms
    AutocompleteSystem2(const vector<string>& sentences, const vector<int>& times) {
      for (int i = 0, n = sentences.size(); i < n; ++i)
        m.emplace(sentences[i], times[i]);
    }
    vector<string> input(char c) {
      if (c == '#') {
        ++m[data], data.clear();
        return vector<string>();
      }
      data.push_back(c);
      auto b = m.lower_bound(data), e = m.upper_bound(data + "~"); // O(LogN)
      vector<string> v;
      auto f=[&](string& s1, string& s2) ->bool {return m[s1] > m[s2] || (m[s1] == m[s2] && s1<s2);};
      //for_each(b,e,[&v](pair<string,int>& pr){v.emplace_back(pr.first);});
      for (; b != e; ++b) /*O(M)*/ v.emplace_back(b->first); // O(LogM)
      if(v.size()<3){
        sort(v.begin(), v.end(), f);
        return v;
      }
      nth_element(v.begin(), v.begin()+2, v.end(), f);
      sort(v.begin(),v.begin()+3,f);
      return vector<string>(v.begin(), v.begin()+3);
    }
    string data;
    map<string, int> m;
  };

  void operator+=(vector<int> &a, const vector<int> &b) {
    for (int i = 0; i < a.size(); i++)
      a[i] += b[i];
  }
  void operator-=(vector<int> &a, const vector<int> &b) {
    for (int i = 0; i < a.size(); i++)
      a[i] -= b[i];
  }
  bool operator<(const vector<int> &a, const int &n) {
    for (int i : a)
      if (i < n)
        return true;
    return false;
  }
  int operator*(const vector<int> &a, const vector<int> &b) {
    int res = 0;
    for (int i = 0; i < a.size(); i++)
      res += a[i] * b[i];
    return res;
  }
  class Solution11 {
  public:
    int iii=0;
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs, int cost = 0) {
      iii++;
      if (needs < 0)
        return INT_MAX;
      int m = cost + needs * price;
      for (auto &offer : special) {
        if (cost + offer.back() >= m) // pruning
          continue;
        needs -= offer;
        m = min(m, shoppingOffers(price, special, needs, cost + offer.back()));
        needs += offer;
      }

      return m;
    }
  };

  class Solutionn {
  public:
    int subarraySum(vector<int>& nums, int k) {
      int sum=0, r=0;
      for(int i=0, j=0; i<=j && j<nums.size(); ++j){
        if(i==j && sum==k){ r++, sum=0, i++; continue; }
        sum += nums[j];
        if(sum == k){
          r++, sum -= nums[i++];
        }else if(sum > k){
          sum -= nums[i++], --j;
        }
      }
      return r;
    }
  };

  void test(){

    Solutionn slln;
    vector<int> vi={1};
    cout << slln.subarraySum(vi,0) << endl;

    //AutocompleteSystem as;
    vector<int> price={2,5};
    vector<vector<int>> special={{3,0,5},{1,2,10}};
    vector<int> needs={3,2};
    Solution11 sln;
    assert(sln.shoppingOffers(price, special, needs)==14);
    cout << sln.iii << endl;


    //Solution sln;
    /*cout << sln.numDecodings("**") << endl;
    cout << sln.numDecodings("204") << endl;
    cout << sln.numDecodings("***") << endl;*/
    /*cout << sln.solveEquation("2+2-x+x+3x=x+2x-x+x+4") << endl;
    cout << sln.solveEquation("2x=x") << endl;
    cout << sln.solveEquation("2x+3x-6x=x+2") << endl;
    cout << sln.solveEquation("x=x+2") << endl;*/

    vector<int> v{2,5,5,5,5,5,3,3};
    rainbow_sort(v);

    v={3,2,2,1,4};
    sortColors2(v, 4);
  }


}



#define LEETCODE_C_SORT_COLOR2_H

#endif //LEETCODE_C_SORT_COLOR2_H
