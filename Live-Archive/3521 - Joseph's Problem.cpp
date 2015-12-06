#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
/*
 *
 * Idea:
 * Let x be a number between k / div and k / (div +1), then k / x == div. --> (1)
 * Let's recall the equation of the % operator: x % y = x - y * x / y ; --> (2)
 * Let x and (x + 1) be between k / div and k / (div +1) , then from (1) and (2):
 * 	k % x == k - x * k / x == k - x * div,
 * 	k % (x+1) == k - (x + 1) * k / (x + 1) == k - (x + 1)  * div,
 * 	Hence, (k % x) - (k % (x + 1)) == div,
 * 	Therefore, {k % i | i <= k / div && i > k / (div + 1) } is an arithmetic progression
 * 	whose the starting number is k % (k / div) and difference is div.
 *
 * Cool, right? :D
 * However, to calculate the answer this way, one should loop on div from 1 to k !
 *
 * No, you can observe that when div reaches sqrt(k), only sqrt(k) numbers are left,
 * which you can calculate their answers directly.
 *
 */

ll solve(int n, int k) {
	ll ans = max(1LL * k * (n - k), 0LL);
	int div = max(1, k / n);
	while (1LL * div * div < k) {
		int startingTerm = min(k / div, n);
		if (!startingTerm) return 0;
		int nTerms = startingTerm - k / (div + 1);
		ans += 1LL * nTerms * (2 * (k % startingTerm) + (nTerms - 1) * div) / 2;
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
	while (cin >> n >> k)
		cout << solve(n, k) << '\n';

}
