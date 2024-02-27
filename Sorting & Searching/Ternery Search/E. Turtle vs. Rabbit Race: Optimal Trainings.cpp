// Problem link: https://codeforces.com/contest/1933/problem/E

#include <bits/stdc++.h>
using namespace std;

long long nthSum (long long n) { 
  return n * (n + 1) / 2;
}

int main () {
  int tt;
  cin >> tt;
  while (tt--) { 
    int n;
    cin >> n;
    vector<long long> dp(n);
    for (int i = 0; i < n; ++i) { 
      int x;
      cin >> x;
      dp[i] = (i ? dp[i - 1] : 0) + x;
    }
    auto getSum = [&] (long long l, long long r) { 
      return dp[r] - (l ? dp[l - 1] : 0);
    };
    auto f = [&] (int l, int r, long long u) { 
      long long curSum = getSum(l, r);
      if (curSum >= u) { 
        curSum -= u;
        curSum = max(curSum - 1, 0LL);
        return nthSum(u) - nthSum(curSum);
      }
      return nthSum(u) - nthSum(u - curSum);
    };
    int q;
    cin >> q;
    while (q--) { 
      long long l, u;
      cin >> l >> u;
      --l;
      int r, lo = l, hi = n - 1;
      while (lo <= hi) { 
        int mid1 = lo + (hi - lo) / 3;
        int mid2 = hi - (hi - lo) / 3;
        long long f1 = f(l, mid1, u);
        long long f2 = f(l, mid2, u);
        if (f1 == f2) {
          r = mid1;
          lo = mid1 + 1;
          hi = mid2 - 1;
        } else if (f1 < f2) { 
          lo = mid1 + 1;
        } else if (f1 > f2) { 
          hi = mid2 - 1;
        }
      }
      cout << r + 1 << ' ';
    }
    cout << '\n';
  }
  return 0;
}
