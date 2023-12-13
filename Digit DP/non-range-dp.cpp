// Problem link: https://codeforces.com/problemset/problem/1143/B

#include <bits/stdc++.h>
using namespace std;

long long dp[10][2][2];

long long sol (int pos, bool equal, bool consec_zero, string& num) { 
  if (pos == (int) num.size()) { 
    return 1LL;
  }
  long long& cur_ans = dp[pos][equal][consec_zero];
  if (cur_ans != -1) { 
    return cur_ans;
  }
  cur_ans = 0;
  int max_dig = equal ? num[pos] - '0' : 9;
  for (int dig = 0; dig <= max_dig; ++dig) { 
    cur_ans = max(cur_ans, (consec_zero and dig == 0 ? 1 : dig) * sol(pos + 1, equal and num[pos] - '0' == dig, consec_zero and dig == 0, num));
  }
  return cur_ans;
}

int main () { 
  int n;
  cin >> n;
  string num = to_string(n);
  memset(dp, -1, sizeof dp);
  cout << sol(0, true, true, num) << '\n';
  return 0;
}
