#include <bits/stdc++.h> 
using namespace std;

string s[3];

int memo[1000001][2][2];

int pos[28][28][28][2][2][2][2];

const int MOD = 1e9 + 9;

void preCalc(int c1, int c2, int c3, bool pre1, bool pre2) {
	int st[3] = { c1, c2, c3 }, ed[3] = { c1, c2, c3 };

	if (c1 == 27) st[0] = 1, ed[0] = 26;
	if (c2 == 27) st[1] = 1, ed[1] = 26;
	if (c3 == 27) st[2] = 1, ed[2] = 26;

	for (int i = st[0]; i <= ed[0]; ++i)
		for (int j = st[1]; j <= ed[1]; ++j)
			for (int k = st[2]; k <= ed[2]; ++k)
				pos[c1][c2][c3][pre1][pre2][pre1 or i != j][pre2 or j != k] += (pre1 or i <= j)
				  && (pre2 or j <= k);

}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

	for (int i = 0; i < 28; ++i)
		for (int j = 0; j < 28; ++j)
			for (int k = 0; k < 28; ++k)
				for (int pre1 = 0; pre1 < 2; ++pre1)
					for (int pre2 = 0; pre2 < 2; ++pre2)
						preCalc(i, j, k, pre1, pre2);

	int t;
	cin >> t;
	while (t--) {

		cin >> s[0] >> s[1] >> s[2];
		s[0] += string(1e6 - s[0].size(), 'a' - 1);
		s[1] += string(1e6 - s[1].size(), 'a' - 1);
		s[2] += string(1e6 - s[2].size(), 'a' - 1);

		memo[1000000][1][1] = 1;

		for (int ind = 1e6 - 1; ind >= 0; --ind)
			for (int pre1 = 0; pre1 < 2; ++pre1)
				for (int pre2 = 0; pre2 < 2; ++pre2) {
					int c[3] = { s[0][ind] - 'a' + 1, s[1][ind] - 'a' + 1, s[2][ind]
					  - 'a' + 1 };

					if (c[0] == '?' - 'a' + 1) c[0] = 27;
					if (c[1] == '?' - 'a' + 1) c[1] = 27;
					if (c[2] == '?' - 'a' + 1) c[2] = 27;

					memo[ind][pre1][pre2] = ((1LL * pos[c[0]][c[1]][c[2]][pre1][pre2][0][0]
					  * memo[ind + 1][0][0] % MOD)
					  + (1LL * pos[c[0]][c[1]][c[2]][pre1][pre2][0][1] * memo[ind + 1][0][1] % MOD)
					  + (1LL * pos[c[0]][c[1]][c[2]][pre1][pre2][1][0] * memo[ind + 1][1][0] % MOD)
					  + (1LL * pos[c[0]][c[1]][c[2]][pre1][pre2][1][1] * memo[ind + 1][1][1] % MOD)) % MOD;
				}

		cout << memo[0][0][0] << '\n';

	}
}
