// Problem link: https://cses.fi/problemset/task/1138

#include <bits/stdc++.h>
using namespace std;

const int N = (int) 2e5 + 1;
vector<int> val(N), g[N], who(N);

// ### Binary Indexed Tree ### 

long long tree[N];

void buildBIT (int n) { 
  for (int i = 1; i <= n; ++i) { 
    int idx = i;
    while (idx <= n) { 
      tree[idx] += val[who[i]];
      idx += idx & (-idx);
    }
  }
}

long long queryBIT (int idx) { 
  long long sum = 0;
  while (idx) { 
    sum += tree[idx];
    idx -= idx & (-idx);
  }
  return sum;
}

// n is the size of the array, x is the number to add
void updateBIT (int idx, int x, int n) {   
  int p = idx;
  while (idx <= n) { 
    tree[idx] += x - val[who[p]];
    idx += idx & (-idx);
  }
  val[who[p]] = x;
}


// ### Heavy Light Decmposition ### 

/* Remember to: 
 *   1. Follow 0 based indexing for nodes
 *   2. Reassign all heavy[u] with -1
 *   3. Clear all containers for each test case */

int p = 1;
vector<int> parent(N), heavy(N), depth(N), head(N), pos(N);

// Finds depth, parent and heavy edge for each node 
int dfs (int from) { 
  int curSubSize = 1, maxSize = 0;
  for (auto to : g[from]) { 
    if (to != parent[from]) { 
      parent[to] = from;
      depth[to] = depth[from] + 1;
      int childSubSize = dfs(to);
      curSubSize += childSubSize;
      if (childSubSize > maxSize) { 
        maxSize = childSubSize;
        heavy[from] = to;
      }
    }
  }
  return curSubSize;
}

/* Marks head and position for each node
 * Note: Positions in each chain will be consecutive from top to bottom
 *       This is what lets us to query on that chain */
void decompose (int from, int curHead) { 
  head[from] = curHead, pos[from] = p, who[p++] = from;
  if (heavy[from] != -1) { 
    decompose(heavy[from], curHead);
  }
  for (auto to : g[from]) { 
    if (to != parent[from] and to != heavy[from]) { 
      decompose(to, to);
    }
  }
}

// Sum Query
long long queryHLD (int from, int to) { 
  long long sum = 0;
  for (; head[from] != head[to]; to = parent[head[to]]) { 
    if (depth[head[from]] > depth[head[to]]) { 
      swap(from, to);
    }
    sum += (queryBIT(pos[to]) - queryBIT(pos[head[to]] - 1));
  }
  if (depth[from] > depth[to]) { 
    swap(from, to);
  }
  sum += (queryBIT(pos[to]) - queryBIT(pos[from] - 1));
  return sum;
}

int main () {
  int n, q;
  cin >> n >> q;
  for (int u = 1; u <= n; ++u) { 
    heavy[u] = -1;
    cin >> val[u];
  }
  for (int i = 0; i < n - 1; ++i) { 
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(1);
  decompose(1, 1);
  buildBIT(n);
  while (q--) { 
    int type;
    cin >> type;
    if (type == 1) { 
      int v, x;
      cin >> v >> x;
      updateBIT(pos[v], x, n);
    } else { 
      int v;
      cin >> v;
      cout << queryHLD(1, v) << '\n';
    }
  } 
  return 0;
}


