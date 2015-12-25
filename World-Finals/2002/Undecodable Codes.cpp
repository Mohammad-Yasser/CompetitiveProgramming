#include <bits/stdc++.h> 
using namespace std;
typedef long long ll;

#define sz(x) (int)x.size()

string codeword[21];

struct Node {
	string s, total;
	bool operator <(const Node &other) const {
		if (sz(total) == sz(other.total)) return total > other.total;
		return sz(total) > sz(other.total);
	}
};
unordered_map<string, Node> nodes;
unordered_set<string> vis;
bool pre(const string &s1, const string &s2) {
	if (sz(s1) < sz(s2)) return 0;
	return s2 == s1.substr(0, s2.size());
}

int m;
string dijkstra() {
	priority_queue<Node> pq;
	vis.clear();
	nodes.clear();
	for (int i = 0; i < m; ++i)
		for (int j = !i; j < m; ++j, j += (i == j))
			if (pre(codeword[i], codeword[j])) {
				string tmp = codeword[i].substr(sz(codeword[j]));
				Node nt = { tmp, codeword[i] };
				if (!nodes.count(tmp) or nodes[tmp] < nt)
				  pq.push(nodes[tmp] = nt);
			}

	while (!pq.empty()) {
		Node node = pq.top();
		pq.pop();

		if (vis.count(node.s)) continue;
		vis.insert(node.s);

		for (int i = 0; i < m; ++i) {
			if (node.s == codeword[i]) return node.total;

			if (pre(codeword[i], node.s)) {
				string tmp = codeword[i].substr(node.s.size());
				Node nt = { tmp, node.total + tmp };
				if (!nodes.count(tmp) or nodes[tmp] < nt)
				  pq.push(nodes[tmp] = nt);

			}

			if (pre(node.s, codeword[i])) {
				string tmp = node.s.substr(codeword[i].size());
				Node nt = { tmp, node.total };
				if (!nodes.count(tmp) or nodes[tmp] < nt)
				  pq.push(nodes[tmp] = nt);
			}
		}
	}
	assert(1);

}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif

	int cs = 0;

	while (cin >> m, m) {
		for (int i = 0; i < m; ++i)
			cin >> codeword[i];

		string res = dijkstra();

		cout << "Code " << ++cs << ": " << sz(res) << " bits\n";
		while (sz(res) > 20)
			cout << res.substr(0, 20) << '\n', res = res.substr(20);

		cout << res << "\n\n";
	}

}
