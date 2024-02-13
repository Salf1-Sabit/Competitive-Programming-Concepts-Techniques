// Problem link: https://codeforces.com/contest/1931/problem/F

#include <bits/stdc++.h>
using namespace std;

bool has_cycle;
const int N = (int) 2e5 + 1;
bool explored[N], cycle_check[N];
vector<set<int>> g(N);

void dfs (int from) { 
  if (has_cycle) { 
    return;
  }
  explored[from] = cycle_check[from] = true;
  for (auto to : g[from]) { 
    if (!cycle_check[to]) { 
      if (!explored[to]) { 
        dfs(to);
      }
    } else { 
      has_cycle = true;
      return;
    }
  }
  cycle_check[from] = false;
}

int main () { 
  int tt;
  cin >> tt;
  while (tt--) { 
    int n, k;
    cin >> n >> k;
    has_cycle = false;
    for (int i = 1; i <= n; ++i) { 
      g[i].clear();
      explored[i] = cycle_check[i] = false;
    }
    while (k--) { 
      int prev = -1;
      for (int i = 0; i < n; ++i) { 
        int cur;
        cin >> cur;
        if (i >= 2) { 
          g[cur].insert(prev);
        }
        prev = cur;
      }
    }
    for (int u = 1; u <= n; ++u) { 
      if (!explored[u]) { 
        dfs(u);
      }
    }
    cout << (has_cycle ? "NO" : "YES") << '\n';
  }
  return 0;
}
 
