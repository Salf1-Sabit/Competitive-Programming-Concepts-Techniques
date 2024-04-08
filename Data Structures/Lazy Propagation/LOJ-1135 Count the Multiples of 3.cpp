/* Problem link: https://lightoj.com/problem/count-the-multiples-of-3 
 * Topic: Segment tree (Lazy Propagation - push technique) */

#include <bits/stdc++.h>
using namespace std;

const int TARGET_NUM = 3;
const int MAX_N = (int) 1e5;
int lazy[4 * MAX_N];
vector<vector<int>> tree(4 * MAX_N, vector<int>(TARGET_NUM));

int getRotatePos (int mod) { 
  if (mod == 0) { 
    return mod;
  }
  return mod == 2 ? 1 : 2;
}

void propagate (int node, int treeL, int treeR) { 
  if (lazy[node] != 0) { 
    int curLazySum = lazy[node] % 3;
    rotate(tree[node].begin(), tree[node].begin() + getRotatePos(curLazySum), tree[node].end());
    if (treeL != treeR) { 
      lazy[node * 2] += lazy[node];
      lazy[node * 2 + 1] += lazy[node];
    }
    lazy[node] = 0;
  }
}

void build (int node, int treeL, int treeR) { 
  lazy[node] = 0;
  tree[node] = {0, 0, 0}; 
  if (treeL == treeR) { 
    tree[node][0] = 1;
    return;
  }
  int mid = (treeL + treeR) / 2;
  build(node * 2, treeL, mid);
  build(node * 2 + 1, mid + 1, treeR);
  tree[node][0] = tree[node * 2][0] + tree[node * 2 + 1][0];
}

void update (int node, int treeL, int treeR, int queryL, int queryR) { 
  propagate(node, treeL, treeR);
  if (queryR < treeL or treeR < queryL) { 
    return;
  }
  if (queryL <= treeL and treeR <= queryR) { 
    lazy[node] += 1;
    propagate(node, treeL, treeR);
    return;
  }
  int mid = (treeL + treeR) / 2;
  update(node * 2, treeL, mid, queryL, queryR);
  update(node * 2 + 1, mid + 1, treeR, queryL, queryR);
  for (int mod = 0; mod < TARGET_NUM; ++mod) { 
    tree[node][mod] = tree[node * 2][mod] + tree[node * 2 + 1][mod];
  }
}

int query (int node, int treeL, int treeR, int queryL, int queryR) { 
  propagate(node, treeL, treeR);
  if (queryR < treeL or treeR < queryL) { 
    return 0;
  }
  if (queryL <= treeL and treeR <= queryR) { 
    return tree[node][0];
  }
  int mid = (treeL + treeR) / 2;
  int leftSum = query(node * 2, treeL, mid, queryL, queryR);
  int rightSum = query(node * 2 + 1, mid + 1, treeR, queryL, queryR);
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
        update(1, 0, n - 1, l, r);
      } else { 
        cout << query(1, 0, n - 1, l, r) << '\n';
      }
    }
  }
  return 0;
}
