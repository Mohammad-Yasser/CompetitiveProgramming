#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef complex<double> Point;
#define EPS 1e-9
#define OO 1e9
#define X real()
#define Y imag()
#define vec(a,b) 	((b) - (a))
#define polar(r,t) 	((r) * exp(point(0, (t))))
#define angle(v) 	(atan2((v).Y, (v).X))
#define length(v) 	((double)hypot((v).Y, (v).X))
#define lengthSqr(v) 	(dot(v, v))
#define dist2(a,b) (lengthSqr(vec(a,b)))
#define dot(a,b) 	((conj(a) * (b)).real())
#define cross(a,b) 	((conj(a) * (b)).imag())
#define rotate(v,t) 	(polar(v, t))
#define rotateabout(v,t,a)  (rotate(vec(a, v), t) + (a))
#define reflect(p,m) 	((conj((p) / (m))) * (m))
#define normalize(p) 	((p) / length(p))
#define same(a,b) 	(lengthSqr(vec(a, b)) < EPS)
#define mid(a,b)	(((a) + (b)) / Point(2, 0))
#define perp(a) 	(Point(-(a).Y, (a).X))
#define collinear 	pointOnLine
bool pointOnLine(const Point& a, const Point& b, const Point& p) {
	// degenerate case: line is a point
	return fabs(cross(vec(a,b), vec(a,p))) < EPS;
}
bool pointOnRay(const Point& a, const Point& b, const Point& p) {
	//IMP NOTE: a,b,p must be collinear
	return dot(vec(a,p), vec(a,b)) > -EPS;
}
bool pointOnSegment(const Point& a, const Point& b, const Point& p) {
	if (!collinear(a, b, p)) return 0;
	return pointOnRay(a, b, p) && pointOnRay(b, a, p);
}

bool intersect(const Point &a, const Point &b,
  const Point &p, const Point &q, Point &ret) {
	//handle degenerate cases (2 parallel lines, 2 identical lines,   line is 1 point)
	double d1 = cross(p - a, b - a);
	double d2 = cross(q - a, b - a);
	ret = (d1 * q - d2 * p) / (d1 - d2);
	if (fabs(d1 - d2) > EPS && pointOnSegment(a, b, ret)) return 1;
	return 0;
}
ostream& operator <<(ostream& os, const Point & p) {
	return os << "(" << p.X << ", " << p.Y << ")";
}

struct Line {
	Point a, b;
};

Point tower[51], city[51];

vector<pair<int, int> > adj[51];

Line bound[51][51];

int vis[51], visID;
int dijkstra(int u, int v) {
	++visID;
	priority_queue<pair<int, int> > q;
	q.push( { 0, u });

	while (!q.empty()) {
		auto curr = q.top();
		q.pop();
		if (curr.second == v) return -curr.first;
		if (vis[curr.second] == visID) continue;
		vis[curr.second] = visID;
		for (auto &p : adj[curr.second])
			if (vis[p.first] != visID)
			  q.push( { curr.first - p.second, p.first });
	}
	return -1;
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif

	int t, c, r, q;
	int cs = 0;
	double tmpX, tmpY;
	while (cin >> t >> c >> r >> q, t) {
		cout << "Case " << ++cs << ":\n";
		for (int i = 0; i < t; ++i) {
			cin >> tmpX >> tmpY;
			tower[i] = Point(tmpX, tmpY);
		}
		for (int i = 0; i < c; ++i) {
			cin >> tmpX >> tmpY;
			city[i] = Point(tmpX, tmpY);
		}

		for (int i = 0; i < t; ++i)
			for (int j = i + 1; j < t; ++j) {
				Line tmp;
				tmp.a = mid(tower[i], tower[j]);
				tmp.b = tmp.a + perp(vec(tower[i],tower[j]));
				bound[i][j] = bound[j][i] = tmp;
			}

		for (int i = 0; i < r; ++i) {
			int u, v;
			cin >> u >> v;
			--u, --v;

			Line l = { city[u], city[v] };
			int cost = 0, currTower = 1;
			for (int twr = 0; twr < t; ++twr)
				if (dist2(l.a,tower[twr]) < dist2(l.a, tower[currTower]))
				  currTower = twr;

			Point ret, nextPoint;
			int nextTower;
			bool changed = 1;

			while (!same(l.a, l.b) && changed) {
				changed = 0;
				for (int twr = 0; twr < t; ++twr, twr += currTower == twr)
					if (intersect(l.a, l.b, bound[currTower][twr].a, bound[currTower][twr].b,
					  ret) && (!changed or dist2(ret , l.a) < dist2(nextPoint, l.a)))
					  nextPoint = ret, changed = 1, nextTower = twr;
				if (changed)
				  l.a = nextPoint + EPS * normalize(vec(l.a, l.b)), ++cost, currTower =
				    nextTower;
			}
			adj[u].push_back( { v, cost }), adj[v].push_back( { u, cost });
		}

		for (int i = 0; i < q; ++i) {
			int u, v;
			cin >> u >> v;
			--u, --v;
			int ans = dijkstra(u, v);
			if (ans == -1)
				cout << "Impossible";
			else
				cout << ans;
			cout << '\n';
		}
	}

}
