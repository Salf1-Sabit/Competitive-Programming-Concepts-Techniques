/* Problem link: https://lightoj.com/problem/horrible-queries 
 * Topic: Segment Tree (Lazy propagataion - push technique) */

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = (int) 1e5;
long long tree[4 * MAX_N], lazy[4 * MAX_N];

void propagate (int node, int treeL, int treeR) { 
  if (lazy[node] != 0) { 
    tree[node] += (treeR - treeL + 1) * lazy[node];
    if (treeL != treeR) { 
      lazy[node * 2] += lazy[node];
      lazy[node * 2 + 1] += lazy[node];
    }
    lazy[node] = 0;
  }
}

void build (int node, int treeL, int treeR) { 
  tree[node] = lazy[node] = 0;
  if (treeL == treeR) {
    return;
  }
  int mid = (treeL + treeR) / 2;
  build(node * 2, treeL, mid);
  build(node * 2 + 1, mid + 1, treeR);
}

void update (int node, int treeL, int treeR, int queryL, int queryR, int valToAdd) { 
  propagate(node, treeL, treeR);
  if (queryR < treeL or treeR < queryL) { 
    return;
  }
  if (queryL <= treeL and treeR <= queryR) { 
    lazy[node] += valToAdd;
    propagate(node, treeL, treeR);
    return;
  }
  int mid = (treeL + treeR) / 2;
  update(node * 2, treeL, mid, queryL, queryR, valToAdd);
  update(node * 2 + 1, mid + 1, treeR, queryL, queryR, valToAdd);
  tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

long long query (int node, int treeL, int treeR, int queryL, int queryR) { 
  propagate(node, treeL, treeR);
  if (queryR < treeL or treeR < queryL) { 
    return 0;
  }
  if (queryL <= treeL and treeR <= queryR) { 
    return tree[node];
  }
  int mid = (treeL + treeR) / 2;
  long long leftSum = query(node * 2, treeL, mid, queryL, queryR);
  long long rightSum = query(node * 2 + 1, mid + 1, treeR, queryL, queryR);
  return leftSum + rightSum;
}

int main () { 
  int tt;
  cin >> tt;
  for (int caseNo = 1; caseNo <= tt; ++caseNo) { 
    int n, q;
    cin >> n >> q;
    build(1, 0, n - 1);
    cout << "Case " << caseNo << ":\n";
    while (q--) { 
      int type, l, r;
      cin >> type >> l >> r;
      if (type == 0) { 
        int valToAdd;
        cin >> valToAdd;
        update(1, 0, n - 1, l, r, valToAdd);
      } else { 
        cout << query(1, 0, n - 1, l, r) << '\n';
      }
    }
  }
  return 0;
}
