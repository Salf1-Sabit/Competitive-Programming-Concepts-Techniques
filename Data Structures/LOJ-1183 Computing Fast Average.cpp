/* Problem link: https://lightoj.com/problem/computing-fast-average
 * Topic: Segment Tree (push technique) - Range update + Range query */

#include <bits/stdc++.h>
using namespace std;

const int N = (int) 1e5;
long long tree[N * 4];
int lazy[N * 4];

void propagate (int node, int treeL, int treeR) { 
  if (lazy[node] != -1) { 
    tree[node] = (treeR - treeL + 1) * 1LL * lazy[node];
    if (treeL != treeR) { 
        lazy[node * 2] = lazy[node * 2 + 1] = lazy[node];
    }
    lazy[node] = -1;
  }
}

void build (int node, int treeL, int treeR) { 
  lazy[node] = -1;
  tree[node] = 0;
  if (treeL == treeR) { 
    return;
  }
  int mid = (treeL + treeR) / 2;
  build(node * 2, treeL, mid);
  build(node * 2 + 1, mid + 1, treeR);
}

void update (int node, int treeL, int treeR, int queryL, int queryR, int val) { 
  propagate(node, treeL, treeR);
  if (treeR < queryL or queryR < treeL) { 
    return;
  }
  if (queryL <= treeL and treeR <= queryR) { 
    lazy[node] = val;
    propagate(node, treeL, treeR);
    return;
  }
  int mid = (treeL + treeR) / 2;
  update(node * 2, treeL, mid, queryL, queryR, val);
  update(node * 2 + 1, mid + 1, treeR, queryL, queryR, val);
  tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

long long query (int node, int treeL, int treeR, int queryL, int queryR) { 
  propagate(node, treeL, treeR);
  if (treeR < queryL or queryR < treeL) { 
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
      int type;
      cin >> type;
      if (type == 1) { 
        int l, r, v;
        cin >> l >> r >> v;
        update(1, 0, n - 1, l, r, v);
      } else { 
        int l, r;
        cin >> l >> r;
        long long len = r - l + 1;
        long long sum = query(1, 0, n - 1, l, r);
        long long g = gcd(len, sum);
        sum /= g, len /= g;
        if (len == 1) { 
          cout << sum << '\n';
        } else { 
          cout << sum << "/" << len << '\n';
        }
      }
    }
  }
  return 0;
}

