/* Problem link: https://lightoj.com/problem/dna-prefix */

#include <bits/stdc++.h>
using namespace std;

const int TOT_CHARS = 4;

short getMappedVal (char c) { 
  short mappedVal;
  switch (c) { 
    case 'A': 
      mappedVal = 0;
      break;
    case 'C': 
      mappedVal = 1;
      break;
    case 'G': 
      mappedVal = 2;
      break;
    default: 
      mappedVal = 3;
  }
  return mappedVal;
}

struct Node { 
  bool isEndOfWord;
  int prefMatchCnt;
  Node* next[TOT_CHARS];
  Node (int initialVal) { 
    prefMatchCnt = initialVal;
    isEndOfWord = false;
    for (int i = 0; i < TOT_CHARS; ++i) { 
      next[i] = NULL;
    }
  }
} *root;

void insert (string s) { 
  Node* curNode = root;
  for (auto c : s) { 
    if (curNode -> next[getMappedVal(c)] == NULL) { 
      Node* nextNode = new Node(1);
      curNode -> next[getMappedVal(c)] = nextNode;
      curNode = curNode -> next[getMappedVal(c)];
    } else { 
      curNode = curNode -> next[getMappedVal(c)];
      curNode -> prefMatchCnt++;
    }
  }
  curNode -> isEndOfWord = true;
}

int getTotPrefMatchCnt (Node* curNode, int prefLen) { 
  if (curNode == NULL) { 
    return 0;
  }
  int totPrefMatchCnt = curNode -> prefMatchCnt * prefLen;
  for (int i = 0; i < TOT_CHARS; ++i) { 
    totPrefMatchCnt = max(totPrefMatchCnt, getTotPrefMatchCnt(curNode -> next[i], prefLen + 1));
  }
  return totPrefMatchCnt;
}

int main () { 
  int tt;
  cin >> tt;
  for (int caseNo = 1; caseNo <= tt; ++caseNo) { 
    root = new Node(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) { 
      string s;
      cin >> s;
      insert(s);
    }
    cout << "Case " << caseNo << ": " << getTotPrefMatchCnt(root, 0) << '\n';
  }
  return 0;
}
