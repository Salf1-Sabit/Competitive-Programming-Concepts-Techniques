// Blog link: http://rachitiitr.blogspot.com/2017/06/wavelet-trees-wavelet-trees-editorial.html

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 1; // DEFINE size of array
const int MAX = 1e7 + 1; // DEFINE max element
int a[N]; // input array

struct wavelet_tree {
	int lo, hi;
	wavelet_tree *l, *r;
	vector<int> b;
	vector<int> c; // c holds the prefix sum of elements
 
	// number of elements are in range [x,y]
	// array indices are [from, to)
	wavelet_tree (int *from, int *to, int x, int y) {
		lo = x, hi = y;
		if(to <= from) { 
      return;
    }
		if (hi == lo) {
			b.reserve(to - from + 1);
      b.push_back(0);
			c.reserve(to-from+1);
      c.push_back(0);
      for(auto it = from; it != to; it++) {
        b.push_back(b.back() + 1);
        c.push_back(c.back() + *it);
      }
			return;
		}
		int mid = (lo + hi) / 2;
		auto f = [mid] (int x) {
			return x <= mid;
		};
		b.reserve(to - from + 1);
		b.push_back(0);
		c.reserve(to - from + 1);
		c.push_back(0);
		for(auto it = from; it != to; it++) {
			b.push_back(b.back() + f(*it));
			c.push_back(c.back() + *it);
		}
		// see how lambda function is used here	
		auto pivot = stable_partition(from, to, f);
		l = new wavelet_tree(from, pivot, lo, mid);
		r = new wavelet_tree(pivot, to, mid + 1, hi);
	}
 
	// kth smallest element in [l, r]
	int kth (int l, int r, int k){
		if (r < l) { 
      return 0;
    }
		if (lo == hi) { 
      return lo;
    }
		int inLeft = b[r] - b[l-1];
		int lb = b[l - 1]; // amount of nos in first (l-1) nos that go in left 
		int rb = b[r]; // amount of nos in first (r) nos that go in left
		if (k <= inLeft) {
      return this -> l -> kth(lb + 1, rb , k);
    }
		return this -> r -> kth(l - lb, r - rb, k - inLeft);
	}
 
	// count of nos in [l, r] Less than or equal to k
	int LTE (int l, int r, int k) {
		if (r < l or k < lo) {
      return 0;
    }
		if (hi <= k) {
      return r - l + 1;
    }
		int lb = b[l - 1], rb = b[r];
		return this -> l -> LTE(lb + 1, rb, k) + this -> r -> LTE(l - lb, r - rb, k);
	}
 
	// count of nos in [l, r] equal to k
	int count (int l, int r, int k) {
		if (l > r or k < lo or k > hi) {
      return 0;
    }
		if (lo == hi) {
      return r - l + 1;
    }
		int lb = b[l - 1], rb = b[r], mid = (lo + hi) / 2;
		if (k <= mid) {
      return this -> l -> count(lb + 1, rb, k);
    }
		return this -> r -> count(l - lb, r - rb, k);
	}
 
	// sum of nos in [l ,r] less than or equal to k
	int sumk (int l, int r, int k) {
		if (r < l or k < lo) {
      return 0;
    }
		if (hi <= k) {
      return c[r] - c[l - 1];
    }
		int lb = b[l - 1], rb = b[r];
		return this -> l -> sumk(lb + 1, rb, k) + this -> r -> sumk(l - lb, r - rb, k);
	}
 
	~wavelet_tree(){
		delete l;
		delete r;
	}
};


int main () {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {  
    cin >> a[i+1];
  }
	wavelet_tree T (a+1, a+n+1, 1, MAX);
  int q;
	cin >> q;
	while(q--){
		int x;
		cin >> x;
    int l, r, k;
		cin >> l >> r >> k;
		if(x == 0){
			//kth smallest
			cout << "Kth smallest: ";
			cout << T.kth(l, r, k) << endl;
		}
		if(x == 1){
			//less than or equal to K
			cout << "LTE: ";
			cout << T.LTE(l, r, k) << endl;
		}
		if(x == 2){
			//count occurence of K in [l, r]
			cout << "Occurence of K: ";
			cout << T.count(l, r, k) << endl;
		}
		if(x == 3){
			//sum of elements less than or equal to K in [l, r]
			cout << "Sum: ";
			cout << T.sumk(l, r, k) << endl;
		}
	}
	return 0;
} 
 
