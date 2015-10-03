#include<bits/stdc++.h>
using namespace std;

const int N = 3e4, M = 3e4;

int nodeCnt, src, snk;

int head[N], from[M], nxt[M], to[M], cap[M],
  cost[M];
int edgeCnt;
int ID;
int vis[N];
void init() {
	edgeCnt = 0;
	memset(head, -1, sizeof(int) * nodeCnt);
}
void addEdge(int f, int t, int cst, int cp) {
	nxt[edgeCnt] = head[f];
	to[edgeCnt] = t;
	cap[edgeCnt] = cp;
	cost[edgeCnt] = cst;
	from[edgeCnt] = f;
	head[f] = edgeCnt++;
}
void addBi(int f, int t, int cst, int cp) {
	addEdge(f, t, cst, cp);
	addEdge(t, f, -cst, 0);
}
#define INF 1e9
int dist[N], flow[N], parent[N];
int spfa() {
	queue<int> Q;
	++ID;
	memset(dist, 0x3f, sizeof(dist[0]) * nodeCnt);
	memset(flow, 0, sizeof(flow[0]) * nodeCnt);
	dist[src] = 0;
	flow[src] = INF;
	Q.push(src);
	vis[src] = ID;

	int cur ;
	while (!Q.empty()) {
		cur = Q.front();
		Q.pop();
		vis[cur] = 0;
		for (int j = head[cur]; j != -1; j = nxt[j]) {
			int node = to[j];
			if (cap[j] && dist[node] > dist[cur] + cost[j]) {
				dist[node] = dist[cur] + cost[j];
				parent[node] = j;
				flow[node] = min(flow[cur], cap[j]);
				if (vis[node] != ID)
				  Q.push(node), vis[node] = ID;
			}
		}
	}

	if (flow[snk]) {
		//found path
		for (int i = snk; i != src; i = from[parent[i]]) {
			int j = parent[i];
			cap[j] -= flow[snk];
			cap[j ^ 1] += flow[snk];
		}
	}
	return flow[snk];
}

typedef pair<int, int> pr;

pr minCostMaxFlow() {

	int cst = 0;
	int flw = 0;

	if (src == snk)
	  return pr(0, INF);

	while (spfa()) {
		cst += dist[snk] * flow[snk];
		flw += flow[snk];
	}

	return pr(cst, flw);

}

struct Triple {
	int s, t, p, ind;

	bool operator <(const Triple &other) const {
		if (s == other.s) return ind < other.ind;
		return s < other.s;
	}
};

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifdef MyPC
	freopen("in.txt", "r", stdin);
#else
#define endl '\n'
#endif

	int t;
	cin >> t;

	while (t--) {
		int n;
		cin >> n;
		Triple prop[n];
		for (int i = 0; i < n; ++i)
			cin >> prop[i].s >> prop[i].t >> prop[i].p, prop[i].ind = 0;

		sort(prop, prop + n);
		for (int i = 0; i < n; ++i)
			prop[i].ind = i;

		int j = 2;

		nodeCnt = 2 * n + 3;

		init();

		for (int i = 0; i < n; ++i, j += 2) {
			addBi(j, j + 1, -prop[i].p, 1);
			addBi(j, j + 2, 0, 2);
			Triple t = { prop[i].t + 1, 0, 0, 0 };
			int tmp;
			auto it = lower_bound(prop + i + 1, prop + n, t);
			if (it == prop + n)
				tmp = 1;
			else
				tmp = 2 * (it->ind + 1);
			addBi(j + 1, tmp, 0, 2);
		}
		addBi(0, 2, 0, 2);

		src = 0, snk = 1;

		cout << -minCostMaxFlow().first << endl;

	}

}
