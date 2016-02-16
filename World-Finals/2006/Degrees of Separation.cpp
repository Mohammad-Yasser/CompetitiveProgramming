#include <bits/stdc++.h> 
using namespace std;
typedef long long ll;

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif
	int p, r;
	int dist[51][51];
	int cs = 0;
	while (cin >> p >> r, p) {
		memset(dist, 0x3f, sizeof dist);
		for (int i = 0; i < p; ++i)
			dist[i][i] = 0;

		unordered_map<string, int> mp;
		pair<string, string> edges[r];
		for (auto &edge : edges)
			cin >> edge.first >> edge.second, mp[edge.first], mp[edge.second];
		int id = 0;
		for (auto &x : mp)
			x.second = id++;
		for (auto &edge : edges) {
			int f = mp[edge.first], s = mp[edge.second];
			dist[f][s] = dist[s][f] = 1;
		}

		for (int k = 0; k < p; ++k)
			for (int i = 0; i < p; ++i)
				for (int j = 0; j < p; ++j)
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

		cout << "Network " << ++cs << ": ";
		int mx = 0;
		for (int i = 0; i < p; ++i)
			for (int j = 0; j < p; ++j)
				mx = max(mx, dist[i][j]);

		if (mx > 50)
			cout << "DISCONNECTED\n\n";
		else
			cout << mx << "\n\n";

	}
}
