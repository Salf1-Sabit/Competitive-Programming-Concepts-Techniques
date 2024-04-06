/* Problem link: https://lightoj.com/problem/easily-readable */

#include <bits/stdc++.h>
using namespace std;

const int MAX_CHARS = 52;

int getMappedVal (char c) { 
  if ('a' <= c and c <= 'z') { 
    return c - 'a';
  }
  return c - 'A' + 26;
}

struct Node { 
  int endedHereCnt;
  Node* next[MAX_CHARS];
  Node () { 
    endedHereCnt = 0;
    for (int charNo = 0; charNo < MAX_CHARS; ++charNo) { 
      next[charNo] = NULL;
    }
  }
} *root;

void insert (string s) { 
  Node* curNode = root;
  for (auto c : s) { 
    if (curNode -> next[getMappedVal(c)] == NULL) { 
      curNode -> next[getMappedVal(c)] = new Node();
    }
    curNode = curNode -> next[getMappedVal(c)];
  }
  curNode -> endedHereCnt++;
}

int getSimilarCnt (string s) { 
  Node* curNode = root;
  for (auto c : s) { 
    if (curNode -> next[getMappedVal(c)] == NULL) { 
      return 0;
    }
    curNode = curNode -> next[getMappedVal(c)];
  }
  return curNode -> endedHereCnt;
}

void clear (Node* curNode) { 
  for (int charNo = 0; charNo < MAX_CHARS; ++charNo) { 
    if (curNode -> next[charNo] != NULL) { 
      clear(curNode -> next[charNo]);
    }
  }
  delete(curNode);
}

int main () { 
  int tt;
  cin >> tt;
  for (int caseNo = 1; caseNo <= tt; ++caseNo) { 
    root = new Node();
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) { 
      string s;
      cin >> s;
      if ((int) s.size() > 2) { 
        sort(s.begin() + 1, s.end() - 1);
      }
      insert(s);
    }
    int m;
    cin >> m;
    cin.ignore();
    cout << "Case " << caseNo << ":\n";
    for (int i = 0; i < m; ++i) { 
      string s;
      getline(cin, s);
      string curWord = "";
      long long ans = 1;
      for (auto c : s) { 
        if (c == ' ') { 
          if (curWord != "") { 
            if ((int) curWord.size() > 2) { 
              sort(curWord.begin() + 1, curWord.end() - 1);
            }
            ans *= getSimilarCnt(curWord);
          }
          curWord = "";
        } else { 
          curWord += c;
        }
      }
      if (curWord != "") { 
        if ((int) curWord.size() > 2) { 
          sort(curWord.begin() + 1, curWord.end() - 1);
        }
        ans *= getSimilarCnt(curWord);
      }
      cout << ans << '\n';
    }
    clear(root);
  }
  return 0;
}

