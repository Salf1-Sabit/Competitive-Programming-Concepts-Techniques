/** Author: Salfi_Sabit
 * Instituion: University of Information Technology & Sciences **/

#include <bits/stdc++.h>
using namespace std;

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

int main() {
  const int N = (int) 1e4;
  sieve_util sieve(N); 
  sieve.run_sieve();
  vector<int> primes = sieve.get_primes<int>(N);
  int n = (int) primes.size();
  vector<int> dp(n);
  for (int i = 0; i < n; ++i) { 
    dp[i] = primes[i] + (i ? dp[i - 1] : 0);
  }
  map<int, int> ans;
  for (int i = 0; i < n; ++i) { 
    for (int j = i; j < n; ++j) { 
      ans[dp[j] - (i ? dp[i - 1] : 0)] += 1;
    }
  }
  while (true) { 
    cin >> n;
    if (n == 0) {
      break;
    }
    cout << ans[n] << '\n';
  }
  return 0;
}
