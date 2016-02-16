#include <bits/stdc++.h> 
using namespace std;
typedef long long ll;
#define getP(x) (x + 2)
#define getC(x) (x + 2 + p)
const int N = 103, M = N * (N - 1), INF = 1e3;
const int SRC = 0, SNK = 1;
struct Edge {
	int from, to, nxt, cap, cost;
};
int head[N];
Edge edges[M];
int edgeCnt;

void init() {
	memset(head, -1, sizeof head);
	edgeCnt = 0;
}

void addEdge(int u, int v, int cap, int cost) {
	edges[edgeCnt] = {u,v,head[u],cap,cost};
	head[u] = edgeCnt++;
}

void addBi(int u, int v, int cap, int cost) {
	addEdge(u, v, cap, cost);
	addEdge(v, u, 0, -cost);
}

bool inQ[N] ;
int dist[N], flow[N], parent[N];

pair<int, int> bellman() {
	queue<int> q;
	memset(dist, 0x3f, sizeof dist);
	memset(flow, 0, sizeof flow);
	dist[SRC] = 0, flow[SRC] = INF;
	q.push(SRC);
	inQ[SRC] = 1;
	while (!q.empty()) {
		int curr = q.front();
		q.pop();
		inQ[curr] = 0;
		for (int edgeID = head[curr]; edgeID != -1; edgeID = edges[edgeID].nxt) {
			Edge &edge = edges[edgeID];
			int node = edge.to;
			if (edge.cap && dist[node] > dist[curr] + edge.cost) {
				dist[node] = dist[curr] + edge.cost;
				parent[node] = edgeID;
				flow[node] = min(flow[curr], edge.cap);
				if (!inQ[node])
				  inQ[node] =1, q.push(node);
			}
		}
	}

	if (flow[SNK]) {
		for (int node = SNK; node != SRC; node = edges[parent[node]].from) {
			int edgeID = parent[node];
			edges[edgeID].cap -= flow[SNK];
			edges[edgeID ^ 1].cap += flow[SNK];
		}
	}

	return {dist[SNK],flow[SNK]};

}

pair<int, int> mcmf() {
	int cst = 0, flow = 0;
	pair<int, int> cf;
	while (cf = bellman(), cf.second)
		cst += cf.first * cf.second, flow += cf.second;
	return {cst,flow};
}

void reverse() {
	for (int i = 0; i < edgeCnt; i += 2) {
		edges[i].cap += edges[i | 1].cap, edges[i | 1].cap = 0;
		edges[i].cost *= -1, edges[i | 1].cost *= -1;
	}
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif
	cout << fixed << setprecision(2) ;
	int p, c;
	int cs = 0 ;
	while (cin >> p >> c, p) {
		init();

		for (int i = 0; i < p; ++i) {
			int tmp;
			cin >> tmp;
			addBi(SRC, getP(i), tmp, 0);
		}
		for (int i = 0; i < c; ++i) {
			int tmp;
			cin >> tmp;
			addBi(getC(i), SNK, tmp, 0);
		}

		for (int i = 0; i < p; ++i)
			for (int j = 0; j < c; ++j) {
				double tmp;
				cin >> tmp;
				if (tmp != -1)
				  addBi(getP(i), getC(j), INF, round(tmp * 100));
			}



		int mn = mcmf().first;
		reverse();
		int mx = -mcmf().first;
		cout << "Problem " << ++cs << ": " << mn / 100.0 << " to " << mx / 100.0 << '\n';
	}

}
