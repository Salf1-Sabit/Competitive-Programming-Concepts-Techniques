#include <bits/stdc++.h>
using namespace std;

const int N = (int) 2e2 + 1;
long long dp[N][21][11][2];
int d, m, n, q, a[N];

long long sol (int i, int mod, int cnt, int sgn) {
  if (cnt == m) {
    return (mod == 0);
  }
  if (i == n) {
    return 0;
  }
  long long& ans = dp[i][mod][cnt][sgn];
  if (ans != -1) {
    return ans;
  }
  int mult = (sgn ? -1 : 1);
  ans = sol(i + 1, mod, cnt, sgn);
  int sum = (mult * mod + a[i]) % d;
  sgn = (sum < 0);
  return ans += sol(i + 1, abs(sum), cnt + 1, sgn);
}

int main () {
  int tt;
  cin >> tt;
  for (int C = 1; C <= tt; ++C) {
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
    }
    cout << "Case " << C << ":\n";
    while (q--) {
      cin >> d >> m;
      memset(dp, -1, sizeof dp);
      cout << sol(0, 0, 0, 0) << '\n';
    }
  }
  return 0;
}
