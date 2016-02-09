#include <bits/stdc++.h> 
using namespace std;
typedef long long ll;

int n;
const int N = 15;
pair<int, int> pos[N], wall[2 * N + 2][N];

int memo[1 << N];

int currWall;
inline int dist(int i, int j) {
	return abs(pos[i].first - wall[currWall][j].first)
	  + abs(pos[i].second - wall[currWall][j].second);
}

int dp(int mask) {
	int &ret = memo[mask];
	if (ret != -1) return ret;
	ret = INT_MAX;
	int ind = __builtin_popcount(mask);
	if (ind == n) return ret = 0;
	for (int i = 0; i < n; ++i)
		if (!((mask >> i) & 1))
		  ret = min(ret, dist(ind, i) + dp(mask | (1 << i)));
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif

	int cs = 0;
	while (cin >> n, n) {
		for (int i = 0; i < n; ++i)
			cin >> pos[i].first >> pos[i].second, --pos[i].first, --pos[i].second;
		int ans = INT_MAX;

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j)
				wall[i][j] = {i,j}, wall[i+n][j] = {j,i};
			wall[2 * n][i] = {i,i};
			wall[2 * n + 1][i] = {i,n-1-i};
		}

		for (currWall = 0; currWall < 2 * n + 2; ++currWall) {
			memset(memo, -1, sizeof memo);
			ans = min(ans, dp(0));
		}
		cout << "Board " << ++cs << ": " << ans << " moves required.\n\n";
	}

}
