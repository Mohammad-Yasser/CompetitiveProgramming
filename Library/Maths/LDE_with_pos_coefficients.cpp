// Hmm , needs good understanding.

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
ll lcm(ll a, ll b) { return a * b / __gcd(a, b); }

bool solve(ll x, ll y, ll c, ll& a, ll& b) {
  // x and y are coprime.
  egcd(x, y, a, b);  // a * x + b * y == 1
  a *= c;
  b *= c;
  if (b < 0) {
    swap(a, b);
    swap(x, y);
  }
  ll bmul = (lcm(x, y) / y);
  ll amul = (lcm(x, y) / x);
  ll mul = abs(a / amul) + 1;
  a += mul * amul;
  b -= mul * bmul;
}
