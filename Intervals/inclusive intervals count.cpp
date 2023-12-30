// Problem link: https://codeforces.com/contest/1915/problem/F

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;
 
template <typename T>
using ordered_set = 
  tree <T,
  null_type, 
  less<T>, 
  rb_tree_tag,
  tree_order_statistics_node_update
>;
 
int main () { 
  int tt;
  cin >> tt;
  while (tt--) { 
    int n;
    cin >> n;
    ordered_set<int> s;
    vector<array<int, 2>> a(n);
    for (auto& [l, r] : a) { 
      cin >> l >> r;
      s.insert(r);
    }
    long long ans = 0;
    sort(a.begin(), a.end());
    for (auto [l, r] : a) { 
      ans += s.order_of_key(r);
      s.erase(r);
    }
    cout << ans << '\n';
  }
  return 0;
}

