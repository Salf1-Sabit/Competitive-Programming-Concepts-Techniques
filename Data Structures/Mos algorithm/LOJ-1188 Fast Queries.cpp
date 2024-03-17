/* Problem link: https://lightoj.com/problem/fast-queries 
 * Problem summary: Find the number of distinct elems in a range in between queries
 * Topic: Mo's algorithm */

#include <bits/stdc++.h>
using namespace std;

/* Why this algo: This algo is used to answer those queries which are 
 * dynamic e.g. (distinct elems). Which cannot be done using segment tree. */ 

/* Time Complexity: O((N + Q) F sqrt(N)). Where F = time of add-remove functions. 
 *     -> Firstly, if all of the left index are at same block then, for one block 
 *   we will move our right index at most N times. Then, for every block we will 
 *   have O(N * sqrt(N)) times. 
 * 	   -> Secondly, for each query our left pointer can move at most sqrt(N) times. 
 * 	 Because, each block has at most sqrt(N) cells. So, for Q query there will 
 * 	 be O(Q * sqrt(N)) calls at most. 
 *	   -> Hence, O(N * sqrt(N) + Q * sqrt(N)) = O((N + Q) * sqrt(N)) by taking 
 *	   sqrt(N) common from both sides. */

/* Before using this, make sure to store all the queries (0 based indexing) 
 * in a vector this manner vector{l, r, query_idx} */

int n, q, blockSize;
const int N = (int) 1e5;

struct Query { 
  int l, r, idx;
};

vector<int> a(N);
vector<Query> queries;

/* Data structure for this paricular problem */
int curUniqueElems;
vector<int> freq(N + 1);

void sortQueries () { 
  /* sorts the queries in ascending order (by block number) 
   * But, in case of same block sorting them by (right endpoint) */
  sort(queries.begin(), queries.end(), [&] (Query x, Query y) { 
    if (x.l / blockSize != y.l / blockSize) { 
      return x.l < y.l;
    }
 /* Optimization: Here, by sorting the even block in ascending order 
  * by (right endpoint) and the odd block in descending order (by right endpoint)
  * The right pointer will have to move less. This will eliminate the extra 
  * movement of the right pointer which was wasteful. 
  * Right pointer movement (before) i: 1, 2, 3, 1, 2, 3, 1, 2, 3, ...
  * Right pointer movement (now)    i: 1, 2, 3, 3, 2, 1, 1, 2, 3, 3, 2, 1, ... */ 
    return ((x.l / blockSize) % 2 ? y.r > x.r : x.r < y.r);
  });
}

void add (int idx) { 
  if (++freq[a[idx]] == 1) { 
    curUniqueElems++;
  }
}

void remove (int idx) { 
  if (--freq[a[idx]] == 0) { 
    curUniqueElems--;
  }
}

int getAnswer () { 
  return curUniqueElems;
}

int main () {
  int tt;
  cin >> tt;
  for (int caseNo = 1; caseNo <= tt; ++caseNo) { 
    curUniqueElems = 0;
    queries.clear();
    freq.assign(N + 1, 0);
    cin >> n >> q;
    blockSize = sqrtl(n);
    for (int i = 0; i < n; ++i) { 
      cin >> a[i];
    }
    for (int i = 0; i < q; ++i) { 
      int l, r;
      cin >> l >> r;
      --l, --r;
      queries.push_back({l, r, i});
    }
    /* Mo's algorithm starts here */
    sortQueries();
    int curL = 0, curR = -1;
    vector<int> queryAns(q);
    for (Query query : queries) { 
      while (query.l < curL) { 
        curL--;
        add(curL);
      }
      while (curR < query.r) { 
        curR++;
        add(curR);
      }
      while (curL < query.l) { 
        remove(curL);
        curL++;
      }
      while (query.r < curR) { 
        remove(curR);
        curR--;
      }
      queryAns[query.idx] = getAnswer();
    }
    cout << "Case " << caseNo << ":\n";
    for (auto curAns : queryAns) { 
      cout << curAns << "\n";
    }
  }
  return 0;
}

