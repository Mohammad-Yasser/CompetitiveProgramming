
bool isCCWSquare(const vector<P>& points) {
  for (int i = 0; i < 4; ++i) {
    int before = (i + 3) % 4;
    int after = (i + 1) % 4;
    int curr = i;
    if (points[after].rotateCCW90Around(points[curr]) != points[before])
      return false;
  }
  return true;
}

// Returns false if degenerate.
// Doesn't do multiplication, so can work with long long.
bool isSquare(vector<P> points) {
  if (points[0] == points[1] || points[0] == points[2] ||
      points[0] == points[3])
    return false;  // Degenerate

  for (int i = 0; i < 3; ++i) {
    if (isCCWSquare(points)) return true;
    swap(points[2], points[3]);
    if (isCCWSquare(points)) return true;
    swap(points[1], points[2]);
  }
  return false;
}