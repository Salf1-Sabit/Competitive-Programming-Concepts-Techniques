/* Problem: Farthest Nodes in a Tree
 * Link: https://lightoj.com/problem/farthest-nodes-in-a-tree */

#include <bits/stdc++.h>
using namespace std;

const int N = 3e4;
int dist[N + 1], last;
vector<array<int, 2>> g[N];

void dfs (int from, int par) { 
  if (dist[from] > dist[last]) { 
    last = from;
  }
  for (auto [to, w] : g[from]) { 
    if (to != par) { 
      dist[to] = dist[from] + w;
      dfs(to, from);
    }
  }
}

int main () {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int tt;
  cin >> tt;
  for (int caseNo = 1; caseNo <= tt; ++caseNo) { 
    int n;
    cin >> n; 
    last = 0;
    for (int u = 0; u < n; ++u) { 
      dist[u] = 0;
      g[u].clear();
    }
    for (int i = 0; i < n - 1; ++i) { 
      int u, v, w;
      cin >> u >> v >> w;
      g[u].push_back({v, w});
      g[v].push_back({u, w});
    }
    dfs(0, -1);
    for (int u = 0; u < n; ++u) { 
      dist[u] = 0;
    }
    dfs(last, -1);
    cout << "Case " << caseNo << ": " << dist[last] << '\n';
  }
  return 0;
}

