#include <bits/stdc++.h>
using namespace std;
#define popCnt(x) (__builtin_popcountll(x))
typedef long long Long;

const int Base = 127;
constexpr int MOD = round(1e8 + 7);

bitset<MOD> used_hash;

string s;
int n, m, k;

void buildUsedHashes() {
  used_hash.reset();
  for (int i = 0; i + m <= n; ++i) {
    int h = 0;
    for (int j = i; j < i + m; ++j) {
      h = (1LL * Base * h + s[j]) % MOD;
    }
    used_hash[h] = true;
  }
}

string getRandomString() {
  string res(m, 0);
  int h = 0;
  for (char& c : res) {
    c = rand() % k + 'a';
    h = (1LL * Base * h + c) % MOD;
  }
  if (used_hash[h]) return "";
  return res;
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifdef Local
  freopen("test.in", "r", stdin);
#else
#define endl '\n'
#endif

  srand(time(0));

  int t;
  cin >> t;

  while (t--) {
    cin >> n >> m >> k >> s;
    buildUsedHashes();
    string res;
    while (res = getRandomString(), res.empty()) {
    }
    cout << res << endl;
  }
}
