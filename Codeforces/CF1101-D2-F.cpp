#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
gp_hash_table<int, int> table;
using namespace std;
#define popCnt(x) (__builtin_popcountll(x))
typedef long long Long;
typedef unsigned long long ULong;

const int N = 1e5;

int a[N];

struct Truck {
  int s, f, c, r;
};

vector<Truck> trucks;
int n;

Long getFuel(int a, int b, int c) {
  return 1LL * (b - a) * c;
}

bool can(Long v, const Truck& truck) {
  Long curr = v;
  int r = truck.r;
  for (int i = truck.s; i < truck.f; ++i) {
    Long fuel = getFuel(a[i], a[i + 1], truck.c);
    if (fuel > v) return false;
    if (fuel > curr) {
      curr = v, --r;
    }
    curr -= fuel;
  }
  return r >= 0;
}

Long bs(const Truck& truck) {
  Long low = 0, high = LLONG_MAX / 2, ans = high;
  while (low <= high) {
    Long mid = (low + high) / 2;
    if (can(mid, truck)) {
      ans = mid;
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  return ans;
}

Long solve() {
  Long ans = 0;
  for (auto& truck : trucks) {
    if (can(ans, truck)) continue;
    ans = max(ans, bs(truck));
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifdef Local
  freopen("test.in", "r", stdin);
#else
#define endl '\n'
#endif

  srand(time(0));

  int m;
  cin >> n >> m;
  trucks.resize(m);

  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }

  for (auto& truck : trucks) {
    cin >> truck.s >> truck.f >> truck.c >> truck.r;
  }

  random_shuffle(trucks.begin(), trucks.end());

  cout << solve() << endl;

}
