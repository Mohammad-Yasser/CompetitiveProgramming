
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

// Calculates minkowski sum of two convex polygons.
// The result is a convex polygon that contains all the points p where p = p1 +
// p2 for any two points p1 in the first polygon, and p2 in the second one.
// O(n)
Polygon minkowskiSum(Polygon a, Polygon b) {
  vector<P> edges_a = getEdges(a);
  vector<P> edges_b = getEdges(b);
  vector<P> merged(sz(edges_a) + sz(edges_b));
  merge(all(edges_a), all(edges_b), begin(merged), antiClockwiseComparator);
  Polygon res;
  res.emplace_back(a[0] + b[0]);
  for (auto& edge : merged) {
    res.emplace_back(res.back() + edge);
  }
  return res;
}

// Computes minkowski difference, check minkowskiSum().
Polygon minkowskiDifference(const Polygon& a, const Polygon& b) {
  Polygon neg_b = b;
  for (auto& p : neg_b) {
    p = p * -1;
  }
  return minkowskiSum(a, neg_b);
}

// Check if two convex polygons intersect.
// `a` and `b` must be sorted in any anticlockwise order.
bool polygonIntersection(const Polygon& a, const Polygon& b) {
  Polygon mink_diff = minkowskiDifference(a, b);
  return inPolygon(mink_diff, P(0, 0), false);
}

// Source:
// https://github.com/kth-competitive-programming/kactl/blob/master/content/geometry/InsidePolygon.h
/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Returns true if p lies within the polygon. If strict is true,
 * it returns false for points on the boundary. The algorithm uses
 * products in intermediate steps so watch out for overflow.
 * Time: O(n)
 * Usage:
 * vector<P> v = {P{4,4}, P{1,2}, P{2,1}};
 * bool in = inPolygon(v, P{3, 3}, false);
 * Status: stress-tested and tested on kattis:pointinpolygon
 */
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