/* Problem link: https://lightoj.com/problem/all-possible-inc-subseq
 * Approach: Sorting + Segment Tree */

#include <bits/stdc++.h>
using namespace std;

const int N = (int) 1e5;
const int mod = (int) 1e9 + 7;
int n, tree[4 * N];
vector<array<int, 2>> a(N);

int getSum (int node, int treeL, int treeR, int queryL, int queryR) { 
  if (queryR < treeL or treeR < queryL) { 
    return 0;
  }
  if (queryL <= treeL and treeR <= queryR) { 
    return tree[node];
  }
  int mid = (treeL + treeR) / 2;
  int leftSum = getSum(node * 2, treeL, mid, queryL, queryR);
  return (leftSum + getSum(node * 2 + 1, mid + 1, treeR, queryL, queryR)) % mod;
}

void updateVal (int node, int treeL, int treeR, int queryIdx, int val) { 
  if (queryIdx < treeL or treeR < queryIdx) { 
    return;
  }
  if (queryIdx == treeL and treeR == queryIdx) { 
    tree[node] = val;
    return;
  }
  int mid = (treeL + treeR) / 2;
  updateVal(node * 2, treeL, mid, queryIdx, val);
  updateVal(node * 2 + 1, mid + 1, treeR, queryIdx, val);
  tree[node] = (tree[node * 2] + tree[node * 2 + 1]) % mod;
}

int main () {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int tt;
  cin >> tt;
  for (int C = 1; C <= tt; ++C) { 
    cin >> n;
    for (int i = 0; i < n; ++i) { 
      cin >> a[i][0];
      a[i][1] = -i;
    }

    /* Sort increasingly of values
     * But, in case of equal values then, sort decreasingly of indices */
    sort(a.begin(), a.begin() + n);

    // Clearing segment tree
    for (int i = 0; i < 4 * n; ++i) { 
      tree[i] = 0;
    }

    for (int i = 0; i < n; ++i) { 
      int idx = -a[i][1];

      /* Get the sum of all values smaller than this element (i.e a[i][0])
       * whose positions are before this (i.e pos < a[i][1]) */
      int cnt = getSum(1, 0, n - 1, 0, idx);

      // Update the value of this index with cnt + 1 
      updateVal(1, 0, n - 1, idx, cnt + 1);
    }

    // Finally, print the sum of all the indexes
    cout << "Case " << C << ": " << getSum(1, 0, n - 1, 0, n - 1) << '\n';
  }
  return 0;
}
