//
// Created by root on 9/5/17.
//

#ifndef LEETCODE_C_LLAP_H
#define LEETCODE_C_LLAP_H

#include <henry.h>

namespace __llap{

  int LLAP(const vector<int> &A) {
    int L=A.size(), len=2;
    if(L<=2) return L;
    vector<vector<int>> dp(L,vector<int>(L, 2));
    for (int i = 0; i < L; i++)
      dp[i][L-1] = 2;
    for(int j=L-2; j>=1; --j){
      int i=j-1, k=j+1;
      while(i>=0 && k<=L-1){
        if(A[i]-A[j]+A[k] < A[j]) k++;
        else if(A[i]-A[j]+A[k] > A[j]) i--;
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

  void test(){
    vector<int> v={729652,1382614,740882302,688260158,2035576,2688538,879350478,3341500,3994462,4647424,5300386,174780165,
      902753309,67221396,261170013,5953348,20981554,697413800,634979324,6606310,7259272,7912234,8565196,365426960,
      9218158,9871120,10524082,214497117,780770428,33203066,530134298,207525479,339378323,108777178,466377836,
      135845030,338758184,16429964,614474430,366933075,974577226,276742682,124388355,808614382,721196653,221239448,
      7325136,544225976,564151016,573481752};
    int mi = *min_element(v.begin(), v.end());
    sort(v.begin(), v.end());
    for(int i=0;i<v.size();++i){
      v[i]-=mi;
      cout << v[i] << ",";
    }
    cout << endl;
    cout << LLAP(v) << endl;
  }

}

#endif //LEETCODE_C_LLAP_H
