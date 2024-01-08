// Finds the lexicographically largest subsequence of a string
#include <bits/stdc++.h>
using namespace std;

int main () { 
  int n;
  cin >> n;
  string s;
  cin >> s;
  string large_subseq = "";
  for (int i = 0; i < n; ++i) { 
    // While the previous element is smaller than 
    // current element keep removing this
    while (large_subseq != "" and large_subseq.back() < s[i]) { 
      large_subseq.pop_back();
    }
    large_subseq += s[i];
  }
  cout << large_subseq << '\n';
  return 0;
}


