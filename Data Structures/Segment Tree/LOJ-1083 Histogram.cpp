/* Problem link: https://lightoj.com/problem/histogram
 * Approach: Divide and conquer + Binary Search + Segment Tree */

#include <bits/stdc++.h>
using namespace std;

const int N = (int) 3e4;
int n, tree[4 * N], a[N];
map<int, vector<int>> ids;

void build (int node, int treeL, int treeR) { 
  if (treeL == treeR) { 
    tree[node] = a[treeL];
    return;
  }
  int mid = (treeL + treeR) / 2;
  build(node * 2, treeL, mid);
  build(node * 2 + 1, mid + 1, treeR);
  tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
}

int query (int node, int treeL, int treeR, int queryL, int queryR) { 
  if (queryR < treeL or treeR < queryL) { 
    return N;
  }
  if (queryL <= treeL and treeR <= queryR) { 
    return tree[node];
  }
  int mid = (treeL + treeR) / 2;
  int leftMin = query(node * 2, treeL, mid, queryL, queryR);
  return min(leftMin, query(node * 2 + 1, mid + 1, treeR, queryL, queryR));
}

long long conquer (int l, int r) { 
  if (l >= r) { 
    return (l > r ? 0 : a[l]);
  }
  int mn = query(1, 0, n - 1, l, r);
  int treeMid = *lower_bound(ids[mn].begin(), ids[mn].end(), l);
  return max({(r - l + 1) * 1LL * mn, 1LL * conquer(l, treeMid - 1), 1LL * conquer(treeMid + 1, r)});
}

int main () {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int tt;
  cin >> tt;
  for (int C = 1; C <= tt; ++C) {
    cin >> n;
    for (int i = 0; i < n; ++i) { 
      cin >> a[i];
      ids[a[i]].push_back(i);
    }
    build(1, 0, n - 1);
    cout << "Case " << C << ": " << conquer(0, n - 1) << '\n';
    ids.clear();
  }
  return 0;
}

