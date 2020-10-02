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

  int getQuad() const {
    if (x >= 0) {
      if (y >= 0) return 0;
      return 3;
    }
    if (y >= 0) return 1;
    return 2;
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

typedef Point<Double> P;

bool antiClockwiseComparator(const P& a, const P& b) {
  int q1 = a.getQuad(), q2 = b.getQuad();
  if (q1 != q2) {
    return q1 < q2;
  }
  auto cross = a.cross(b);
  if (cross == 0) {
    return a.dist2() < b.dist2();
  }
  return cross > 0;
}

bool areCollinear(const Point& a, const Point& b, const Point& c) {
  return isZero(a.getVector(b).cross(c.getVector(b)));
}

// Returns 1 if CW, 0 if collinear, -1 if ACW.
int getDirection(const Point& a, const Point& b, const Point& c) {
  auto value = cross(c - a, b - a);
  if (isZero(value)) return 0;
  return 2 * (value > 0) - 1;
}