#include <bits/stdc++.h> 
using namespace std;
typedef long long ll;

const int N = 25;

int load[N][N];
pair<int, int> conf[N];
int pos[2][N];

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int n;
	while (cin >> n, n) {
		memset(load, 0, sizeof load);
		for (int i = 0; i < n; ++i) {
			int u;
			cin >> u;
			--u;
			int v, l, k;
			cin >> k;
			while (k--)
				cin >> v >> l, load[u][v - 1] = l;
		}
		int confCnt = 0, c, tmp;
		while (cin >> c, c) {
			for (int i = 0; i < 2; ++i)
				for (int j = 0; j < n; ++j) {
					cin >> tmp;
					pos[i][tmp - 1] = j;
				}
			int tot = 0;
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
					tot += load[i][j] * (abs(pos[0][i] - pos[1][j]) + 1);
			conf[confCnt++] = {tot , c};
		}
		sort(conf, conf + confCnt);
		cout << "Configuration Load\n";
		for (int i = 0; i < confCnt; ++i)
			cout << setw(5) << conf[i].second << "         " << conf[i].first << '\n';

	}
}
