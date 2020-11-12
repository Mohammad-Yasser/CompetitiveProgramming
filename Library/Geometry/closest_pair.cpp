
#define square(x) ((x) * (x))

struct Point {
  Long x, y;
  Long dist2(const Point& other) const {
    return square(x - other.x) + square(y - other.y);
  }
  friend ostream& operator<<(ostream& os, const Point& p) {
    return os << p.x << " " << p.y;
  }
};

// O(n log n)
// Sort by x before calling.
// Returns the squared distance between the closest pair of points.
Long closestPair(int l, int r, vector<Point>& points) {
  if (l == r) return LLONG_MAX;
  int m = (l + r) / 2;
  auto pivot = points[m];
  Long res = min(closestPair(l, m, points), closestPair(m + 1, r, points));
  inplace_merge(begin(points) + l, begin(points) + m + 1, begin(points) + r + 1,
                [](const auto& a, const auto& b) { return a.y < b.y; });
  vector<Point> candidates;
  for (int i = l; i <= r; ++i) {
    if (square(pivot.x - points[i].x) < res) candidates.emplace_back(points[i]);
  }
  for (int i = 0; i < sz(candidates); ++i) {
    int j = i + 1;
    auto& current = candidates[i];
    while (j < sz(candidates) && square(candidates[j].y - current.y) < res) {
      res = min(res, current.dist2(candidates[j]));
      ++j;
    }
  }
  return res;
}
