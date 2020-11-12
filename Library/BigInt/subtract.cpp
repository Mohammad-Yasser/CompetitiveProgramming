// a and b are +ve integers and b < a.
string subtract(const string& a, const string& b) {
  string res(sz(a), 0);
  string rev_a = a, rev_b = b;
  reverse(all(rev_a)), reverse(all(rev_b));
  while (sz(rev_b) < sz(rev_a)) rev_b += '0';
  bool borrow = false;
  for (int i = 0; i < sz(rev_a); ++i) {
    int ai = rev_a[i] - borrow;
    int bi = rev_b[i];
    borrow = false;
    if (bi > ai) {
      borrow = true;
      ai += 10;
    }
    res[i] = ai - bi + '0';
  }
  while (res.back() == '0') {
    res.pop_back();
  }
  reverse(all(res));
  return res;
}