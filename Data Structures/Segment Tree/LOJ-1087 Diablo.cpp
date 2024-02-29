/* Problem link: https://lightoj.com/problem/diablo
 * Approach: Segment Tree + Binary Search */

#include <bits/stdc++.h>
using namespace std;

const int N = (int) 150000;
int n, q, tree[N * 4], a[N];

void build (int node, int treeL, int treeR) { 
  if (treeL == treeR) { 
    tree[node] = 1;
    return;
  }
  int mid = (treeL + treeR) / 2;
  build(node * 2, treeL, mid);
  build(node * 2 + 1, mid + 1, treeR);
  tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

void update (int node, int treeL, int treeR, int queryIdx, int val) { 
  if (queryIdx < treeL or treeR < queryIdx) { 
    return;
  }
  if (queryIdx == treeL and queryIdx == treeR) { 
    tree[node] = val;
    return;
  }
  int mid = (treeL + treeR) / 2;
  update(node * 2, treeL, mid, queryIdx, val);
  update(node * 2 + 1, mid + 1, treeR, queryIdx, val);
  tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

int getSum (int node, int treeL, int treeR, int queryL, int queryR)  {
  if (queryR < treeL or treeR < queryL) { 
    return 0;
  }
  if (queryL <= treeL and treeR <= queryR) { 
    return tree[node];
  }
  int mid = (treeL + treeR) / 2;
  int leftSum = getSum(node * 2, treeL, mid, queryL, queryR);
  return leftSum + getSum(node * 2 + 1, mid + 1, treeR, queryL, queryR);
}

int main () {
  int tt;
  cin >> tt;
  for (int C = 1; C <= tt; ++C) { 
    cin >> n >> q;
    for (int i = 0; i < n; ++i) { 
      cin >> a[i];
    }
    build(1, 0, N - 1);
    cout << "Case " << C << ":\n";
    while (q--) { 
      char type;
      cin >> type;
      if (type == 'c') { 
        int pos;
        cin >> pos;
        int foundPos = -1, lo = 0, hi = n - 1;
        while (lo <= hi) { 
          int mid = (lo + hi) / 2;
          int sum = getSum(1, 0, N - 1, 0, mid);
          if (sum >= pos) { 
            foundPos = mid;
            hi = mid - 1;
          } else { 
            lo = mid + 1;
          }
        }
        cout << (foundPos == -1 ? "none" : to_string(a[foundPos])) << '\n';
        if (foundPos != -1) { 
          update(1, 0, N - 1, foundPos, 0);
          a[foundPos] = 0;
        }
      } else { 
        int val;
        cin >> val;
        ++n;
        a[n - 1] = val;
        update(1, 0, N - 1, n - 1, 1);
      }
    }
  }
  return 0;
}
