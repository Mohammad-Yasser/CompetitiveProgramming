#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 102;

struct Node {
	ll x, y, z, r;
} nodes[N];

double dist(Node x, Node y) {
	return max(0.0, sqrt((x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y)
	  + (x.z - y.z) * (x.z - y.z)) - x.r - y.r);

}

long double d[N];
int vis[N], visID;

int n;

void dijkstra() {
	++visID;
	int curr, nxt = n - 2;
	fill(d, d + n, numeric_limits<long double>::max());
	d[nxt] = 0;
	while (nxt != -1) {
		curr = nxt;
		vis[curr] = visID;
		nxt = -1;
		for (int j = 0; j < n; ++j)
			if (vis[j] != visID) {
				d[j] = min(d[j], d[curr] + dist(nodes[curr], nodes[j]));
				if (nxt == -1 or d[j] < d[nxt]) nxt = j;
			}
	}
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif

	int cs = 0;
	while (cin >> n && n != -1) {
		n += 2;

		for (int i = 0; i + 2 < n; ++i)
			cin >> nodes[i].x >> nodes[i].y >> nodes[i].z >> nodes[i].r;

		for (int i = n - 2; i < n; ++i)
			cin >> nodes[i].x >> nodes[i].y >> nodes[i].z, nodes[i].r = 0;

		dijkstra();

		cout << "Cheese " << ++cs << ": Travel time = " << (ll) round(10 * d[n - 1]) << " sec\n";
	}

}
