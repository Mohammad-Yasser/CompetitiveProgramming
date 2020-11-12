// Assumes no 3 collinear points.
void sweep(vector<P> points) {
  sort(all(points), antiClockwiseComparator);
  for (int i = 0; i < sz(points); ++i) {
    int j = (i + 1) % sz(points);
    if (points[i].cross(points[j]) < 0) {
      rotate(begin(points), begin(points) + j, end(points));
      break;
      // To prevent having two consecutive points having angle more than 180,
      // or in other words, p[i].cross(p[i+1]) < 0.
    }
  }
  int l = 0, r = 1 % sz(points);

  while (points[l].cross(points[r]) > 0) {
    // update
    r = (r + 1) % sz(points);
  }
  for (auto& p : points) {
    if (points[l].cross(p) < 0) {
      // update
    }
  }

  while (l + 1 < sz(points)) {
    ++l;
    // update
    // assert(points[l - 1].cross(points[l]) > 0);
    while (points[l].cross(points[r]) > 0) {
      r = (r + 1) % sz(points);
      // update
    }
  }
}
