
using Polygon = vector<P>;

// Pre-condition: `a` is a convex polygon whose points are sorted in
// anticlockwise order.
// Returns the edges of the polygon sorted in anticlockwise
// order.
// Rotates `a` to start from the start point of the smallest edge according to
// the given anticlockwise order.
vector<P> getEdges(Polygon& a) {
  vector<P> edges;
  int base_a = 0;
  for (int i = 0; i < sz(a); ++i) {
    int j = (i + 1) % sz(a);
    edges.emplace_back(a[j] - a[i]);
    if (antiClockwiseComparator(edges.back(), edges[base_a])) {
      base_a = i;
    }
  }
  rotate(begin(edges), begin(edges) + base_a, end(edges));
  rotate(begin(a), begin(a) + base_a, end(a));
  return edges;
}

template <class P>
bool inPolygon(const vector<P>& p, const P& a) {
  int cnt = 0, n = sz(p);
  rep(i, 0, n) {
    int j = (i + 1) % n;
    P q = p[j];
    if (onSegment(p[i], q, a)) return !strict;
    // or: if (segDist(p[i], q, a) <= eps) return !strict;
    cnt ^= ((a.y < p[i].y) - (a.y < q.y)) * a.cross(p[i], q) > 0;
  }
  return cnt;
}

template <class T>
T polygonArea2(const vector<Point<T>>& v) {
  T a = v.back().cross(v[0]);
  rep(i, 0, sz(v) - 1) a += v[i].cross(v[i + 1]);
  return a;
}

Double pointPolygonDistance(const P& point, const Polygon& polygon) {
  if (inPolygon(polygon, point)) return 0;
  Double res = 1e15;
  for (int i = 0; i < sz(polygon); ++i) {
    int j = (i + 1) % sz(polygon);
    res = min(res, segDist(polygon[i], polygon[j], point));
  }
  return res;
}

bool circleIntersectsPolygon(const Circle& circle, const Polygon& polygon) {
  return compareDoubles(pointPolygonDistance(circle.center, polygon),
                        circle.r) != Relation::GREATER_THAN;
}