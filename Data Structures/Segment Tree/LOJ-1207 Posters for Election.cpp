/* Probelm link: https://lightoj.com/problem/posters-for-election 
 * Topic: Segment tree (push technique) - Range update with new value + point query */

#include <bits/stdc++.h>
using namespace std;

int n;
const int N = (int) 2e5;
int tree[4 * N];

void build (int node, int treeL, int treeR) { 
  tree[node] = 0;
  if (treeL == treeR) { 
    return;
  }
  int mid = (treeL + treeR) / 2;
  build(node * 2, treeL, mid);
  build(node * 2 + 1, mid + 1, treeR);
}

int queryVal (int node, int treeL, int treeR, int queryL, int queryR) { 
  if (treeR < queryL or queryR < treeL) {
    return 0;
  }
  if ((queryL <= treeL and treeR <= queryR) or tree[node] != 0) {
    return tree[node];
  }
  int mid = (treeL + treeR) / 2;
  int leftVal = queryVal(node * 2, treeL, mid, queryL, queryR);
  return leftVal + queryVal(node * 2 + 1, mid + 1, treeR, queryL, queryR);
}

void update (int node, int treeL, int treeR, int queryL, int queryR, int newVal) { 
  if (treeR < queryL or queryR < treeL) { 
    return;
  }
  if (queryL <= treeL and treeR <= queryR) { 
    tree[node] = newVal;
    return;
  }
  /* While traversing down the tree, If the current node 
   * holds a value already, push that value to the childs */
  if (tree[node] != 0) { 
    tree[node * 2] = tree[node * 2 + 1] = tree[node];
    tree[node] = 0;
  }
  int mid = (treeL + treeR) / 2;
  update(node * 2, treeL, mid, queryL, queryR, newVal);
  update(node * 2 + 1, mid + 1, treeR, queryL, queryR, newVal);
}

int main () {
  int tt;
  cin >> tt;
  for (int caseNo = 1; caseNo <= tt; ++caseNo) { 
    cin >> n;
    build(1, 1, 2 * n);
    for (int i = 1; i <= n; ++i) { 
      int l, r;
      cin >> l >> r;
      update(1, 1, 2 * n, l, r, i);
    }
    set<int> uniqueColors;
    for (int i = 1; i <= 2 * n; ++i) { 
      int curSectionColor = queryVal(1, 1, 2 * n, i, i);
      if (curSectionColor != 0) { 
        uniqueColors.insert(curSectionColor);
      }
    }
    cout << "Case " << caseNo << ": " << (int) uniqueColors.size() << '\n';
  }
  return 0;
}
