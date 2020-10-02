// Source: modification of kactl's.
vector<P> lowerHull(vector<P> pts) {
  if (sz(pts) <= 1) return pts;
  sort(all(pts));
  vector<P> h(sz(pts) + 1);
  int s = 0, t = 0;
  for (P p : pts) {
    while (t >= s + 2 && h[t - 2].cross(h[t - 1], p) <= 0) t--;
    h[t++] = p;
  }
  return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}