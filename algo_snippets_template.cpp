# ----------------------- Snippets -----------------------


snippet regular_4d_adjacent_moves "Regular 4D adjacent Moves" b
array<int, 4> dx = {-1, 0, 1, 0};
array<int, 4> dy = {0, 1, 0, -1};
endsnippet

snippet regular_4d_corner_moves "Regular 4D corner Moves" b
array<int, 4> dx = {-1, 1, 1, -1};
array<int, 4> dy = {1, 1, -1, -1};
endsnippet

snippet regular_4d_square_moves "Regular 4D Square Moves" b
array<int, 4> dx = {0, 0, 1, 1};
array<int, 4> dy = {0, 1, 1, 0};
endsnippet

snippet regular_8d_moves "Regular 8D Moves" b
array<int, 8> dx = {-1, -1, 0, 1, 1, 1, 0, -1};
array<int, 8> dy = {0, 1, 1, 1, 0, -1, -1, -1};
endsnippet

snippet knight_moves "Knight Moves" b
array<int, 8> dx = {-2, -2, 2, 2, -1, 1, -1, 1};
array<int, 8> dy = {-1, 1, -1, 1, 2, 2, -2, -2};
endsnippet

snippet set_cmp "set comparator lambda" b
auto cmp = [&] (array<int, 2> e1, array<int, 2> e2) { 
  return e1[0] >= e2[0];
};
set<array<int, 2>, decltype(cmp)> pq(cmp);
endsnippet

snippet lcm "Lcm Utility" b
auto lcm = [&] (${1:long long} a, $1 b) { 
  return a / __gcd(a, b) * b;
};
endsnippet

snippet valid_cell "Valid cell utility" b
auto inside = [&] (int row, int col) { 
  return 0 <= row and row < n and 0 <= col and col < m;
};
endsnippet

snippet is_power_of_two "Check if a number is power of two or not" b
bool is_power_of_two (long long x) {
  if (x <= 0) {
    return false;
  }
  return (x & (x - 1)) == 0;
}
endsnippet

snippet mod_utility "mod utility" b
const int mod = (int) 1e9 + 7;
int add_mod (int a, int b) { 
  int res = (a + b) % mod;
  res += (res < 0 ? mod : 0);
  return res;
}

int sub_mod (int a, int b) { 
  int res = (a - b) % mod;
  res += (res < 0 ? mod : 0);
  return res;
}

int mult_mod (int a, int b) { 
  int res = (a * 1LL * b) % mod;
  res += (res < 0 ? mod : 0);
  return res;
}
endsnippet


snippet LCS "Longest Common Subsequence in [O(n) Space | O(n * m) Time]" b
// Space Optimized LCS - Space O(n)

#include <bits/stdc++.h>
using namespace std;

int main() {
  string s = "AGGTAB";
  string t = "GXTXAYB"; // Ans = 4
  int n = (int) s.size();
  int m = (int) t.size();
  vector<vector<int>> dp(2, vector<int>(m + 1));
  for (int i = 0; i <= n; ++i) { 
    int k = i & 1;
    for (int j = 0; j <= m; ++j) { 
      if (i == 0 or j == 0) { 
        dp[k][j] = 0;
      } else if (s[i - 1] == t[j - 1]) { 
        dp[k][j] = 1 + dp[k ^ 1][j - 1];
      } else { 
        dp[k][j] = max(dp[k ^ 1][j], dp[k][j - 1]);
      }
    }
  }
  cout << max(dp[1][m], dp[0][m]) << '\n';
  return 0;
}
endsnippet


snippet LIS "Longest Increasing Subsequence" b
// LIS in O(nlog(n))
int LIS (vector<int> const& a) {
  int n = a.size();
  const int inf = 1e9;
  vector<int> dp(n + 1, inf);
  dp[0] = -inf;
  for (int i = 0; i < n; i++) {
    int l = upper_bound(dp.begin(), dp.end(), a[i]) - dp.begin();
    if (dp[l - 1] < a[i] and a[i] < dp[l]) { 
      dp[l] = a[i];
    }
  }
  int ans = 0;
  for (int l = 0; l <= n; l++) {
    if (dp[l] < inf) { 
      ans = l;
    }
  }
  return ans;
}
endsnippet

snippet string_to_int "String to integer utility" b
/* Converts a string to an integer */
template <typename T>
T str_to_int (string x) { 
  T val = 0;
  for (auto d : x) { 
    val = (val * 10) + ((d - '0') % 10);
  }
  return val;
}
endsnippet

snippet count_digits "Count digits utility" b
/* Return the digit count of an integer */
template <typename T>
T count_digits (T x) { 
  T cnt = 0;
  while (x) { 
    x /= 10;
    ++cnt;
  }
  return cnt;
}
endsnippet

snippet distinct_digits "Distinct digits utility" b
/* Returns total number of distinct digits in a integer */
template <typename T>
T distinct_digits (T x) { 
  set<T> st;
  while (x) { 
    st.insert(x % 10);
    x /= 10LL;
  }
  return (T) st.size();
}
endsnippet

snippet intersect "Two objects intersection utility" b
/* intersect<int>(a, b, c, d) 
 * Note : Used for determining if two objects intersects or not.
 */
template<typename T> 
bool intersect (int a, int b, int c, int d) {
  T xOverlap = max((T) 0, min(b, d) - max(a, c));
  return xOverlap > (T) 0;
}
endsnippet

snippet kadanes_algo "Finds the largest subarray sum in O(n)" b
/* Largest sum in O(n) - DP */
/* There are 2 cases: */ 
/* When curSum <= 0: */ 
/*   When some positive number adds to the sum: */ 
/*     This is always profit. */
/*   When some negative number adds to the sum: */ 
/*     This is also always profit. Because, this is atleast better then the only negative number. */
/* When 0 < curSum: */ 
/*   When some positive number adds to the sum: */ 
/*     This is always bad. (Worse than the only negative number); */
/*   When some negative number adds to the sum: */ 
/*     This is also always bad. (Worse than the only negative number); */
/* This is why always make the sum = 0, when it becomes negative. */
auto kadane = [&] () { 
  long long curs = 0;
  long long mx = (long long) -1e17;
  for (int i = 0; i < n - 1; ++i) { 
    mx = max(mx, (curs += a[i]));
    curs = curs < 0 ? 0 : curs;
  }
  return mx;
};
endsnippet

snippet binary_expo "Power Algo" b
/* binary_expo<int>(2, n - 1, m); */
template<typename T, typename X>
T binary_expo (T val, T power, X m) {
  T output = 1;
  while (power) {
    if (power & 1) {
      output = T((output * 1LL * val) % m);
    }
    val = (val * 1LL * val) % m;
    power >>= 1;
  }
  return output;
}
endsnippet

snippet prime_factorization "Prime Factorization" b
template <typename T>
vector<T> factorize(T n) {
  vector<T> factors;
  while (n & 1 ^ 1) {
    factors.push_back(2);
    n >>= 1;
  }
  for (T d = 3; d * d <= n; d += 2) {
    while (!(n % d)) {
      factors.push_back(d);
      n /= d;
    }
  }
  if (n > 1) { 
    factors.push_back(n);
  }
  return factors;
}
endsnippet

snippet fast_factorization "Fast Factorization (Number theory)" b
/* Time complexity: O(n) for sieve + log(n) for each get_factors() query */
/* fast_factorize<int> ff((int) 1e5); */
/* auto factors = ff.get_factors(n); */
int prime_n = 0;
vector<int> lp;
vector<bool> is_prime;
struct linear_sieve {  
  vector<int> p;
  void run_sieve () { 
    for (int i = 2; i <= prime_n; ++i) {
      if (!lp[i]) {
        lp[i] = i;
        p.push_back(i);
      }
      for (int j = 0; i * 1LL * p[j] <= prime_n; ++j) {
        lp[i * p[j]] = p[j];
        if (p[j] == lp[i]) {
          break;
        }
      }
    }
  }
  linear_sieve (int sz) { 
    prime_n = sz;
    lp.resize(prime_n + 1, 0);
  }
  vector<int> get_primes () { 
    return p;
  }
  void gen_isPrime () { 
    is_prime.resize(prime_n + 1, false);
    for (auto num : p) { 
      is_prime[num] = true;
    }
  }
};

template <typename T>
struct fast_factorize { 
  fast_factorize (int n) { 
    linear_sieve sieve(n); 
    sieve.run_sieve();
  }
  /* change this set<T> to multiset<T> according to the question */
  multiset<T> get_factors (int x) { 
    multiset<T> factors;
    while (x != 1) { 
      factors.insert(lp[x]);
      x /= lp[x];
    }
    return factors;
  }
};
endsnippet

# ---------------------------------- Combinatorics ------------------------------- 

snippet ncr_triv "nCr trivial version" b
/* Used when there's no mod used 
 * Time complexity: O(k) */
template <typename T>
T ncr_triv (T n, T k) { 
  T ncr = 1;
  if (n - k < k) { 
    k = n - k;
  }
  for (T i = 0; i < k; ++i) { 
    ncr *= (n - i);
    ncr /= (i + 1);
  }
  return ncr;
}
endsnippet

snippet ncr "Binomial Coefficients" b
/* bin_coeff<int> bcoef(N, M); */
/* bcoef.nCr(n, r); */
template <typename T>
struct bin_coeff { 
  T n, m;
  vector<T> fact;
  void gen_fact () { 
    fact[0] = fact[1] = 1;
    for (int i = 2; i <= n; ++i) { 
      fact[i] = (1LL * fact[i - 1] * i) % m;
    }
  }
  bin_coeff (T n, T m) { 
    this -> n = n;
    this -> m = m;
    fact.resize(n + 1);
    gen_fact();
  }
  T inv (T val, T power) {
    T output = 1;
    while (power) {
      if (power & 1) {
        output = T((output * 1LL * val) % m);
      }
      val = (val * 1LL * val) % m;
      power >>= 1;
    }
    return output;
  }
  T nCr (T N, T R) { 
    return (fact[N] * 1LL * inv((fact[R] * 1LL * fact[N - R]) % m, m - 2)) % m;
  }
};
endsnippet

snippet derangement "Finds the derangement of n elements" b
/* Theory: 
   Definition: Find the number of arrangement of n elements such that no elements stayes in it's initial position.
   Formula: D(n) = (n - 1) * (D(n - 1) + D(n - 2)) */

/* How to use? */
/* memset(derange_dp, -1, sizeof derange_dp); // Putting it before the test case is enough */
/* derangement(n) */

const int N = 1e3;
const int mod = (int) 1e9 + 7;

int derange_dp[N + 1];

int derangement (int n) { 
  if (n == 1) { 
    return 0;
  }
  if (n == 2 or n == 0) { 
    return 1;
  }
  if (derange_dp[n] != -1) { 
    return derange_dp[n];
  }
  return derange_dp[n] = ((n - 1) * 1LL * ((derangement(n - 1) + derangement(n - 2)) % mod)) % mod;
}
endsnippet

snippet matrix_mult "Matrix Multiplication utility" b
/* Time complexity: O(matrix_x_row_size * matrix_y_col_size * matrix_x_col_size) 
 * matrix_mult <data_type> (matrix_x, matrix_y, mod_val) */
template <typename T>
vector<vector<T>> matrix_mult (vector<vector<T>> matx, vector<vector<T>> maty, T m) { 
  int xrow_size = matx.size();
  int yrow_size = maty.size();
  int xcol_size = matx[0].size();
  int ycol_size = maty[0].size();
  vector<vector<T>> ret_mat(xcol_size, vector<T> (yrow_size));
  for (int xr = 0; xr < xrow_size; ++xr) { 
    for (int yc = 0, xc = 0; yc < ycol_size; ++yc, ++xc) { 
      for (int i0 = 0; i0 < xcol_size; ++i0) { 
        ret_mat[xr][xc] += ((matx[xr][i0] * 1LL * maty[i0][yc]) % m);
      }
    }
  }
  return ret_mat;
}
endsnippet

snippet miller_rabin "Miller Rabin primality test utility" b
template<typename T, typename X>
T binary_expo (T val, T power, X m) {
  T output = 1;
  while (power) {
    if (power & 1) {
      output = T((output * 1LL * val) % m);
    }
    val = (val * 1LL * val) % m;
    power >>= 1;
  }
  return output;
}

template <typename T>
bool check_composite(T n, T a, T d, T s) {
  T x = binary_expo<T>(a, d, n);
  if (x == 1 or x == n - 1) { 
    return false;
  }
  for (T r = 1; r < s; r++) {
    x = x * x % n;
    if (x == n - 1) { 
      return false;
    }
  }
  return true;
};

template <typename T>
bool miller_rabin (T n) { 
  if (n < 2) { 
    return false;
  }
  T r = 0, d = n - 1;
  while ((d & 1) ^ 1) {
    d >>= 1, r++;
  }
  for (T a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if (n == a) { 
      return true;
    }
    if (check_composite(n, a, d, r)) { 
      return false;
    }
  }
  return true;
}
endsnippet

snippet fermat "Femat's primality test" b
template <typename T>
bool fermat (T n, int iter=5) {
  if (n < 4) { 
    return n == 2 or n == 3;
  }
  for (int i = 0; i < iter; i++) {
    T a = 2 + rand() % (n - 3);
    if (binary_expo<T>(a, n - 1, n) != 1) { 
      return false;
    }
  }
  return true;
}
endsnippet

snippet ultra_sieve "Ultra memory optimized sieve utility" b
/* 1. This is (Ultra Memory Efficient) Sieve */
const int prime_limit = (int) 1e6;
int mark[prime_limit / 2 / 32 + 7];
/* What is being done?
 *   - Here we're dividing size by 2 because of eliminating
 *       the odd numbers. 
 *   - After that, dividing by 32 because assuming 
 *       every integer as a 32 bit block and using it as a mask
 *       of bits for checking a number corresponding to that block. 
 * TODO: # set the (prime_limit) variable at first
 *       # call (the ultra_sieve()) function
 *       # Check if a number if prime or not: 
 *         - is_prime(x) */

#define is_set(x) (mark[x / 2 / 32] & (1 << ((x / 2) % 32)))
#define set_bit(x) (mark[x / 2 / 32] |= (1 << ((x / 2) % 32)))

template <typename T>
bool is_prime (T x) { 
  return x == 2 or ((x & 1) and !is_set(x));
}

void ultra_sieve () { 
  set_bit(0);
  set_bit(1);
  for (int i = 3; i * i <= prime_limit; i += 2) { 
    if (!is_set(i)) { 
      for (int j = i * i; j <= prime_limit; j += i + i) { 
        set_bit(j);
      }
    }
  }
}
endsnippet

snippet sieve "Sieve Utility" b
/** 1. sieve_util sieve((int) 1e3); 
  * 2. sieve.run_sieve();
  * 3. vector<int> primes = sieve.get_primes<int>(50);
  */
int prime_n = 0;
vector<bool> is_prime;
struct sieve_util {  
  sieve_util (int sz) { 
    prime_n = sz;
    is_prime.resize(prime_n + 1, true);
  }
  void run_sieve () { 
    is_prime[0] = is_prime[1] = false;
    for (long long i = 2; i * i <= prime_n; i++) {
      if (is_prime[(int) i]) {
        for (long long j = i * i; j <= prime_n; j += i) {
          is_prime[(int) j] = false;
        }
      }
    }
  }
  template <typename T>
  vector<T> get_primes (int lim) { 
    vector<T> generated_prime;
    for (int i = 1; i <= lim; ++i) { 
      if (is_prime[i]) { 
        generated_prime.push_back(i);
      }
    }
    return generated_prime;
  }
};
endsnippet

snippet linear_sieve "Linear Sieve Utility" b
/* const int N = (int) 1e5; */
/* linear_sieve sieve(N); */ 
/* sieve.run_sieve(); */
/* auto p = sieve.get_primes(); */
/* sieve.gen_isPrime(); */
int prime_n = 0;
vector<bool> is_prime;
struct linear_sieve {  
  vector<int> p, lp;
  /* lp[i] defines the lowest prime factor of i */
  void run_sieve () { 
    for (int i = 2; i <= prime_n; ++i) {
      if (!lp[i]) {
        lp[i] = i;
        p.push_back(i);
      }
      for (int j = 0; i * 1LL * p[j] <= prime_n; ++j) {
        lp[i * p[j]] = p[j];
        if (p[j] == lp[i]) {
          break;
        }
      }
    }
  }
  linear_sieve (int sz) { 
    prime_n = sz;
    lp.resize(prime_n + 1, 0);
  }
  vector<int> get_primes () { 
    return p;
  }
  void gen_isPrime () { 
    is_prime.resize(prime_n + 1, false);
    for (auto num : p) { 
      is_prime[num] = true;
    }
  }
};
endsnippet

snippet find_divisors "Finding Divisors Algo" b
/* auto d = find_divisors<int>(n); */
template<typename T> 
vector<T> find_divisors (T n) {
  vector<T> divisors;
  for (T i = 1; i * 1LL * i <= n; ++i) {
    if (!(n % i)) {
      divisors.push_back(i);
      if (n / i != i) {
        divisors.push_back(n / i);
      }
    }
  }
  return divisors;
}
endsnippet

snippet primality_check "primality_check" b 
bool primality_check (int x) {
  for (int d = 2; d * d <= x; d++) {
    if (x % d == 0) {
      return false;
    }
  }
  return true;
}
endsnippet


snippet policy_based_data_structure "Policy based data strucuture" b
/** 1. Firstly, place the header files and namespace and set the data type and comparator.
 *  2. ordered_set<int> X;
 *  3. X.insert(8);
 *  4. *X.find_by_order(1) 
 *        Note : finds the kth largest or the kth smallest element (counting from zero)
 *              i.e. The element at the position i (powerful)
 *  5. X.order_of_key(3) 
 *       Note : finds the number of items in a set that are strictly smaller than our item
 *              i.e. The position of the current element (powerful)
 *  Note : This will exactly work like set, multiset, map [also can use their functinalities.
 *    -> Not possible : erasing elements with their value (in multiset)
 */
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = 
  tree <T,
  null_type, // use mapped_type for map
  less<T>, // comparator (less/greater) & type [less_equal for multiset]
  rb_tree_tag,
  tree_order_statistics_node_update
>;

// Returns the position if found, else returns size
auto pbds_lower_bound = [&] (int el) { 
  return (int) ms.order_of_key(el);
};
// Returns the position if found, else returns size
auto pbds_upper_bound = [&] (int el) { 
  return (int) ms.order_of_key(el + 1);
};
endsnippet

snippet to_binary "Binary representation of a number" b
/* 1. to_binary<int>(leading_zeroes, n) */
template<typename T>
void to_binary_utility (T x, string& bin) {
  if (x > 1) { 
    to_binary_utility<T>(x >> 1, bin);
  }
  bin += ('0' + (x % 2));
}
template<typename T>
string to_binary (int leading_zeroes, T x) { 
  string bin = "";
  to_binary_utility<T>(x, bin);
  while ((int) bin.size() < leading_zeroes) { 
    bin = '0' + bin;
  }
  return bin;
}
endsnippet

snippet dsu "Disjoint Set Union" b 
/* disjoint_set<int> dsu(n + 1); */
/* dsu.make_set(u, v); */
vector<int> par, siz;
template<typename T>
struct disjoint_set { 
  int n;
  T find_set(T v) {
    if (par[v] == v) {
      return v;
    }
    return par[v] = find_set(par[v]);
  }
  void init(T v) {
    par[v] = v;
    siz[v] = 1;
  }
  disjoint_set (int n) { 
    this -> n = n;
    siz.assign(n + 1, 0);
    par.assign(n + 1, 0);
    for (int u = 1; u <= n; ++u) {
      init(u);
    }
  }
  void make_set(T a, T b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
      if (siz[a] < siz[b]) {
        swap(a, b);
      }
      par[b] = a;
      siz[a] += siz[b];
    }
  }
  T find_group_size(T a) { 
    a = find_set(a);
    return siz[a];
  }
};
endsnippet

snippet  fenwick_tree "Fenwick Tree" b 
/* 1. fenwick_tree<long long> bit; // to create the struct */
/* 2. bit.build_empty_tree(n); // for empty tree */
/* 3. bit.range_sum(a[i], n) // for range_sum */
/* 4. bit.update_by_adding(a[i], 1); // To update an index with a new value */
template<typename T>
struct fenwick_tree {
  vector<T> tree;
  /* Array size must be 1 indexed. */
  /* use this when only setting up the tree w/ the array is necessary */
  void get_tree (vector<T> a) { 
    tree = a;
  }
  /* Array size must be 1 indexed. */
  /* use this when building empty tree is necessary */
  void build_empty_tree (int n) { 
    tree.assign(n + 1, 0);
  }
  /* Array size must be 1 indexed. */
  /* builds the tree from array - (a) */
  /* use this when only setting up the tree w/ the array is NOT necessary */
  void build_tree (vector<T> a) { 
    tree = a;
    int n = (int) a.size() - 1;
    for (int i = 1; i <= n; ++i) {
      int idx = i;
      idx = idx + (idx & -idx);
      if (idx <= n) { 
        tree[idx] += tree[i];
      }
    }
  }
  /* returns the prefix sum till idx */
  T sum (int idx) { 
    T result = 0;
    while (idx) { 
      result += tree[idx];
      idx -= (idx & -idx);
    }
    return result;
  }
  /* returns the sum of segment l to r (inclusive) */
  T range_sum (int l, int r) { 
    return sum(r) - sum(l - 1);
  }
  /* updates an element at position idx */
  void update_by_adding (int idx, T val) { 
    int n = (int) tree.size() - 1;
    while (idx <= n) { 
      tree[idx] += val;
      idx = idx + (idx & -idx);
    }
  }
};
endsnippet

snippet  sqrt_decomp "Sqrt Decomposition Utlity" b 
// 0 based indexing
// Time: O(sqrt(N)) each query
/* Initialize: sqrt_decomp<int> sd(a); */
/* Query: cout << sd.query(l, r) << '\n'; // 0 based indexing (l, r */
/* Update: sd.update(idx, val) // 0 based indexing (idx) */

template <typename T> 
struct sqrt_decomp { 
  int n, blk_sz;
  vector<T> a, block;
  void preprocess () { 
    int blk_idx = -1;
    // Time: O(N)
    for (int i = 0; i < n; ++i) { 
      if (i % blk_sz == 0) { 
        blk_idx += 1;
      }
      block[blk_idx] += a[i];
    }
  }
  sqrt_decomp (vector<T> a) { 
    this -> a = a;
    n = (int) a.size();
    blk_sz = (int) sqrtl(n);
    /* Change the initial value according to the question */
    /* e.g. (int) 1e9 for finding minimum */
    block.assign(blk_sz + 1, 0);
    preprocess();
  }
  // Time: O(3 * sqrt(N)) = sqrt(N)
  /* returns sum/min/max/cnt of an array in the range (l, r) */
  T query (int l, int r) { 
    /* Change this initial value according to the question */
    /* e.g. (int) 1e9 for finding minimum */
    T sum = (T) 0;
    while (l < r and l % blk_sz != 0 and l != 0) { 
      sum += a[l++];
    }
    while (l + blk_sz - 1 <= r) { 
      sum += block[l / blk_sz];
      l += blk_sz;
    }
    while (l <= r) { 
      sum += a[l++];
    }
    return sum;
  }
  // Time: Point update O(1)
  void update (int idx, T val) { 
    int block_num = idx / blk_sz;
    block[block_num] += val - a[idx];
    a[idx] = val;
  }
};
endsnippet

snippet mos_algo "Mo's algorithm Utility" b 
/* Why this algo: This algo is used to answer those queries which are dynamic e.g. (distinct elems). Which cannot be done using segment tree. */ 
/* Time Complexity: O((N + Q) F sqrt(Q)). Where F = time of add-remove functions. */
/*  				-> Firstly, if all of the left index are at same block then, for one block we will move our right index at most N times. Then, for every block we will have O(N * sqrt(N)) times. */
/* 					-> Secondly, for each query our left pointer can move at most sqrt(N) times. Because, each block has at most sqrt(N) cells. So, for Q query there will be O(Q * sqrt(N)) calls at most. */
/* 					-> Hence, O(N * sqrt(N) + Q * sqrt(N)) = O((N + Q) * sqrt(N)) by taking sqrt(N) common from both sides. */
/* mos_algo<int> mo(Q, a, N); */
/* auto ans = mo.query_answers(); */
/* Before using this, make sure to store all the queries (0 based indexing) in a vector this manner vector{l, r, i} */

template <typename T> 
struct mos_algo { 
  int q;
  vector<int> a;
  vector<T> frq;
  int tot_block; 
  /* Important: This is the answer variable */ 
  /* Change according to the question */
  T curr_ans = 0;
  /* array<T, 3> {l, r, id} */
  vector<array<int, 3>> Q;
  void proc () { 
    /* sorts the queries in asc order */
    sort(Q.begin(), Q.end(), [&] (array<int, 3> x, array<int, 3> y) { 
      int blockl = x[0] / tot_block;
      int blockr = y[0] / tot_block;
      if (blockl != blockr) { 
        return blockl < blockr;
      }
    /* Optimization: Here, by changing the add block in ascending order and the even block in descending order. The right pointer will have to move less. This will eliminate the extra movement of the right pointer which was wasteful. right pointer movement (before) i: 1, 2, 3, 1, 2, 3, 1, 2, 3. Right pointer movement (now) i: 1, 2, 3, 3, 2, 1, 1, 2, 3, 3, 2, 1. */ 
      return (x[0] / tot_block & 1) ? x[1] < y[1] : y[1] < x[1];
    });
  }
  mos_algo (vector<array<int, 3>> Q, vector<int> a, int N) { 
    this -> Q = Q;
    this -> a = a;
    q = (int) Q.size();
    frq.assign(N + 1, 0);
    tot_block = (int) sqrtl(q);
    proc();
  }
  void add (int pos) { 
    /* Change according to the question */
    if (++frq[a[pos]] == 1) { 
      curr_ans += 1;
    }
  }
  void remove (int pos) { 
    /* Change according to the question */
    if (!--frq[a[pos]]) { 
      curr_ans -= 1;
    }
  }
  vector<T> query_answers () { 
    int cur_l = 0;
    int cur_r = -1;
    vector<T> ans(q);
    for (int i = 0; i < q; ++i) { 
      int l = Q[i][0];
      int r = Q[i][1];
      int id = Q[i][2];
      /* Spread section and try adding elements to the answer*/
      while (l < cur_l) { 
        cur_l -= 1;
        add(cur_l);
      }
      while (cur_r < r) { 
        cur_r += 1;
        add(cur_r);
      }
      /* Shrinking section and try removing elements from the answer*/
      while (cur_l < l) { 
        remove(cur_l);
        cur_l += 1;
      }
      while (r < cur_r) { 
        remove(cur_r);
        cur_r -= 1;
      }
      ans[id] = curr_ans; 
    }
    return ans;
  }
};
endsnippet

snippet sparse_table "Sparse table utility" b 
/* Used for answering queries, but can answer R(Min/Max)Q in O(1) */
/* sparse_table<int> st(a, N); */
/* cout << st.min_query(l, r) << '\n'; */
template <typename T> 
struct sparse_table { 
  int N;
  int n, k;
  vector<T> a;
  vector<T> logs;
  vector<vector<T>> st;
  void gen_logs () { 
    logs[1] = 0;
    for (int i = 2; i <= N; i++) { 
      logs[i] = logs[i/2] + 1;
    }
  }
  void proc () { 
    st[0] = a;
    for (int i = 1; i <= k; ++i) { 
      for (int j = 0; j + (1 << i) - 1 < n; ++j) {
        /* Change this line according the question */
        st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
      }
    }
  }
  sparse_table (vector<T> a, int N) { 
    this -> a = a;
    this -> N = N;
    n = (int) a.size();
    logs.assign(N + 1, 0);
    gen_logs();
    k = logs[n];
    st.assign(k + 1, vector<T>(n + 1, 0));
    proc();
  }
  /* This function is used for only min/max query O(1); */
  T min_query (int l, int r) { 
    int p = logs[r - l + 1];
    return min(st[p][l], st[p][r - (1 << p) + 1]);
  }
  /* This function is used for the rest of the query O(log(n)) */
  T sum_query (int l, int r) { 
    T sum = 0;
    for (int i = k; i >= 0; --i) { 
      if ((1 << i) <= r - l + 1) { 
        sum += st[i][l];
        l += 1 << i;
      }
    }
    return sum;
  }
};
endsnippet

snippet  segment_tree "Segment Tree" b 
/** 1. segment_tree<long long> seg_tree(a);
  * 2. seg_tree.build(1, 0, n - 1);
  * 3. Note : Make sure that the segment tree type and the 
       vector type must mathc. E.g If, struct segment_tree <long long> 
	   then, vector must be vector<long long>
  *	4. Note : While using index for answer. Make sure to use them as (0 based)
  * 5. now, you're good to go.
 **/
template <typename T>
struct segment_tree {
  int n;
  vector<T> a, tree;
  /* Used to create the tree array */
  segment_tree (vector<T> cpy) { 
    a = cpy;
    n = (int) a.size();
    tree.assign(n << 2, 0);
  };
  /* used to build the tree */ 
  void build (int node, int l, int r) {
    if (l == r) { 
      tree[node] = a[l];
      return;
    }
    int mid = (l + r) >> 1;
    build(node << 1, l, mid);
    build((node << 1) + 1, mid + 1, r);
    tree[node] = tree[node << 1] + tree[(node << 1) + 1];
  }
  /* point sum or range sum */ 
  T sum (int node, int start, int end, int l, int r) { 
    if (end < l or r < start) {
      return 0;
    }
    if (l <= start and end <= r) { 
      return tree[node];
    }
    int mid = (start + end) >> 1;
    T left_sum = sum(node << 1, start, mid, l, r);
    T right_sum = sum((node << 1) + 1, mid + 1, end, l, r);
    return left_sum + right_sum;
  }
  /* point updating value / adding value */
  void update (int node, int start, int end, int id, T val) { 
    if (start == end) {
      tree[node] = val;
      return;
    }
    int mid = (start + end) >> 1;
    if (id <= mid) { 
      update(node << 1, start, mid, id, val);
    } else {
      update((node << 1) + 1, mid + 1, end, id, val);
    }
    tree[node] = tree[node << 1] + tree[(node << 1) + 1];
  }
};
endsnippet

snippet 2D_segment_tree "2D segment tree utilities" b
/** 1. _2D_segment_tree<long long> _2D_seg_tree(a);
  * 2. _2D_seg_tree.buildx(1, 0, n - 1);
  * 3. Note : Make sure that the segment tree type and the 
       vector type must mathc. E.g If, struct _2D_segment_tree <long long> 
	   then, vector must be vector<long long>
  *	4. Note : While using index for answer. Make sure to use them as (0 based)
  * 5. now, you're good to go.
 **/
template <typename T> 
struct _2D_segment_tree { 
  int n, m; 
  vector<vector<T>> a, t;
  _2D_segment_tree (vector<vector<T>> a) { 
    this -> a = a;
    this -> n = (int) a.size();
    this -> m = (int) a[0].size();
    t.assign(n << 2, vector<T>(m << 2));
  }
  void build_y (int vx, int lx, int rx, int vy, int ly, int ry) {
    if (ly == ry) {
      if (lx == rx) { 
        t[vx][vy] = a[lx][ly];
      } else { 
        t[vx][vy] = t[(vx << 1)][vy] + t[(vx << 1) + 1][vy];
      }
    } else {
      int my = (ly + ry) >> 1;
      build_y(vx, lx, rx, (vy << 1), ly, my);
      build_y(vx, lx, rx, (vy << 1) + 1, my + 1, ry);
      t[vx][vy] = t[vx][(vy << 1)] + t[vx][(vy << 1) + 1];
    }
  }
  /* Prepares the _2D segment tree 
   * _2D_seg_tree.build_x(1, 0, n - 1); */
  void build_x (int vx, int lx, int rx) {
    if (lx != rx) {
      int mx = (lx + rx) >> 1;
      build_x((vx << 1), lx, mx);
      build_x((vx << 1) + 1, mx + 1, rx);
    }
    build_y(vx, lx, rx, 1, 0, m - 1);
  }
  T sum_y (int vx, int vy, int tly, int try_, int ly, int ry) {
    if (ly > ry) { 
      return (T) 0;
    }
    if (ly == tly && try_ == ry) { 
      return t[vx][vy];
    }
    int tmy = (tly + try_) >> 1;
    return sum_y(vx, (vy << 1), tly, tmy, ly, min(ry, tmy))
       + sum_y(vx, (vy << 1) + 1, tmy + 1, try_, max(ly, tmy + 1), ry);
  }
  /* Returns the sum of a sub-matrix from, 
   * [(left_x, left_y) top_left corner] to [(right_x, right_y) bottom_right corner]
   * _2D_seg_tree.sum_x(1, 0, n - 1, --left_x, --right_x, --left_y, --right_y) -> 0 based indexing */
  T sum_x (int vx, int tlx, int trx, int lx, int rx, int ly, int ry) {
    if (lx > rx) { 
      return 0;
    }
    if (lx == tlx && trx == rx) { 
      return sum_y(vx, 1, 0, m - 1, ly, ry);
    }
    int tmx = (tlx + trx) >> 1;
    return sum_x((vx << 1), tlx, tmx, lx, min(rx, tmx), ly, ry)
       + sum_x((vx << 1) + 1, tmx + 1, trx, max(lx, tmx + 1), rx, ly, ry);
  }
  void update_y (int vx, int lx, int rx, int vy, int ly, int ry, int x, int y, T new_val) {
    if (ly == ry) {
      if (lx == rx) { 
        t[vx][vy] = new_val;
      } else { 
        t[vx][vy] = t[(vx << 1)][vy] + t[(vx << 1) + 1][vy];
      }
    } else {
      int my = (ly + ry) >> 1;
      if (y <= my) { 
        update_y(vx, lx, rx, (vy << 1), ly, my, x, y, new_val);
      } else { 
        update_y(vx, lx, rx, (vy << 1) + 1, my + 1, ry, x, y, new_val);
      }
      t[vx][vy] = t[vx][(vy << 1)] + t[vx][(vy << 1) + 1];
    }
  }
  /* Updates a particular cell of the matrix - (x_axis, y_axis)
   * _2D_seg_tree.update_x(1, 0, n - 1, --left_x, --left_y, new_val); */
  void update_x (int vx, int lx, int rx, int x, int y, T new_val) {
    if (lx != rx) {
      int mx = (lx + rx) >> 1;
      if (x <= mx) { 
        update_x((vx << 1), lx, mx, x, y, new_val);
      } else { 
        update_x((vx << 1) + 1, mx + 1, rx, x, y, new_val);
      }
    }
    update_y(vx, lx, rx, 1, 0, m - 1, x, y, new_val);
  }
};
endsnippet

snippet lazy_propagation "Lazy Propagation" b
/** 1. struct lazy_propagation <int64_t>lazy_prop(a);
  * 2. lazy_prop.build(1, 0, n - 1);
  * 3. now, you're good to go.
 **/
template <typename T>
struct lazy_propagation {
  struct info {
    T sum = 0, prop = 0;
  };
  int n;
  vector<T> a;
  vector<info> tree;
  lazy_propagation (vector<T> cpy) { 
    a = cpy;
    n = (int) a.size();
    tree.resize(4 * n);
  };
  void build (int node, int l, int r) {
    if (l == r) { 
      tree[node].sum = a[l];
      return;
    }
    int mid = (l + r) >> 1;
    build(node << 1, l, mid);
    build((node << 1) + 1, mid + 1, r);
    tree[node].sum = tree[node << 1].sum + tree[(node << 1) + 1].sum;
  }
  T sum (int node, int start, int end, int l, int r, T carry = 0) { 
    if (end < l or r < start) {
      return 0;
    }
    if (l <= start and end <= r) { 
      return tree[node].sum + (((end - start) + 1) * carry);
    }
    int mid = (start + end) >> 1;
    T left_sum = sum(node << 1, start, mid, l, r, carry + tree[node].prop);
    T right_sum = sum((node << 1) + 1, mid + 1, end, l, r, carry + tree[node].prop);
    return left_sum + right_sum;
  }
  void update (int node, int start, int end, int l, int r, T val) { 
    if (end < l or r < start) {
      return;
    }
    if (l <= start and end <= r) {
      tree[node].sum += ((end - start) + 1) * val;
      tree[node].prop += val;
      return;
    }
    int mid = (start + end) >> 1;
    update(node << 1, start, mid, l, r, val);
    update((node << 1) + 1, mid + 1, end, l, r, val);
    tree[node].sum = tree[node << 1].sum + tree[(node << 1) + 1].sum + (((end - start) + 1) * tree[node].prop);
  }
};
endsnippet

snippet Rectangle "Rectangle Utility" b
/* 1. Rect<int> r1(x1, y1, x2, y2);
 * 2. r1.area()
 * 3. intersected_area<int>(r1, r2)
 * 4. intersect<int>(r1, r2)
 * 5. array<int, 4> Ta = intersected_axis<int64_t>(r1, r2);
 */
template<typename T> 
struct Rect {
  T x1, y1, x2, y2;
  Rect () {}
  Rect (T x1, T y1, T x2, T y2) { 
    this -> x1 = x1;
    this -> x2 = x2;
    this -> y1 = y1;
    this -> y2 = y2;
  }
  T area () {
    return (y2 - y1) * (x2 - x1); 
  }
};

/* Used to determine the intersected area of two rectangles. */
template<typename T> 
T intersected_area (Rect<T> p, Rect<T> q) {
  T xOverlap = max((T) 0, min(p.x2, q.x2) - max(p.x1, q.x1));
  T yOverlap = max((T) 0, min(p.y2, q.y2) - max(p.y1, q.y1));
  return xOverlap * yOverlap;
}

/* Used to detect if there is any intersection between two rectangles */
/* or not? */
template<typename T> 
bool intersect (Rect<T> p, Rect<T> q) {
  T xOverlap = max((T) 0, min(p.x2, q.x2) - max(p.x1, q.x1));
  return xOverlap > (T) 0;
}

/* If using this function you've to make sure that there is */ 
/* definitely a intersection between these two rectangles. */
/* Which can be done using intersect<int>(r1, r2) function. */
template<typename T> 
array<T, 4> intersected_axis (Rect<T> p, Rect<T> q) {
  array<T, 4> axis;
  T Nx1 = max(p.x1, q.x1);
  T Nx2 = min(p.x2, q.x2);
  T Ny1 = max(p.y1, q.y1);
  T Ny2 = min(p.y2, q.y2);
  axis[0] = Nx1, axis[1] = Ny1;
  axis[2] = Nx2, axis[3] = Ny2;
  return axis;
}
endsnippet

snippet y_combinator "y_combinator Utility" b
/* 1. auto fact = y_combinator([&](auto fact, int n) -> int { */
/*      return n == 1 ? 1 : n * fact(n - 1); */
/*    }); */  
/* 2. cout << fact(a) << endl; */
/* 3. Note : Name of the recurse function and the calling function can be same. */
namespace std {
  template<class U>
  class y_combinator_result {
    U func;
	public:
	  template<class T>
	  explicit y_combinator_result(T &&arg): func(std::forward<T>(arg)) {}
	  template<class ...Args>
	  decltype(auto) operator()(Args &&...args) {
		return func(std::ref(*this), std::forward<Args>(args)...);
	  }
  };
  template<class U>
  decltype(auto) y_combinator(U &&arg) {
    return y_combinator_result<std::decay_t<U>>(std::forward<U>(arg));
  }
}
endsnippet

snippet count_inversions "counting inversions" b
/* counting inversions : */ 
/* 1. long long ans = count_inversions<long long>(a, n); */
template <typename T, typename U>
T merge_sides (vector<U>& ar, vector<U>& dmy, int st, int m, int en) {
  T inv_count = 0;
  int i = st, j = m, k = st;
  while (i <= m - 1 and j <= en) {
    if (ar[i] <= ar[j]) {
      dmy[k++] = ar[i++];
    }
    else {
      dmy[k++] = ar[j++];
      inv_count += (m - i);
    }
  }
  while (i <= m - 1) {
    dmy[k++] = ar[i++];
  }
  while (j <= en) {
    dmy[k++] = ar[j++];
  }
  for (i = st; i <= en; i++) {
    ar[i] = dmy[i];
  }
  return inv_count;
}
template <typename T, typename U>
T merge_sort (vector<U>& ar, vector<U>& dmy, int st, int en) {
  T inv = 0;
  if (st < en) {
    int m = ((st + en) >> 1);
    inv += (T) merge_sort<T>(ar, dmy, st, m);
    inv += (T) merge_sort<T>(ar, dmy, m + 1, en);
    inv += (T) merge_sides<T>(ar, dmy, st, m + 1, en);
  }
  return inv;
}
template <typename T, typename U>
T count_inversions (vector<U>& ar, int n) {
  vector<U> dmy(n);
  return merge_sort<T>(ar, dmy, 0, n - 1);
}
endsnippet

snippet dijkstra "Dijkstra (Single Source Shortest Path)" b
/* Used to extract the shortest path from source(u) to destination(v) */
/* Time complexity: O(V + E log V) */
/* dijkstra<int> dij(g, n, --src); */
/* dij.proc_tab(); */
/* cout << dij.get_dist(--v) << '\n'; */
/* auto path = dij.get_path(v); */
template <typename T> 
struct dijkstra { 
  int n;
  int src;
  // Change this (inf) according to the question
  const T inf = (T) 1e16;
  vector<int> par, seen;
  vector<T> dist;
  vector<vector<array<int, 2>>> g;
  dijkstra (vector<vector<array<int, 2>>> g, int n, int src) { 
    this -> g = g;
    this -> n = n;
    this -> src = src;
    // Remove this (par) if not needed
    par.assign(n, -1);
    seen.assign(n, false);
    dist.assign(n, inf);
  }
  void proc_tab () { 
    multiset<array<T, 2>> ms;
    dist[src] = 0;
    ms.insert({0, src});
    while (!ms.empty()) { 
      auto u = *ms.begin();
      ms.erase(ms.begin());
      if (!seen[u[1]]) { 
        seen[u[1]] = true;
        for (auto ch : g[u[1]]) { 
          if (dist[u[1]] + ch[1] < dist[ch[0]]) { 
            dist[ch[0]] = dist[u[1]] + ch[1];
            /* Here saving the previous node as parent if this is giving less cost */
            par[ch[0]] = u[1];
            ms.insert({dist[ch[0]], ch[0]});
          }
        }
      }
    }
  }
  T get_dist (int dest) { 
    return dist[dest];
  }
  vector<int> get_path (int dest) { 
    vector<int> path;
    for (int v = dest; v != -1; v = par[v]) { 
      path.push_back(v + 1);
    }
    reverse(path.begin(), path.end());
    return path;
  }
};
endsnippet

snippet bellman_ford "Bellman ford" b
/* Time complexity: O(V * E) */
/* Add edges both ways for undirected graph */
/* g.push_back({u, v, w}); */
/* g.push_back({v, u, w}); */
int cyc_node = -1;
const int inf = (int) 1e9;
vector<int> dist(n + 1, inf);
vector<int> par(n + 1, -1);
auto check_neg_cycle = [&] () { 
  if (cyc_node == -1) { 
    return printf("No neg cycle\n"), 0;
  }
  int u = cyc_node;
  for (int i = 1; i <= n; ++i) { 
    u = par[u];
  }
  vector<int> path;
  for (int cur = u; ; cur = par[cur]) { 
    path.push_back(cur);
    if (1 < (int) path.size() and cur == u) { 
	  break;
    }
  }
  reverse(path.begin(), path.end());
  for (auto p : path) { 
    printf("%d ", p);
  }
  printf("\n");
  return 0;
};
auto bellman_ford = [&] (int src) { 
  dist[src] = 0;
  for (int i = 1; i <= n; ++i) { 
    cyc_node = -1;
    for (int j = 0; j < m; ++j) { 
	  int u = g[j][0];
	  int v = g[j][1];
	  int w = g[j][2];
	  if (dist[u] < inf) { 
	    if (dist[u] + w < dist[v]) { 
		  dist[v] = max(-inf, dist[u] + w);
		  par[v] = u;
		  cyc_node = v;
	    }
	  }
    }
    dbg("two", cyc_node);
  }
  check_neg_cycle();
};
bellman_ford(1);
endsnippet

snippet spfa "Bellman ford (improved version)" b
  /* Shortest Path Faster Algorithm */
  /* Improved version of Bellman Ford */
  /* Used when negative weight is involed but negative cycle is not involved */
  /* This can work faster in most of the cases */
  /* Time complexity: On average O(m), worst case O(n * m) */
  /* Change next 2 line to long long according to question */
  const int inf = (int) 1e9;
  vector<int> dist(n + 1, inf);
  auto spfa = [&] (int src) { 
    /* Take input in the form g[u].push_back({v, w}) */
    queue<int> q;
    dist[src] = 0;
    q.push(src);
    bool neg_cycle = false;
    inque[src] = true;
    vector<int> cnt(n + 1);
    vector<bool> inque(n + 1);
    while (!q.empty()) { 
      int u = q.front();
      q.pop();
      inque[u] = false;
      for (auto ch : g[u]) { 
        if (dist[u] + ch[1] < dist[ch[0]]) { 
          dist[ch[0]] = dist[u] + ch[1];
          if (!inque[ch[0]]) { 
            q.push(ch[0]);
            inque[ch[0]] = true;
            if (n < ++cnt[ch[0]]) { 
              neg_cycle = true;
              // negative cycle
            }
          }
        }
      }
      if (neg_cycle) {
        break;
      }
    }
  };
endsnippet

snippet floyd_warshall "Floyd Warshall (all pair shortest path)" b
/* Time complexity: O(n ^ 3) */
auto floyd_warshall = [&] () { 
  /* init the (d) array, if there doesn't exists a path b/w u-v then set them to infinity */ 
  const int inf = (int) 1e9;
  for (int k = 1; k <= n; ++k) {
    for (int i = 1; i <= n; ++i) { 
      for (int j = 1; j <= n; ++j) { 
       /* if there exists both of these path or not */
        if (d[i][k] < inf and d[k][j] < inf) { 
          d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        }
      }
    }
  }
};
endsnippet

snippet kruskals "Kruskals algo (MST)" b
/* Before this, make sure to write the dsu algo */
/* Time complexity: O(mlog(m)) - only for sorting, others done in constant time */
disjoint_set<int> dsu(n + 1);
auto kruskals = [&] () { 
  long long min_cost = 0;
  /* The edges must be sorted in asc according to their weights */
  sort(p.begin(), p.end());
  for (int i = 0; i < m; ++i) { 
    /* p[i][0] = cost, p[i][1] = u, p[i][2] = v; */
    if (dsu.find_set(p[i][1]) != dsu.find_set(p[i][2])) { 
      min_cost += p[i][0];
      dsu.make_set(p[i][1], p[i][2]);
    }
  }
  return min_cost;
};
endsnippet

snippet directed_cycle "Directed graph (cycle finding)" b
  /* time complexity: O(N + M) and O(M) if only one component */
  /* Detects cycle in a directed graph */
  int cyc_end = -1;
  int cyc_start = -1;
  vector<int> color(n + 1), parent(n + 1);
  auto dfs = y_combinator([&](auto dfs, int v) -> bool {
    /* color gray */
    color[v] = 1;
    for (auto u : g[v]) { 
      if (!color[u]) { 
        parent[u] = v;
        if (dfs(u)) { 
          return true;
        }
      } else if (color[u] == 1) { 
        cyc_start = u;
        cyc_end = v;
        return true;
      }
    }
    /* color black */
    color[v] = 2;
    return false;
  });  
  auto print_path = [&] () { 
    vector<int> path;
    path.push_back(cyc_start);
    for (int v = cyc_end; v != cyc_start; v = parent[v]) { 
      path.push_back(v);
    }
    path.push_back(cyc_start);
    reverse(path.begin(), path.end());
    for (auto p : path) { 
      printf("%d ", p);
    }
    printf("\n");
  };
  auto detect_cycle = [&] () { 
    for (int v = 1; v <= n; ++v) { 
      if (!color[v] and dfs(v)) { 
        // Has a cycle
        break;
      }
    }
    if (cyc_start == -1) { 
      return printf("No cycle\n"), 0;
    }
    return print_path(), 0;
  };
  detect_cycle();
endsnippet

snippet lca "binary lifting (lca)" b
/* Time complexity: Build O(nlog(n)), Query O(log(n)); */
/* binary_lifting bl(n, m, g); */
/* bl.lca(u, v); */
/* bl.get_dist(u, v); */
struct binary_lifting { 
  int n, m;
  vector<int> lvl;
  vector<vector<int>> g;
  vector<vector<int>> par;
  void dfs (int v, int l, int p) { 
    lvl[v] = l;
    par[v][0] = p;
    for (auto ch : g[v]) { 
      if (ch != p) { 
        dfs(ch, l + 1, v);
      }
    }
  }
  void init () { 
    dfs(1, 0, -1);
    const int logn = __lg(n);
    for (int i = 1; i <= logn; ++i) { 
      for (int j = 1; j <= n; ++j) { 
        if (par[j][i - 1] != -1) { 
          int p = par[j][i - 1];
          par[j][i] = par[p][i - 1];
        }
      }
    }
  }
  binary_lifting (int n, int m, vector<vector<int>> g) {
    this -> n = n;
    this -> m = m;
    this -> g = g;
    lvl.assign(n + 1, 0);  
    const int logn = __lg(n);
    par.assign(n + 1, vector<int>(logn + 1, -1));
    init();
  }
  int lca (int u, int v) { 
    if (lvl[v] < lvl[u]) { 
      swap(v, u);
    }
    int d = lvl[v] - lvl[u];
    while (d) { 
      int logd = __lg(d);
      v = par[v][logd];
      d -= (1 << logd);
    }
    if (u == v) { 
      return u;
    }
    int logn = __lg(n);
    for (int i = logn; i >= 0; --i) { 
      if (par[u][i] != -1 and par[u][i] != par[v][i]) { 
        u = par[u][i];
        v = par[v][i];
      }
    }
    return par[u][0];
  }
  int get_dist (int u, int v) { 
    int com_ances = lca(u, v);
    return lvl[u] + lvl[v] - (lvl[com_ances] << 1);
  }
};
endsnippet

snippet max_flow "Max-Flow Algo (Graphs)" b
/* 1. Before starting, fill the 2D capacity array with each edges capacity */
/* 2. And, fill the adjacency list (g) */
/* 3. Initialize (inf) variable */
vector<vector<int>> g(n + 1);
vector<vector<int>> capacity(n + 1, vector<int>(n + 1));
auto bfs = [&](int s, int t, vector<int>& parent) {
  fill(parent.begin() + 1, parent.end(), -1);
  parent[s] = -2;
  queue<pair<int, int>> q;
  q.push({s, inf});
  while (!q.empty()) {
    int cur = q.front().first;
    int flow = q.front().second;
    q.pop();
    for (int next : g[cur]) {
      if (parent[next] == -1 && capacity[cur][next]) {
        parent[next] = cur;
        int new_flow = min(flow, capacity[cur][next]);
        if (next == t) { 
          return new_flow;
        }
        q.push({next, new_flow});
      }
    }
  }
  return 0;
};
auto maxflow = [&](int s, int t) {
  int flow = 0;
  vector<int> parent(n + 1);
  int new_flow;
  while (new_flow = bfs(s, t, parent)) {
    flow += new_flow;
    int cur = t;
    while (cur != s) {
      int prev = parent[cur];
      capacity[prev][cur] -= new_flow;
      capacity[cur][prev] += new_flow;
      cur = prev;
    }
  }
  return flow;
};
cout << maxflow(source, sink) << '\n';
endsnippet

snippet kmp "Knuth Morris Pratt Algo (strings)" b
/* Total complexity: O(n + m) */
/* Application (string problems) : */ 
/*  1. Used to extract matched positions */
/*  2. Used to know if we have a match or not */
/* kmp<int> km(full_string, pattern_to_search_for); */
/* auto ids = km.pos(); */
template <typename T> 
struct kmp {
  int n, m;
  string s, t;
  vector<T> tab;
  // Creating the prefix length table
  void proc () { 
    int i = 0;
    for (int j = 1; j < m;) { 
      if (t[i] == t[j]) { 
        tab[j] = i + 1;
        i += 1, j += 1;
      } else { 
        if (i) { 
          i = tab[i - 1];
        } else { 
          j += 1;
        }
      }
    }
  }
  // initializing everything
  kmp (string s, string t) {
    this -> s = s;
    this -> t = t;
    n = (T) s.size();
    m = (T) t.size();
    tab.assign(m, 0);
    proc();
  }
  // Returns all the starting positions where we have a match
  // If we have a match we continue, 
  // Otherwise, we look in the previous index of the table to save time.
  vector<T> pos () { 
    int i = 0;
    int j = 0;
    vector<T> ids;
    while (i < n) { 
      if (s[i] == t[j]) { 
        i += 1, j += 1;
      } else { 
        if (j) { 
          j = tab[j - 1];
        } else { 
          i += 1;
        }
      }
      // If pattern found take the index
      if (j == m) { 
        ids.push_back(i - m);
        j = tab[j - 1];
      }
    }
    return ids;
  }
};
endsnippet

snippet z_algo "Z Algorithm (string)" b
/* auto z = z_algo<int>(s); */
/* Time complexity: O(n + n) */
/* Note: every (i) denotes, what is the max length prefix mathces with the string starting from (i) */
/* Z algo exactly works like KMP but, most of the times probelems are more intuitive with Z algo. */ 
template <typename T>
vector<T> z_algo (string s) {
  int n = (int) s.size();
  vector<T> z(n);
  z[0] = n;
  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    /* if we're in a already computed segment, then use the computed answer to save time */
    if (i <= r) {
      z[i] = min(r - i + 1, z[i - l]);
    }
    /* just keep on going while have a match */
    while (i + z[i] < n and s[z[i]] == s[i + z[i]]) { 
      z[i] += 1;
    }
    /* if we have computed a segment for the first time, update it */
    if (r < i + z[i] - 1) { 
      l = i, r = i + z[i] - 1;
    }
  }
  return z;
}
endsnippet

snippet manachers "Manacher's algo utility (string algo)" b
/* Time complexity: O(N) */
/* While solving this problem always try to solve this on the basis of the generated answer it is returning */
/* Which means, always try to solve on the basis of converted string -> #a#b#a# */
/* Return the length of a palindrome from left side, defining (i) as the middle of that palindrome*/
/* manachers<int> man(s); */
/* auto ans = man.ret_ans(); */
template <typename T> 
struct manachers { 
  int n;
  vector<int> p;
  void manac_odd (string s) { 
    n = (int) s.size();
    s = "(" + s + ")";
    p.assign(n + 2, 0);
    int l = 1, r = 1;
    for (int i = 1; i <= n; ++i) { 
      p[i] = max(0, min(r - i, p[l + (r - i)]));
      while (s[i - p[i]] == s[i + p[i]]) { 
        p[i] += 1;
      }
      if (r < i + p[i]) { 
        l = i - p[i];
        r = i + p[i];
      }
    }
  }
  manachers (string t) { 
    string s = "";
    for (auto c : t) { 
      s += string("#") + c;
    }
    manac_odd(s + "#");
  }
  vector<T> ret_ans () { 
    return vector<T>(p.begin() + 1, p.end() - 1);
  }
};
endsnippet

snippet trie "Trie utility (string algo)" b
/* Time complexity (construction): */ 
/*   * number of nodes. Which depends on matched prefix. */
/*   * the more prefix-match, the better. */
/* Time complexity (per query): */ 
/*   * length of the asked string */ 
/* Trie trie; */
/* trie.insert(s); */
/* cout << (trie.search(t) ? "YES\n" : "NO\n") << '\n'; */
/* trie.del(); */
/* Note: useful for searching a string is present or not */
struct Trie { 
  struct node { 
    bool endmark;
	/* Change the size to (10) if working with digits */
    node* next[26];
    node () { 
      endmark = false;
	  /* Change the limit to 10 if working with digits */
      for (int i = 0; i < 26; ++i) { 
        next[i] = NULL;
      }
    }
  } * root;
  /* Trie tri; */
  Trie () { 
    root = new node();
  }
  /* tri.insert(s); */
  /* inserts a string the the Trie */
  void insert (string s) { 
    node* curr = root;
    for (auto ch : s) { 
      /* change 'a' according to the problem statement */
      int id = ch - 'a';
      if (curr -> next[id] == NULL) { 
        curr -> next[id] = new node();
      }
      curr = curr -> next[id];
    }
    curr -> endmark = true;
  }
  /* return if a string is present in the list or not */
  /* cout << (tri.search(t) ? "YES\n" : "NO\n") << '\n'; */
  bool search (string s) { 
    node* curr = root;
    for (auto ch : s) { 
      /* change 'a' according to the problem statement */
      int id = ch - 'a';
      if (curr -> next[id] == NULL) { 
        return false;
      }
      curr = curr -> next[id];
    }
    return curr -> endmark;
  }
  void del_node (node* curr) { 
	/* Change the limit to 10 if working with digits */
    for (int i = 0; i < 26; ++i) { 
      if (curr -> next[i]) { 
        del_node(curr -> next[i]);
      }
    }
    delete(curr);
  }
  /* tri.del(); */
  /* deletes, all the nodes. Useful in reducing memory */
  void del () { 
    del_node(root);
  }
};
endsnippet

snippet string_hash "String hashing utility" b
/* Time complexity: Size of the string O(s.size()) */
/* string_hash<int> hash((int) 1e5); */
/* hash.comp_hash(s); */
/* Note: -> Used to convert a string to a integer in a form of hash value. */ 
/*          To, reduce the complexity of comparing strings. Which gets reduced from O(s.size()) to O(1) */
/* 	     -> If there's atleast 10^6 strings, then there'll be definitely collisions. */
/*	     -> To reduce collisions, two (p) can be used. Ex: p1 = 53, p2 = 31. Do everything similar like p1. Then, */
/* 		    to compare check if both of there (p1 and p2) values are exactly similar or not. (Set can also be used).*/

/* Imp: An crucial property of hash function, if hash value of all equal string (in length also) are retrieved from */ 
/*      a prefix sum or something. Then, if we multiply all of them with a particular powers in descending order to balance them and then mod them, then we */
/*      get all the similar hash values. */
/*      Example: cur = (cur * 1LL * p_pow[n - j]) % mod; */
template <typename T> 
struct string_hash { 
  int n;
  int p = 53;
  int m = (int) 1e9 + 7;
  vector<T> p_pow;
  void gen_pow () { 
    p_pow[0] = 1;
    for (int i = 1; i < n; i++) { 
      p_pow[i] = (p_pow[i - 1] * 1LL * p) % m;
    }
  }
  /* Receives the max size of a string can be */ 
  string_hash (int n) { 
    this -> n = n;
    p_pow.assign(n, 0);
    gen_pow();
    dbg(p_pow);
  }
  /* Computes hash value of a given string */
  T comp_hash (string s) { 
    T hash_val = 0;
    for (int i = 0; i < (int) s.size(); ++i) { 
      /* Change 'a' according to the problem statement */
      hash_val = (hash_val + ((((s[i] - 'a') + 1) * 1LL * p_pow[i]) % m)) % m;
    }
    return hash_val;
  }
};
endsnippet

snippet bst_construction "BST construction" b
/* BST constructing */
struct node { 
  int data;
  node *left;
  node *right;
};

node *root = NULL;
auto insert_in_bst = [&] (int x) { 
  node *cur = new node();
  cur -> data = x;
  cur -> left = NULL;
  cur -> right = NULL;
  if (root == NULL) { 
    root = cur;
  } else { 
    node *cpy = root;
    while (true) { 
      if (cur -> data <= cpy -> data) { 
        if (cpy -> left == NULL) { 
          cpy -> left = cur;
          break;
        } else { 
          cpy = cpy -> left;
        }
      } else { 
        if (cpy -> right == NULL) { 
          cpy -> right = cur;
          break;
        } else { 
          cpy = cpy -> right;
        }
      }
    }
  }
};

for (int i = 1; i <= n; ++i) { 
  int x;
  scanf("%d", &x);
  insert_in_bst(x);
}
endsnippet

snippet bst_insertion_after_construction "BST insertion after construction" b
/* BST insertion after constructing */
auto insert_after_constructing = [&] () { 
  node *cur = new node();
  cur -> data = k;
  cur -> left = NULL;
  cur -> right = NULL;
  node *cpy = root;
  while (true) { 
    if (last < cpy -> data) { 
      if (cpy -> left == NULL) { 
        cpy -> left = cur;
        break;
      } else { 
        cpy = cpy -> left;
      }
    } else { 
      if (cpy -> right == NULL) { 
        cpy -> right = cur;
        break;
      } else { 
        cpy = cpy -> right;
      }
    }
  }
};
endsnippet

snippet bst_check "BST check" b
/* BST check */
auto is_bst = y_combinator([=](auto is_bst, node *root) -> bool {
  if (root == NULL) { 
    return false;
  }
  if (root -> data == k) { 
    return true;
  }
  if (k <= root -> data) { 
    return is_bst(root -> left);
  }
  return is_bst(root -> right);
});  
endsnippet

snippet file_utilities "Write & read from files" b
/* create file stream to load a file*/
fstream newfile;
/* open the file */
newfile.open("tpoint.txt",ios::out);  // open a file to perform write operation using file object
/* Write in file */
if(newfile.is_open()) //checking whether the file is open
{
  newfile<<"Tutorials point \n";   //inserting text
  newfile.close();    //close the file object
}

/* open the file */
newfile.open("tpoint.txt",ios::in); //open a file to perform read operation using file object
/* Read from file */
if (newfile.is_open()){   //checking whether the file is open
  string tp;
  while(getline(newfile, tp)){ //read data from file object and put it into string.
     cout << tp << "\n"; //print the data of the string
  }
  newfile.close(); //close the file object.
}
endsnippet


# ------------------------------------ geometry ------------------------ 
snippet collinear "Checks if three points are collinear or not" b
// Formula: (y2 - y1) (x3 - x2) = (y3 - y2) (x2 - x1)
bool collinear (auto a, auto b, auto c) {
  return (b[1] - a[1]) * (c[0] - b[0]) == (c[1] - b[1]) * (b[0] - a[0]);
}
endsnippet
