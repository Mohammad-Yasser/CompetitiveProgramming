#include <bits/stdc++.h> 
using namespace std;
#define popCnt(x) (__builtin_popcountll(x))
typedef unsigned long long ll;

const int nPrimes = 17;

int primes[nPrimes];

inline void genPrimes() {
	int idx = 0;
	for (char i = 2; idx < nPrimes; ++i) {
		bool isPrime = 1;
		for (char j = 2; j < i; ++j)
			isPrime &= i % j != 0;
		if (isPrime) primes[idx++] = i;
	}
}

ll currN = 1, currK = 1;
int idx, sum;
const ll K = LLONG_MAX;
int cnt[nPrimes];

unordered_map<ll, ll> mp;

inline ll calc(ll a, ll b, ll c) {
	ll g = __gcd(a, c);
	a /= g, c /= g;
	g = __gcd(b, c);
	b /= g;
	if (a > K / b) return -1;
	return a * b;
}
ll newN;
void bt() {
	if (currK != 1) {
		ll &tmp = mp.insert( { currN, K }).first->second;
		tmp = min(tmp, currK);
	}

	for (char i = 0; i < 2; ++i) {
		idx += i;
		newN = calc(currN, sum + 1, cnt[idx] + 1);
		if ((!idx or cnt[idx] < cnt[idx - 1]) && currK <= K / primes[idx]
		  && newN != -1) {
			++sum;
			++cnt[idx];
			ll tmp = currN;
			currN = newN;
			currK *= primes[idx];
			bt();
			currN = tmp;
			currK /= primes[idx];
			--sum;
			--cnt[idx];
		}
		idx -= i;
	}

}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif

	genPrimes();
	bt();

	ll n;
	while (cin >> n)
		cout << n << ' ' << mp[n] << '\n';

}
