
// Source:
// https://github.com/kth-competitive-programming/kactl/blob/master/content/strings/Hashing-codeforces.h
const int RANDOM =
    chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rng(RANDOM);

int rnd(int a, int b) { return rng() % (b - a + 1) + a; }
typedef uint64_t ull;

template <int M, class B>
struct A {
  int x;
  B b;
  A(int x = 0) : x(x), b(x) {}
  A(int x, B b) : x(x), b(b) {}
  A operator+(A o) {
    int y = x + o.x;
    return {y - (y >= M) * M, b + o.b};
  }
  A operator-(A o) {
    int y = x - o.x;
    return {y + (y < 0) * M, b - o.b};
  }
  A operator*(A o) { return {(int)(1LL * x * o.x % M), b * o.b}; }
  explicit operator ull() { return x ^ (ull)b << 21; }
};

typedef A<1000000007, A<1000000009, unsigned>> Hash;

const int BASE = rnd(300, 500);
struct HashInterval {
  vector<Hash> ha, pw;
  HashInterval(const string& str) : ha(sz(str) + 1), pw(ha) {
    pw[0] = 1;
    rep(i, 0, sz(str)) ha[i + 1] = ha[i] * BASE + str[i],
                              pw[i + 1] = pw[i] * BASE;
  }
  Hash hashInterval(int a, int b) {  // hash [a, b)
    return ha[b] - ha[a] * pw[b - a];
  }
};

vector<Hash> getHashes(const string& str, int length) {
  if (sz(str) < length) return {};
  Hash h = 0, pw = 1;
  rep(i, 0, length) h = h * BASE + str[i], pw = pw * BASE;
  vector<Hash> ret = {h};
  rep(i, length, sz(str)) {
    ret.push_back(h = h * BASE + str[i] - pw * str[i - length]);
  }
  return ret;
}

Hash hashString(const string& s) {
  Hash h{};
  for (char c : s) h = h * BASE + c;
  return h;
}