// Problem link: https://codeforces.com/contest/1915/problem/G

#include <bits/stdc++.h>
using namespace std;

int main () { 
  int tt;
  cin >> tt;
  while (tt--) { 
    int n, m;
    cin >> n >> m;
    vector<array<int, 2>> g[n];
    for (int i = 0; i < m; ++i) { 
      int u, v, w;
      cin >> u >> v >> w;
      --u, --v;
      g[u].push_back({v, w});
      g[v].push_back({u, w});
    }
    vector<int> s(n);
    for (int u = 0; u < n; ++u) { 
      cin >> s[u];
    }
    long long inf = (long long) 1e18;
    using nested = vector<long long>;
    vector<nested> dp(n, nested(n, inf));
    vector<nested> seen(n, nested(n, false));
    multiset<array<long long, 3>> q;
    dp[0][0] = 0;
    q.insert({0, 0, 0});
    long long ans = inf;
    while (!q.empty()) { 
      auto [weight, bike, city] = *q.begin();
      q.erase(q.begin());
      if (city == n - 1) {
        ans = weight;
        break;
      }
      if (seen[city][bike]) { 
        continue;
      }
      seen[city][bike] = true;
      for (auto [to, len] : g[city]) { 
        int new_bike = bike;
        if (s[to] < s[bike]) { 
          new_bike = to;
        }
        if (weight + s[bike] * 1LL * len <= dp[to][new_bike]) { 
          dp[to][new_bike] = weight + s[bike] * 1LL * len;
          q.insert({dp[to][new_bike], new_bike, to});
        }
      }
    }
    cout << ans << '\n';
  }
  return 0;
}

