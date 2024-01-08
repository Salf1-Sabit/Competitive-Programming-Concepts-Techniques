// Topic: DP + MEX
// Rating: 1600
// Problem link: https://codeforces.com/contest/1875/problem/D

#include <bits/stdc++.h>
using namespace std;

const int N = (int) 5e3 + 1;
int cnt[N];
long long dp[N][N];

long long sol (int cur, int mex) { 
  if (mex == 0) { 
    return 0LL;
  }
  if (cur == 0) { 
    return (cnt[cur] - 1) * 1LL * mex;
  }
  long long& ans = dp[cur][mex];
  if (ans != -1) { 
    return ans;
  }
  return ans = 1LL * min(sol(cur - 1, mex), 
                         sol(cur - 1, cur) + (cnt[cur] - 1) * 1LL * mex + cur);
}

int main () { 
  int tt;
  cin >> tt;
  while (tt--) { 
    int n;
    cin >> n;
    for (int x = 0; x <= n; ++x) { 
      cnt[x] = 0;
      for (int y = 0; y <= n; ++y) { 
        dp[x][y] = -1;
      }
    }
    vector<int> a(n);
    for (auto& x : a) { 
      cin >> x;
      if (x <= n) { 
        cnt[x]++;
      }
    }
    int mex = 0;
    while (cnt[mex]) { 
      ++mex;
    }
    cout << sol(mex - 1, mex) << '\n';
  }
  return 0;
}


