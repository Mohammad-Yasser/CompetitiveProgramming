
#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;

typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef pair<ld, ld> pd;

typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<cd> vcd;

template <class T>
using Tree = tree<T, null_type, less_equal<T>, rb_tree_tag,
                  tree_order_statistics_node_update>;

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= (a); i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define trav(a, x) for (auto& a : x)

#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

#define sz(x) (int)x.size()
#define beg(x) x.begin()
#define en(x) x.end()
#define all(x) beg(x), en(x)
#define resz resize

const int MOD = 1000000007;
const ll INF = 1e18;
const int MX = 200005;
const ld PI = 4 * atan((ld)1);

template <class T>
void ckmin(T& a, T b) {
  a = min(a, b);
}
template <class T>
void ckmax(T& a, T b) {
  a = max(a, b);
}

namespace io {
// TYPE ID (StackOverflow)

template <class T>
struct like_array : is_array<T> {};
template <class T, size_t N>
struct like_array<array<T, N>> : true_type {};
template <class T>
struct like_array<vector<T>> : true_type {};
template <class T>
bool is_like_array(const T& a) {
  return like_array<T>::value;
}

// I/O

void setIn(string s) { freopen(s.c_str(), "r", stdin); }
void setOut(string s) { freopen(s.c_str(), "w", stdout); }
void setIO(string s = "") {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  if (sz(s)) {
    setIn(s + ".in"), setOut(s + ".out");
  }
}

// INPUT

template <class T>
void re(T& x) {
  cin >> x;
}
template <class Arg, class... Args>
void re(Arg& first, Args&... rest);
void re(double& x) {
  string t;
  re(t);
  x = stod(t);
}
void re(ld& x) {
  string t;
  re(t);
  x = stold(t);
}

template <class T>
void re(complex<T>& x);
template <class T1, class T2>
void re(pair<T1, T2>& p);
template <class T>
void re(vector<T>& a);
template <class T, size_t SZ>
void re(array<T, SZ>& a);

template <class Arg, class... Args>
void re(Arg& first, Args&... rest) {
  re(first);
  re(rest...);
}
template <class T>
void re(complex<T>& x) {
  T a, b;
  re(a, b);
  x = cd(a, b);
}
template <class T1, class T2>
void re(pair<T1, T2>& p) {
  re(p.f, p.s);
}
template <class T>
void re(vector<T>& a) {
  F0R(i, sz(a)) re(a[i]);
}
template <class T, size_t SZ>
void re(array<T, SZ>& a) {
  F0R(i, SZ) re(a[i]);
}

// OUTPUT

template <class T1, class T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& a) {
  os << '{' << a.f << ", " << a.s << '}';
  return os;
}
template <class T>
ostream& printArray(ostream& os, const T& a, int SZ) {
  os << '{';
  F0R(i, SZ) {
    if (i) {
      os << ", ";
      if (is_like_array(a[i])) cout << "\n";
    }
    os << a[i];
  }
  os << '}';
  return os;
}
template <class T>
ostream& operator<<(ostream& os, const vector<T>& a) {
  return printArray(os, a, sz(a));
}
template <class T, size_t SZ>
ostream& operator<<(ostream& os, const array<T, SZ>& a) {
  return printArray(os, a, SZ);
}

template <class T>
void pr(const T& x) {
  cout << x << '\n';
}
template <class Arg, class... Args>
void pr(const Arg& first, const Args&... rest) {
  cout << first << ' ';
  pr(rest...);
}
}  // namespace io

using namespace io;

template <int SZ>
struct mstree {
  Tree<pi> val[SZ + 1];
  // for offline queries use vector with binary search instead

  void upd(int x, int y,
           int t = 1) {  // x-coordinate between 1 and SZ inclusive
    for (int X = x; X <= SZ; X += X & -X) {
      if (t == 1)
        val[X].insert({y, x});
      else
        val[X].erase({y, x});
    }
  }

  int query(int x, int y) {
    int t = 0;
    for (; x > 0; x -= x & -x) t += val[x].order_of_key({y, MOD});
    return t;
  }

  int query(int lox, int hix, int loy,
            int hiy) {  // query number of elements within a rectangle
    return query(hix, hiy) - query(lox - 1, hiy) - query(hix, loy - 1) +
           query(lox - 1, loy - 1);
  }
};

mstree<MX> M;
https :  // codeforces.com/contest/1093/submission/47051089

         // https://codeforces.com/contest/1093/submission/50972554

         void
         Insert(vector<int>& BIT, int ind, int val) {
  ind++;
  for (int i = ind; i < BIT.size(); i += i & -i) BIT[i] += val;
}

int Get(const vector<int>& BIT, int ind) {
  ind++;
  int res = 0;
  for (int i = ind; i > 0; i -= i & -i) res += BIT[i];
  return res;
}

void Create(int v, int l, int r) {
  if (l == r) {
    sort(my[l].begin(), my[l].end());
    my[l].erase(unique(my[l].begin(), my[l].end()), my[l].end());
    un[v] = my[l];
  } else {
    int m = l + r >> 1;
    int lc = 2 * v, rc = 2 * v + 1;
    Create(lc, l, m);
    Create(rc, m + 1, r);
    set_union(un[lc].begin(), un[lc].end(), un[rc].begin(), un[rc].end(),
              inserter(un[v], un[v].begin()));
  }
  BIT[v].resize(un[v].size() + 1, 0);
}

void Update(int v, int l, int r, int a, int b, int delt) {
  int ind = lower_bound(un[v].begin(), un[v].end(), b) - un[v].begin();
  Insert(BIT[v], ind, delt);
  if (l < r) {
    int m = l + r >> 1;
    if (a <= m)
      Update(2 * v, l, m, a, b, delt);
    else
      Update(2 * v + 1, m + 1, r, a, b, delt);
  }
}

int Get(int v, int l, int r, int l1, int r1, int l2, int r2) {
  if (l == l1 && r == r1) {
    int ind1 = lower_bound(un[v].begin(), un[v].end(), l2) - un[v].begin() - 1;
    int ind2 = upper_bound(un[v].begin(), un[v].end(), r2) - un[v].begin() - 1;
    if (ind1 < ind2)
      return Get(BIT[v], ind2) - Get(BIT[v], ind1);
    else
      return 0;
  } else {
    int m = l + r >> 1;
    int res = 0;
    if (l1 <= m) res += Get(2 * v, l, m, l1, min(m, r1), l2, r2);
    if (m + 1 <= r1)
      res += Get(2 * v + 1, m + 1, r, max(m + 1, l1), r1, l2, r2);
    return res;
  }
}
