// Problem link: https://codeforces.com/contest/1909/problem/C
/* Learned from this probelm: 
     - How to arrange the intervals in a way, such that
       if the difference between each interval, di = (i.e ri - li) 
       and c = {d1, d2, ..., dn} in non-decreasing order.
       Then, this sequence "c" is the lexicogrphically smallest sequence. 
   Algorithm: 
     - Sort all the points (l and r) together in a list with associated type of them.
       Then, the list would look like this {l1 < l2 < l3 < r1 < l4 < r2 < r3 < r4 ... }
     - Then, (follow the "valid bracket sequence" technique) maintain a stack 
       which will store only the "left point - l" of a range such that stack = {l1, l2 .. lk}. 
     - Then, as soon as a "right point - r" is found take the difference of this range 
       (i.e r - l) and pop the top (l) from the stack. */

#include <bits/stdc++.h>
using namespace std;

int main () { 
  ios::sync_with_stdio(0);
  cin.tie(0);
  int tt;
  cin >> tt;
  while (tt--) { 
    int n;
    cin >> n;
    vector<array<int, 2>> endpoints; // stores [point, type] 
    // Input the "left endpoints"
    for (int i = 0; i < n; ++i) { 
      int l;
      cin >> l;
      endpoints.push_back({l, 0});
    }
    // Input the "right endpoints"
    for (int i = 0; i < n; ++i) { 
      int r;
      cin >> r;
      endpoints.push_back({r, 1});
    }
    vector<int> c(n); // costs for each range 
    for (auto& x : c) { 
      cin >> x;
    }
    stack<int> stk;
    vector<int> optimal_dist;
    sort(endpoints.begin(), endpoints.end());
    for (auto [point, type] : endpoints) { 
      if (type == 0) { // If this is a "l" push it into the stack
        stk.push(point); 
      } else { // If this is a "r" take the difference and pop the last "l" from stack
        optimal_dist.push_back(point - stk.top()); 
        stk.pop();
      }
    }
    long long ans = 0;
    sort(optimal_dist.begin(), optimal_dist.end()); // This contains the lexicographically 
                                                    // smallest sequence "c" mentioned above
    sort(c.rbegin(), c.rend());
    for (int i = 0; i < n; ++i) { 
      ans += optimal_dist[i] * 1LL * c[i];
    }
    cout << ans << '\n';
  }
  return 0; 
}

