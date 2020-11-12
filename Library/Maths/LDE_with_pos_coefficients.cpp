ll egcd(ll a, ll b, ll& x, ll& y) {
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  }
  ll x1, y1;
  ll d = egcd(b % a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;
  return d;
}

// Needs testing
bool solve(ll x, ll y, ll c, ll& a, ll& b) {
  // x and y must be coprime.
  if (__gcd(x, y) != 1) return false;
  egcd(x, y, a, b);  // a * x + b * y == 1
  a *= c;
  b *= c;
  if (b < 0) {
    swap(a, b);
    swap(x, y);
  }
  ll bmul = x;
  ll amul = y;
  ll mul = abs(a / amul) + 1;
  a += mul * amul;
  b -= mul * bmul;
  return a > 0 && b > 0;
}
