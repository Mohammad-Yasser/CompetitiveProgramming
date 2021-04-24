typedef array<P, 2> Segment;

bool LinesParallel(const Point& a, const Point& b, const Point& c,
                   const Point& d) {
  return isZero(cross(b - a, c - d));
}

bool LinesCollinear(const Point& a, const Point& b, const Point& c,
                    const Point& d) {
  return LinesParallel(a, b, c, d) && isZero(cross(b - c, a - c));
}

// Assuming that c already lies on the straight line ab,
// returns true if c lies on the segment ab.
bool onSegment(const Point& a, const Point& b, const Point& c) {
  return checkInRange(min(a.x, b.x), max(a.x, b.x), c.x) &&
         checkInRange(min(a.y, b.y), max(a.y, b.y), c.y);
}

// Returns true if c lies on the segment ab.
bool onSegment(const P& s, const P& e, const P& p) {
  return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

// Returns true if one segment is nested in the other.
bool nestedSegment(const Point& a, const Point& b, const Point& c,
                   const Point& d) {
  return (LinesCollinear(a, b, c, d) &&
          (((onSegment(a, b, c) && onSegment(a, b, d)) ||
            (onSegment(c, d, a) && onSegment(c, d, b)))));
}

// Determine if a to b intersects with c to d.
bool SegmentsIntersect(const Point& a, const Point& b, const Point& c,
                       const Point& d) {
  // Handles collinear cases.
  auto d1 = getDirection(c, d, a);
  auto d2 = getDirection(c, d, b);
  auto d3 = getDirection(a, b, c);
  auto d4 = getDirection(a, b, d);

  if (d1 == 0 && onSegment(c, d, a)) return true;
  if (d2 == 0 && onSegment(c, d, b)) return true;
  if (d3 == 0 && onSegment(a, b, c)) return true;
  if (d4 == 0 && onSegment(a, b, d)) return true;
  if (d1 == 0 || d2 == 0 || d3 == 0 || d4 == 0) return false;
  return (((d1 > 0) == (d2 < 0)) && ((d3 > 0) == (d4 < 0)));
}

// Source: kactl
/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-27
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description:\\
\begin{minipage}{75mm}
If a unique intersection point between the line segments going from s1 to e1 and
from s2 to e2 exists then it is returned. If no intersection point exists an
empty vector is returned. If infinitely many exist a vector with 2 elements is
returned, containing the endpoints of the common line segment. The wrong
position will be returned if P is Point<ll> and the intersection point does not
have integer coordinates. Products of three coordinates are used in intermediate
steps so watch out for overflow if using int or long long. \end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/SegmentIntersection}
\end{minipage}
 * Usage:
 * vector<P> inter = segInter(s1,e1,s2,e2);
 * if (sz(inter)==1)
 *   cout << "segments intersect at " << inter[0] << endl;
 * Status: stress-tested, tested on kattis:intersection
 */
template <class P>
vector<P> segInter(const P& a, const P& b, const P& c, const P& d) {
  auto oa = c.cross(d, a), ob = c.cross(d, b), oc = a.cross(b, c),
       od = a.cross(b, d);
  // Checks if intersection is single non-endpoint point.
  if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
    return {(a * ob - b * oa) / (ob - oa)};
  set<P> s;
  if (onSegment(c, d, a)) s.insert(a);
  if (onSegment(c, d, b)) s.insert(b);
  if (onSegment(a, b, c)) s.insert(c);
  if (onSegment(a, b, d)) s.insert(d);
  return {all(s)};
}

Double segDist(const P& s, const P& e, const P& p) {
  if (s == e) return (p - s).dist();
  auto d = (e - s).dist2(), t = min(d, max(Double(.0), (p - s).dot(e - s)));
  return ((p - s) * d - (e - s) * t).dist() / d;
}

bool SegmentsIntersect(const Segment& a, const Segment& b) {
  return SegmentsIntersect(a[0], a[1], b[0], b[1]);
}

// ST Line ab intersect ST Line cd assuming unique intersection exists
// for line segments, check if segments intersect first
Point ComputeLineIntersection(Point a, Point b, Point c, Point d) {
  b = b - a;
  d = c - d;
  c = c - a;
  return a + b * cross(c, d) / cross(b, d);  // cross(b,d) != 0
}

// Pre-condition: `Double` is non floating point.
bool SegmentsIntersectAtLatticePoint(const Segment& seg1, const Segment& seg2) {
  if (!SegmentsIntersect(seg1, seg2)) return false;
  Point a = seg1[0], b = seg1[1], c = seg2[0], d = seg2[1];
  b = b - a;
  d = c - d;
  c = c - a;
  Long cd = abs(cross(c, d));
  Long bd = abs(cross(b, d));
  if (bd == 0) return false;
  bd /= __gcd(bd, cd);
  return b.x % bd == 0 && b.y % bd == 0;
}

int countLattticePoints(const Segment& segment) {
  return __gcd(abs(segment[0].x - segment[1].x),
               abs(segment[0].y - segment[1].y)) +
         1;
}
