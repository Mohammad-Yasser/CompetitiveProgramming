#include <bits/stdc++.h> 
using namespace std;
#define popCnt(x) (__builtin_popcountll(x))
#define lNode (node << 1)
#define rNode ((node << 1) + 1)
typedef long long ll;
typedef pair<int, int> Point;
const int N = 100005;
const int INF = 1e6 + 5;
const int ShiftY = 2e6 + 5;
int n;
Point points[N];

struct Rect {
	int xL, xH, yL, yH;
	inline ll area() {
		return 1LL * (xH - xL + 1) * (yH - yL + 1);
	}
};

struct Event {
	vector<pair<int, int> > in, out;
};

map<int, Event> getXs(vector<Rect> & rects) {
	map<int, Event> xs;
	for (auto &r : rects) {
		xs[r.xL].in.push_back( { r.yL + ShiftY, r.yH + ShiftY });
		xs[r.xH + 1].out.push_back( { r.yL + ShiftY, r.yH + ShiftY });
	}
	return xs;
}

struct SegmentTree {
	const static int nLeaves = 4 * INF;
	const static int SZ = 1 << ((int) (log2(nLeaves)) + 2);
	struct Node {
		int nonZeroes, whollyCovered;
	};
		Node *tree = new Node[SZ];
//	Node tree[SZ];

	void update(int left, int right, char val, int s = 0, int e = nLeaves - 1, int node = 1) {
		if (right < s || left > e) return;

		if (left <= s && e <= right) {
			tree[node].whollyCovered += val;
			if (tree[node].whollyCovered) {
				tree[node].nonZeroes = e - s + 1;
			} else {
				if (s == e) {
					tree[node].nonZeroes = 0;
				} else {
					tree[node].nonZeroes = tree[lNode].nonZeroes + tree[rNode].nonZeroes;
				}
			}
			return;
		}

		int mid = (s + e) >> 1;

		update(left, right, val, s, mid, lNode);
		update(left, right, val, mid + 1, e, rNode);
		if (!tree[node].whollyCovered)
		  tree[node].nonZeroes = tree[lNode].nonZeroes + tree[rNode].nonZeroes;
	}

	inline ll getNonZeroes() {
		return tree[1].nonZeroes;
	}
	inline void reset() {
		memset(tree, 0, sizeof tree);
	}
};

SegmentTree tree;

ll calcTotArea(vector<Rect> & rects) {
	ll ret = 0;
	map<int, Event> xs = getXs(rects);
	int lst = xs.begin()->first;
	tree.reset();

	for (auto &curr : xs) {
		ret += tree.getNonZeroes() * (curr.first - lst);

		lst = curr.first;
		for (auto &range : curr.second.in)
			tree.update(range.first, range.second, 1);
		for (auto &range : curr.second.out)
			tree.update(range.first, range.second, -1);
//		ret += tree.getNonZeroes(); // * (curr.first - lst + 1);

	}

	return ret;
}

bool getIntersection(Rect &first, Rect &second, Rect &res) {
	res.xL = max(first.xL, second.xL);
	res.xH = min(first.xH, second.xH);
	res.yL = max(first.yL, second.yL);
	res.yH = min(first.yH, second.yH);
	if (res.xH < res.xL || res.yH < res.yL) return false;
	return true;
}

Rect getSquare(Point &pt, int ts) {
	Rect ret;
	ret.xL = pt.first - ts;
	ret.xH = pt.first + ts;
	ret.yL = pt.second - ts;
	ret.yH = pt.second + ts;
	return ret;
}

vector<Rect> getSquares(int ts) {
	vector<Rect> squares(n);
	for (int i = 0; i < n; ++i)
		squares[i] = getSquare(points[i], ts);
	return squares;
}

bool val(int ts) {
	vector<Rect> squares = getSquares(ts);
	vector<Rect> rects;
	Rect res;
	for (int i = 1; i < n; ++i)
		if (getIntersection(squares[0], squares[i], res))
		  rects.push_back(res);

	if (calcTotArea(rects) == squares[0].area())
	  return 0;
	return 1;
}

inline int bs() {
	int low = 0, high = INF, mid, ans;
	while (low <= high) {
		mid = (low + high) >> 1;
		if (val(mid))
			low = mid + 1, ans = mid;
		else
			high = mid - 1;
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif
	int cs = 0;
	while (cin >> n, n != -1) {
		for (int i = 1; i <= n; ++i)
			cin >> points[i].first >> points[i].second;
		++n;
		points[0] = Point(0, 0);

		int ans = bs();
		cout << "Case " << ++cs << ": ";
		if (ans == INF)
			cout << "never";
		else
			cout << ans + 1;
		cout << '\n';
	}

}
