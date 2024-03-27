/* Problem link: https://codeforces.com/problemset/problem/1941/E
 * Approach: DP + Sliding window using multiset technique
 * How is this useful? 
 *    - This style can be used in places, where we need the min/max  
 *      from last "k" values of "dp[i]"
 *    - Here, instead of looping backward everytime for last "k" values, 
 *      we can simply use a multiset, and each time we can remove the 
 *      last (i - k)th value from the multiset. And push the current dp[i] 
 *      into the multiset. 
 * Time complexity: 
 *   - Before: O(n^2)
 *   - After:  O(nlogn) */

#include <bits/stdc++.h>
using namespace std;

int main () {
  int tt;
  cin >> tt;
  while (tt--) { 
    int n, m, k, d;
    cin >> n >> m >> k >> d;
    vector<long long> minCost(n);
    for (int i = 0; i < n; ++i) { 
      vector<long long> dp(m);
      multiset<long long> lastMinimums; /* multiset to store each dp[i] */
      for (int j = 0; j < m; ++j) { 
        int x;
        cin >> x;
        dp[j] = x + 1;
        if (!lastMinimums.empty()) { 
          dp[j] += *lastMinimums.begin();
        }
        /* Remove the last dp[i - k], so that we can get the minumum from 
         * only the last "k" dp[i] values*/
        if (j - d - 1 >= 0) { 
          lastMinimums.erase(lastMinimums.find(dp[j - d - 1]));
        }
        lastMinimums.insert(dp[j]);
      }
      minCost[i] = dp.back();
    }
    long long curSum = 0;
    for (int i = 0; i < k; ++i) { 
      curSum += minCost[i];
    }
    long long ans = curSum;
    for (int i = k; i < n; ++i) { 
      curSum += minCost[i] - minCost[i - k];
      ans = min(ans, curSum);
    }
    cout << ans << '\n';
  }
  return 0;
}
