// Add pairs (m, c) then query(x) returns min {m * x + c}.
// Complexity: O(number of insertions + number of queries).
// Maintains the lower convex hull.
// Lines added must be sorted non-decreasingly by slope.
// Queries must be sorted non-decreasingly by x.
struct LinearLineContainer {
  vector<P>
      lines;  // Each line is represented as a 2D point (slope, y-intercept).
  void addLine(Long m, Long c) {
    P line(m, c);
    while (sz(lines) >= 2 &&
           lines[sz(lines) - 2].cross(lines[sz(lines) - 1], line) <= 0) {
      lines.pop_back();
    }
    if (!lines.empty() && lines.back().x == line.x) {
      lines.back().y = min(lines.back().y, line.y);
    } else {
      lines.emplace_back(line);
    }
  }

  Long query(Long x) {
    P p(x, 1);
    Long res = LLONG_MAX;
    for (auto& line : lines) {
      res = min(res, line.dot(p));
    }
    return res;
  }
};