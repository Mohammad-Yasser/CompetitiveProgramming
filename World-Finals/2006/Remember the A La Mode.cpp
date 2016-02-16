
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

pair<int, int> spfa() {
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
	while (cf = spfa(), cf.second)
		cst += cf.first * cf.second, flow += cf.second;
	return {cst,flow};
}

