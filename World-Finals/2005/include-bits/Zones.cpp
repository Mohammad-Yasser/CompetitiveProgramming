#include <bits/stdc++.h> 
using namespace std;

int arr[21];

vector<int> common[11];
int comm[11];
inline void nxt(int &mask) {
	int cntZeroes = ~mask & 1;
	for (int i = 1; i < 32; ++i) {
		cntZeroes += (~mask >> i) & 1;
		if ((~mask >> i) & 1 & (mask >> (i - 1))) {
			mask |= 1 << i;
			for (int j = i - 1; j >= 0; --j, --cntZeroes)
				mask &= ~((cntZeroes > 0) << j), mask |= (cntZeroes < 1) << j;
			return;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("test.in", "r", stdin);
#endif

	int n, c, m, cs = 0;
	while (cin >> n >> c, n) {
		for (int i = 0; i < n; ++i)
			cin >> arr[i];
		cin >> m;
		for (int i = 0; i < m; ++i) {
			int t;
			cin >> t;
			common[i].resize(t);
			for (int &x : common[i])
				cin >> x, --x;
			cin >> comm[i];
		}
		vector<int> ans(c);
		int mx = 0;
		for (int i = 0; i < c; ++i)
			ans[i] = i;
		for (int mask = (1 << c) - 1; mask < (1 << n); nxt(mask)) {
			int total = 0;
			vector<int> tmp;

			for (int i = 0; i < n; ++i)
				if ((mask >> i) & 1) total += arr[i], tmp.push_back(i + 1);

			for (int i = 0; i < m; ++i) {
				bool fnd = 0;
				for (int x : common[i])
					if ((mask >> x) & 1) {
						total -= comm[i] * fnd;
						fnd = 1;
					}
			}
			if (total > mx or total == mx && tmp < ans)
			  mx = total, ans = tmp;
		}
		cout << "Case Number  " << ++cs << "\nNumber of Customers: " << mx
		  << "\nLocations recommended:";
		for (int x : ans)
			cout << ' ' << x;
		cout << "\n\n";
	}

}
