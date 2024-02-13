/* Contest: UAP Collaboration contest (Juniors)
	 Problem name: Puzzle */

#include <bits/stdc++.h>
using namespace std;

bool has_cycle;
bool explored[26], cycle_check[26];
vector<int> g[26], topo;

void dfs (int from) { 
  if (has_cycle) { 
    return;
  }
  explored[from] = cycle_check[from] = true;
  for (auto to : g[from]) { 
    if (!cycle_check[to]) { 
      if (!explored[to]) { 
        dfs(to);
      }
    } else { 
      has_cycle = true;
      return;
    }
  }
  cycle_check[from] = false;
  topo.push_back(from);
}

int main () { 
  int tt;
  cin >> tt;
  while (tt--) { 
    topo.clear();
    has_cycle = false;
    for (int i = 0; i < 26; ++i) { 
      g[i].clear();
      explored[i] = cycle_check[i] = false;
    }
    int n, q;
    cin >> n >> q;
    vector<int> present(26);
    while (q--) { 
      string s;
      cin >> s;
      if (s[1] == '<') { 
        g[s[2] - 'A'].push_back(s[0] - 'A');
      } else { 
        g[s[0] - 'A'].push_back(s[2] - 'A');
      }
      present[s[0] - 'A'] = present[s[2] - 'A'] = true;
    }
    for (int u = 0; u < 26; ++u) { 
      if (present[u] and !explored[u]) { 
        dfs(u);
      }
    }
    if (has_cycle) { 
      cout << "Impossible\n";
      continue;
    }
    for (auto u : topo) { 
      cout << char(u + 'A');
    }
    cout << '\n';
  }
  return 0;
}

