#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll solve(int n, int k) {
	ll ans = max(1LL * k * (n - k), 0LL);
	int div = max(1, k / n);
	while (1LL * div * div < k) {
		int a = min(k / div, n);
		if (!a) return 0;
		int nTerms = a - k / (div + 1);
		ans += 1LL * nTerms * (2 * (k % a) + (nTerms - 1) * div) / 2;
		++div;
	}
	div = k / div;

	for (int i = 1; i <= div; ++i)
		ans += k % i;

	return ans;
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

	int n, k;
	while (cin >> n >> k) {
		cout << solve(n, k) << '\n';
	}
}
