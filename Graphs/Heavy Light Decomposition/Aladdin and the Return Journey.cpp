// Problem link: https://lightoj.com/problem/aladdin-and-the-return-journe

#include <bits/stdc++.h>
using namespace std;

int n, p;
const int N = 3e4;
vector<int> g[N], tree(N + 1), genies(N), parent(N), depth(N), head(N), heavy(N), pos(N), who(N);

void buildBIT () { 
  for (int i = 1; i <= n; ++i) { 
    int idx = i;
    while (idx <= n) { 
      tree[idx] += genies[pos[i]];
      idx += idx & (-idx);
    }
  }
}

int queryBIT (int idx) { 
  int sum = 0;
  while (idx) { 
    sum += tree[idx];
    idx -= idx & (-idx);
  }
  return sum;
}

void updateBIT (int nodeNo, int x) { 
  int idx = who[nodeNo];
  while (idx <= n) { 
    tree[idx] += x - genies[nodeNo];
    idx += idx & (-idx);
  }
  genies[nodeNo] = x;
}

// Marks heavy edges and parents for each node
int dfs (int from) { 
  int parSubSize = 1, maxChildSize = 0;
  for (auto to : g[from]) { 
    if (to != parent[from]) { 
      parent[to] = from;
      depth[to] = depth[from] + 1;
      int childSubSize = dfs(to);
      parSubSize += childSubSize;
      if (childSubSize > maxChildSize) { 
        maxChildSize = childSubSize;
        heavy[from] = to;
      }
    }
  }
  return parSubSize;
}

// Marks head for each chain and position for each node
void decompose (int from, int curHead) { 
  head[from] = curHead, who[from] = p, pos[p++] = from;
  if (heavy[from] != -1) { 
    decompose(heavy[from], curHead);
  }
  for (auto to : g[from]) { 
    if (to != parent[from] and to != heavy[from]) { 
      decompose(to, to);
    }
  }
}

int queryHLD (int u, int v) { 
  int sum = 0;
  for (; head[u] != head[v]; v = parent[head[v]]) { 
    if (depth[head[u]] > depth[head[v]]) {
      swap(u, v);
    }
    sum += queryBIT(who[v]) - queryBIT(who[head[v]] - 1);
  }
  if (depth[u] > depth[v]) {
    swap(u, v);
  }
  sum += queryBIT(who[v]) - queryBIT(who[u] - 1);
  return sum;
}

int main () {
  int tt;
  cin >> tt;
  for (int C = 1; C <= tt; ++C) {
    p = 1;
    cin >> n;
    for (int u = 0; u < n; ++u) { 
      cin >> genies[u];
      g[u].clear();
      heavy[u] = -1;
      tree[u + 1] = 0;
    }
    for (int i = 0; i < n - 1; ++i) {
      int u, v;
      cin >> u >> v;
      g[u].push_back(v);
      g[v].push_back(u);
    } 
    dfs(0);
    decompose(0, 0);
    buildBIT();
    int q;
    cin >> q;
    cout << "Case " << C << ":\n";
    while (q--) { 
      int type;
      cin >> type;
      if (type == 0) { 
        int u, v;
        cin >> u >> v;
        cout << queryHLD(u, v) << '\n';
      } else { 
        int u, x;
        cin >> u >> x;
        updateBIT(u, x);
      }
    }
  }
  return 0;
}


