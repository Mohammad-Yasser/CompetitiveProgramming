#include <bits/stdc++.h>
using namespace std;
#define popCnt(x) (__builtin_popcountll(x))
typedef long long Long;

typedef complex<double> Point;
// rotate anti-clockwise
#define EPS 1e-9
#define OO 1e9
#define X real()
#define Y imag()
#define vec(a,b)  ((b) - (a))
#define polar(r,t)  ((r) * exp(Point(0, (t))))
#define angle(v)  (atan2((v).Y, (v).X))
#define length(v)   ((double)hypot((v).Y, (v).X))
#define lengthSqr(v)  (dot(v, v))
#define dot(a,b)  ((conj(a) * (b)).real())
#define cross(a,b)  ((conj(a) * (b)).imag())
#define rotate(v,t)   (polar(v, t))
#define rotateabout(v,t,a)  (rotate(vec(a, v), t) + (a))
#define reflect(p,m)  ((conj((p) / (m))) * (m))
#define normalize(p)  ((p) / length(p))
#define same(a,b)   (lengthSqr(vec(a, b)) < EPS)
#define mid(a,b)  (((a) + (b)) / Point(2, 0))
#define perp(a)   (Point(-(a).Y, (a).X))

#define sz(p) (p.size())

typedef vector<Point> Polygon;
const double PI = acos(-1);

double getAngle(const Point& a, const Point& b) {
  return acos(dot(a, b) / length(a) / length(b));
}

Polygon getRegularPolygon(int n, double side) {
  Point a(0, 0), b(side, 0);
  Polygon res = { a, b };
  double angle = (PI * (n - 2)) / n;

  for (int i = 2; i < n; ++i) {
    Point a = res[i - 2], b = res[i - 1];
    Point curr = rotateabout(a, -angle, b);
    res.push_back(curr);
  }

//  for (int i = 0; i < n; ++i) {
//    Point a = res[i], b = res[(i + 1) % n], c = res[(i + 2) % n];
//    assert(abs(lengthSqr(vec(a , b)) - side * side) < 1e-9);
//    assert(abs(getAngle(a - b, c - b) - angle) < 1e-9);
//  }

  return res;
}

void print(const Polygon& p) {
  for (auto& x : p) {
    cout << x << endl;
  }
}

void input(Point& p) {
  int x, y;
  cin >> x >> y;
  p = Point(x, y);
}

double polygonArea(const vector<Point> &p) {
  double res = 0;
  for (int i = 0; i < sz(p); i++) {
    int j = (i + 1) % sz(p);
    res += cross(p[i], p[j]);
  }
  return fabs(res) / 2;
}

double solve(int n, double d) {
  double low = 0, high = 1e6, mid;
  for (int i = 0; i < 70; ++i) {
    mid = (low + high) / 2;
    auto polygon = getRegularPolygon(n, mid);
    double diag = length(vec(polygon[0] , polygon[n / 2]));
    if (d < diag) {
      high = mid;
    } else {
      low = mid;
    }
  }
  return mid;
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifdef Local
  freopen("test.in", "r", stdin);
#else
#define endl '\n'
#endif

  while (true) {
    Point a, b;
    int n;

    input(a);
    input(b);
    cin >> n;

    if (n == 0) return 0;

    double side = solve(n, length(vec(a , b)));
    auto polygon = getRegularPolygon(n, side);
    double res = polygonArea(polygon);

    cout << fixed << setprecision(6) << res << endl;
  }

}
