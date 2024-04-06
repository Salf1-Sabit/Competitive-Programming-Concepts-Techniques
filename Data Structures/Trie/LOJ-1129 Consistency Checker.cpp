/* Problem link: https://lightoj.com/problem/consistency-checker */

#include <bits/stdc++.h>
using namespace std;

const int MAX_NUM = 10;

int getVal (char c) { 
  return c - '0';
}

struct Node { 
  bool isEndOfWord;
  Node* next[MAX_NUM];
  Node () { 
    isEndOfWord = false;
    for (int digit = 0; digit < MAX_NUM; ++digit) { 
      next[digit] = NULL;
    }
  }
} *root;

void insert (string s) { 
  Node* curNode = root;
  for (auto c : s) { 
    if (curNode -> next[getVal(c)] == NULL) { 
      curNode -> next[getVal(c)] = new Node();
    }
    curNode = curNode -> next[getVal(c)];
  }
  curNode -> isEndOfWord = true;
}

bool search (Node* curNode, bool seenPrefix) { 
  if (curNode == NULL) { 
    return false;
  }
  if (curNode -> isEndOfWord and seenPrefix) { 
    return true;
  }
  for (int digit = 0; digit < MAX_NUM; ++digit) { 
    if (search(curNode -> next[digit], seenPrefix | curNode -> isEndOfWord)) { 
      return true;
    }
  }
  return false;
}

void clear (Node* curNode) { 
  for (int digit = 0; digit < MAX_NUM; ++digit) { 
    if (curNode -> next[digit] != NULL) { 
      clear(curNode -> next[digit]);
    }
  }
  delete(curNode);
}

int main () { 
  int tt;
  cin >> tt;
  for (int caseNo = 1; caseNo <= tt; ++caseNo) { 
    int n;
    cin >> n;
    root = new Node();
    for (int i = 0; i < n; ++i) { 
      string s;
      cin >> s;
      insert(s);
    }
    cout << "Case " << caseNo << ": " << (search(root, false) ? "NO" : "YES") << "\n";
    clear(root);
  }
  return 0;
}
