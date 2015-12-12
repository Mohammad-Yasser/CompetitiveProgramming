#include <bits/stdc++.h> 
using namespace std;
typedef long long ll;

int m, n;
int region[10];

vector<pair<int, int> > progs[50];

const int N = 552, M = 2 * (500 * 50 + 50 + 500);

int head[N], edgeCnt;

struct Edge {
	int from, to, nxt, cost, flow;
} edges[M];

void init() {
	edgeCnt = 0;
	memset(head, -1, sizeof head);
}

void addEdge(int u, int v, int cost, int flow) {
	edges[edgeCnt] = {u, v, head[u], cost, flow};
	head[u] = edgeCnt++;
}

void addBi(int u, int v, int cost) {
	addEdge(u, v, cost, 1);
	addEdge(v, u, -cost, 0);
}

const int src = 0, snk = 1;

const int OO = 1e9;

int getCost(int p, int r) { // program , region
	for (int i = progs[p].size() - 1; i >= 0; --i)
		if (region[r] >= progs[p][i].first) return progs[p][i].second;
	return OO;
}

int dist[N], parent[N], flow[N], nodeCnt;
bool inQ[N];

void buildGraph() {
	init();

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			addBi(n + 3 + i * m + j, snk, 0);

	for (int i = 0; i < n; ++i) {
		addBi(src, i + 2, 0);
		for (int k = 0; k < n; ++k)
			for (int j = 0; j < m; ++j)
				addBi(i + 2, n + 3 + k * m + j, min(1LL * OO, 1LL * (k + 1) * getCost(i, j)));
	}

	nodeCnt = n + 2 + n * m;
}

bool spfa() {
	memset(dist, 0x3f, sizeof dist);
	memset(flow, 0, sizeof flow);
	memset(inQ, 0, sizeof inQ);
	queue<int> Q;

	dist[src] = 0;
	flow[src] = OO;
	Q.push(src);
	for (int i = 0; i < nodeCnt; ++i) {
		int s = Q.size();
		while (s--) {
			int cur = Q.front();
			Q.pop();
			inQ[cur] = 0;
			for (int j = head[cur]; j != -1; j = edges[j].nxt)
				if (edges[j].cost != OO && edges[j].flow
				  && dist[edges[j].to] > dist[cur] + edges[j].cost) {
					int to = edges[j].to;
					dist[to] = dist[cur] + edges[j].cost;
					parent[to] = j;
					flow[to] = min(edges[j].flow, flow[cur]);
					if (!inQ[to]) inQ[to] = 1, Q.push(to);
				}
		}
	}

	if (flow[snk])
	  for (int i = snk; i != src; i = edges[parent[i]].from)
		  edges[parent[i]].flow -= flow[snk], edges[parent[i] ^ 1].flow += flow[snk];

	return flow[snk];

}

int mcmf() {
	int cst = 0;
	while (spfa())
		cst += dist[snk] * flow[snk];
	return cst;
}

vector<pair<int, int> > regProg[10]; // cost , prog for each region

struct Answer {
	int region, start, end;
} answers[50];

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif

	int cs = 0;
	while (cin >> m >> n, n or m) {
		for (int i = 0; i < m; ++i)
			cin >> region[i];
		for (int i = 0; i < n; ++i) {
			int k;
			cin >> k;
			progs[i].resize(k);
			for (int j = 0; j < k; ++j)
				cin >> progs[i][j].first >> progs[i][j].second;
		}

		buildGraph();

		cout << "Case " << ++cs << "\nAverage turnaround time = " << fixed
		  << setprecision(2) << 1.0 * mcmf() / n << '\n';

		for (int j = 0; j < m; ++j)
			regProg[j].clear();

		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j) {
				for (int edge = head[n + 3 + i * m + j]; edge != -1; edge = edges[edge].nxt)
					if (edges[edge].flow && edges[edge].to != 1)
					  regProg[j].push_back( { -edges[edge].cost / (i + 1), edges[edge].to - 2 });
			}

		for (int i = 0; i < m; ++i) {
			sort(regProg[i].begin(), regProg[i].end());
			int tm = 0;
			for (auto &x : regProg[i])
				answers[x.second] = {i+1 , tm , tm + x.first},tm += x.first;
			}

		for (int i = 0; i < n; ++i)
			cout << "Program " << i + 1 << " runs in region " << answers[i].region << " from "
			  << answers[i].start << " to " << answers[i].end << '\n';

	}

}
