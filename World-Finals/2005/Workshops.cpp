#include <bits/stdc++.h> 
using namespace std;

int n, m;
pair<int, int> workshops[1003], rooms[1003];
bool used[1003];
int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif

	int cs = 0;
	while (cin >> n, n) {
		memset(used, 0, sizeof used);
		int p = 0;
		for (int i = 0; i < n; ++i)
			cin >> workshops[i].first >> workshops[i].second;
		sort(workshops, workshops + n);
		cin >> m;
		for (int i = 0; i < m; ++i) {
			cin >> rooms[i].first;
			int h, mnt;
			char c;
			cin >> h >> c >> mnt;
			rooms[i].second = (h - 14) * 60 + mnt;
		}
		int tw = 0, tp = 0;
		for (int i = n - 1; i >= 0; --i) {
			int ind = -1;
			for (int j = 0; j < m; ++j)
				if (!used[j] && rooms[j].first >= workshops[i].first
				  && rooms[j].second >= workshops[i].second
				  && (ind == -1 or rooms[j].second < rooms[ind].second))
				  ind = j;
			if (ind == -1)
				++tw, tp += workshops[i].first;
			else
				used[ind] = 1;
		}

		cout << "Trial " << ++cs << ": " << tw << ' ' << tp << "\n\n";

	}
}
