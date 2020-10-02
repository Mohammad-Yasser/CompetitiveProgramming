
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
