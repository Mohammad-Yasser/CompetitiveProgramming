#include <bits/stdc++.h>
using namespace std;

typedef long double Double;

const Double EPS = 1e-10;

enum Relation { LESS_THAN, EQUAL, GREATER_THAN };

bool areEqual(Double x, Double y, Double eps = EPS) {
  auto diff = abs(x - y);
  x = abs(x), y = abs(y);
  if (diff <= eps) return true;
  if (min(x, y) <= eps) return false;
  return diff <= eps * max(x, y);
}

bool isZero(Double x, Double eps = EPS) { return abs(x) <= eps; }

int compareDoubles(Double x, Double y, Double eps = EPS) {
  if (areEqual(x, y, eps)) return Relation::EQUAL;
  if (x < y) return Relation::LESS_THAN;
  return Relation::GREATER_THAN;
}

template <typename T = Double>
struct Point {
  typedef Point P;
  const static P Invalid;
  const static P Origin;

  T x = 0, y = 0;
  Point(T x, T y) : x(x), y(y) {}
  Point() {}
  pair<T, T> to_pair() const { return make_pair(x, y); }
  Point operator+(const Point& p) const { return Point{x + p.x, y + p.y}; }
  Point operator-(const Point& p) const { return Point{x - p.x, y - p.y}; }
  Point operator*(T c) const { return Point(x * c, y * c); }
  Point operator/(T c) const { return Point(x / c, y / c); }
  bool operator<(const Point& p) const {
    return (*this) != p && to_pair() < p.to_pair();
  }
  bool operator>(const Point& p) const { return (*this) != p && !(*this < p); }
  bool operator==(const Point& p) const {
    return isZero(this->x - p.x) && isZero(this->y - p.y);
  }
  bool operator!=(const Point& p) const { return !(*this == p); }
  T cross(const P& p) const { return x * p.y - y * p.x; }
  T cross(const P& a, const P& b) const { return (a - *this).cross(b - *this); }
  T dot(const P& p) const { return x * p.x + y * p.y; }
  P midPoint(const P& p) const { return ((*this) + p) / 2; }
  P getVector(const P& p) const { return p - (*this); }
  T dist2(const P& p) const { return getVector(p).dist2(); }
  T dist2() const { return (*this).dot(*this); }
  Double dist(const P& p) const { return sqrt(dist2(p)); }
  Double dist() const { return sqrt(dist2()); }
  P rotateCCW90() const { return P(-y, x); }
  P rotateCCW90Around(const P& p) const {
    return p + p.getVector(*this).rotateCCW90();
  }
  P rotateCCW(Double angle) const {
    return Point(x * cos(angle) - y * sin(angle),
                 x * sin(angle) + y * cos(angle));
  }

  // Project point onto line through a and b (assuming a != b).
  P projectOnLine(const P& a, const P& b) const {
    P ab = a.getVector(b);
    P ac = a.getVector(*this);
    return a + ab * ac.dot(ab) / a.dist2(b);
  }

  // Project point c onto line segment through a and b (assuming a != b).
  P projectOnSegment(const P& a, const P& b) const {
    P& c = *this;
    P ab = a.getVector(b);
    P ac = a.getVector(c);

    Double r = dot(ac, ab), d = a.dist2(b);
    if (r < 0) return a;
    if (r > d) return b;

    return a + ab * r / d;
  }

  P reflectAroundLine(const P& a, const P& b) const {
    return projectOnLine(a, b) * 2 - (*this);
  }

  friend istream& operator>>(istream& is, P& p) { return is >> p.x >> p.y; }

  friend ostream& operator<<(ostream& os, P& p) {
    return os << p.x << " " << p.y;
  }
};

template <typename T>
const Point<T> Point<T>::Invalid = Point<T>(numeric_limits<T>::max(),
                                            numeric_limits<T>::max());
template <typename T>
const Point<T> Point<T>::Origin = Point<T>(0, 0);

typedef Point<Double> Vector;
typedef Point<Double> P;
typedef array<P, 2> Segment;

bool LinesParallel(const Point& a, const Point& b, const Point& c,
                   const Point& d) {
  return isZero(cross(b - a, c - d));
}

bool LinesCollinear(const Point& a, const Point& b, const Point& c,
                    const Point& d) {
  return LinesParallel(a, b, c, d) && isZero(cross(b - c, a - c));
}

bool areCollinear(const Point& a, const Point& b, const Point& c) {
  return LinesParallel(a, b, b, c);
}

// Returns 1 if CW, 0 if collinear, -1 if ACW.
int getDirection(const Point& a, const Point& b, const Point& c) {
  auto value = cross(c - a, b - a);
  if (isZero(value)) return 0;
  return 2 * (value > 0) - 1;
}

// Checks if c lies in the range [a,b]. NOTE: if b < a, returns false.
bool checkInRange(Double a, Double b, Double c, Double eps = EPS) {
  if (areEqual(a, c)) return true;
  if (areEqual(b, c)) return true;
  return a <= c && c <= b;
}

// Assuming that c already lies on the straight line ab,
// returns true if c lies on the segment ab.
bool onSegment(const Point& a, const Point& b, const Point& c) {
  return checkInRange(min(a.x, b.x), max(a.x, b.x), c.x) &&
         checkInRange(min(a.y, b.y), max(a.y, b.y), c.y);
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

vector<Point> CircleLineIntersection(Point a, Point b, Point c, Double r) {
  vector<Point> ret;
  b = b - a, a = a - c;
  Double A = dot(b, b), B = dot(a, b), C = dot(a, a) - r * r, D = B * B - A * C;
  if (isZero(D)) {
    D = 0;
  }
  if (D < 0) return ret;
  ret.push_back(c + a + b * (-B + sqrt(D)) / A);
  if (D > 0) ret.push_back(c + a + b * (-B - sqrt(D)) / A);
  return ret;
}

Double computeArcLength(Double r, Double chord_length) {
  Double theta = 2 * asin(chord_length / (2 * r));
  return r * theta;
}

template <typename T = Double>
struct Circle {
  Point<T> centre;
  T r;
  bool contains(const Point& p) const {
    return compareDoubles(dist2(centre, p), r * r) != 1;
  }
  static Circle invalidCircle() {
    static Circle circle;
    circle.centre = Point(0, 0);
    circle.r = -1;
    return circle;
  }
};

Circle circle2(const Point& p1, const Point& p2) {
  return Circle{midPoint(p1, p2), dist(p1, p2) / 2};
}

// Returns `Invalid Circle` iff the three points are collinear.
Circle circle3(const Point& p1, const Point& p2, const Point& p3) {
  if (areCollinear(p1, p2, p3)) return Circle::invalidCircle();
  Point m1 = midPoint(p1, p2);
  Point m2 = midPoint(p2, p3);
  Point perp1 = getPerpendicularVector(getVector(p1, p2));
  Point perp2 = getPerpendicularVector(getVector(p2, p3));
  Circle res;
  res.centre = ComputeLineIntersection(m1, m1 + perp1, m2, m2 + perp2);
  res.r = dist(res.centre, p1);
  return res;
}

// Don't forget to random shuffle.
Circle minEnclosingCircle(const vector<Point>& points, int& ps,
                          vector<Point>& r) {
  if (r.size() == 3) {
    return circle3(r[0], r[1], r[2]);
  }

  if (r.size() == 2 && ps == 0) {
    return circle2(r[0], r[1]);
  }

  if (ps == 0) {
    if (r.empty()) {
      return Circle{Point(0, 0), 0};
    }
    return Circle{r[0], 0};
  }

  --ps;
  Circle res = minEnclosingCircle(points, ps, r);
  if (!res.contains(points[ps])) {
    r.emplace_back(points[ps]);
    res = minEnclosingCircle(points, ps, r);
    r.pop_back();
  }
  ++ps;

  return res;
}

Circle minEnclosingCircle(const vector<Point>& points) {
  auto shuffled = points;
  mt19937 gen(0x94949);
  shuffle(shuffled.begin(), shuffled.end(), gen);
  int ps = points.size();
  vector<Point> r;
  return minEnclosingCircle(shuffled, ps, r);
}

// Adapted from
// https://github.com/kth-competitive-programming/kactl/blob/master/content/geometry/CircleIntersection.h
pair<P, P> circleInter(const P& a, const P& b, Double r1, Double r2) {
  pair<P, P> invalid = {P::Invalid, P::Invalid};
  if (a == b) {
    if (isZero(r1) && isZero(r2)) return {a, a};
    return invalid;
  }
  P vec = b - a;
  Double d2 = vec.dist2(), sum = r1 + r2, dif = r1 - r2;
  Double p = (d2 + r1 * r1 - r2 * r2) / (d2 * 2), h2 = r1 * r1 - p * p * d2;

  // Not sure that `compareDoubles` is better than just using < , > here.
  if (compareDoubles(sum * sum, d2) == Relation::LESS_THAN ||
      compareDoubles(dif * dif, d2) == Relation::GREATER_THAN)
    return invalid;

  P mid = a + vec * p, per = vec.rotateCCW90() * sqrt(fmax(0, h2) / d2);
  return {mid + per, mid - per};
}

// Adapted from
// https://github.com/kth-competitive-programming/kactl/blob/master/content/geometry/CircleIntersection.h
pair<P, P> circleInter(const Circle& a, const Circle& b) {
  return circleInter(a.centre, b.centre, a.r, b.r);
}

int countLattticePoints(const Segment& segment) {
  return __gcd(abs(segment[0].x - segment[1].x),
               abs(segment[0].y - segment[1].y)) +
         1;
}

// Check if any 2 segments from a set of given segments intersect.
{
  struct Event {
    int x, type, y, id;

    tuple<int, int, int, int> getTuple() const {
      return make_tuple(x, type, y, id);
    }

    bool operator<(const Event& other) const {
      return getTuple() < other.getTuple();
    }

    Event(int x, int type, int y, int id) : x(x), type(type), y(y), id(id) {}
  };

  struct SetComparator {
    static vector<Segment> segments;
    bool operator()(int a, int b) const {
      if (segments[a][0].x == segments[b][0].x) {
        return segments[a][0].y < segments[b][0].y;
      }
      if (segments[a][0] > segments[b][0]) {
        int dir = getDirection(segments[b][0], segments[b][1], segments[a][0]);
        return dir > 0;
      }
      int dir = getDirection(segments[a][0], segments[a][1], segments[b][0]);
      return dir < 0;
    }
  };

  vector<Segment> SetComparator::segments;

  bool noIntersection(const vector<Segment>& segments) {
    int n = segments.size();
    vector<Event> events;
    for (int i = 0; i < n; ++i) {
      // Each segment endpoints must be sorted.
      assert(segments[i][0] < segments[i][1]);
      events.emplace_back(segments[i][0].x, 0, segments[i][0].y, i);
      events.emplace_back(segments[i][1].x, 1, segments[i][1].y, i);
    }

    sort(events.begin(), events.end());

    SetComparator::segments = segments;
    set<int, SetComparator> st;

    for (auto& event : events) {
      if (event.type == 0) {
        auto nxt = st.upper_bound(event.id);
        if (nxt != st.end()) {
          if (SegmentsIntersect(segments[event.id][0], segments[event.id][1],
                                segments[*nxt][0], segments[*nxt][1]))
            return false;
        }

        if (nxt != st.begin()) {
          --nxt;
          if (SegmentsIntersect(segments[event.id][0], segments[event.id][1],
                                segments[*nxt][0], segments[*nxt][1]))
            return false;
        }

        st.insert(event.id);

      } else {
        st.erase(event.id);
        auto nxt = st.upper_bound(event.id);
        if (nxt != st.end() && nxt != st.begin()) {
          auto before = nxt;
          --before;
          if (SegmentsIntersect(segments[*before][0], segments[*before][1],
                                segments[*nxt][0], segments[*nxt][1])) {
            return false;
          }
        }
      }
    }

    return true;
  }
}
// End
