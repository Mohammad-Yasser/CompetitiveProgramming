const int MOD = 179424673;

const int kBase[2] = { 5, 7 };

const int N = 5e6 + 5;
int base_power[N];

int arrForward[N];
int arrBackward[N];

bitset<MOD> vis;

string s;

void build() {
  base_power[0] = 1;
  for (int i = 1; i < N; ++i) {
    base_power[i] = 1LL * base_power[i - 1] * kBase[0] % MOD;
  }

  for (char& c : s) {
    ++c;
    c -= 'a';
  }

  arrForward[0] = 1;
  for (int i = 0; i < s.size(); ++i) {
    arrForward[i + 1] = (1LL * arrForward[i] * kBase[0] + s[i]) % MOD;
  }

  arrBackward[s.size()] = 1;
  for (int i = s.size() - 1; i >= 0; --i) {
    arrBackward[i] = (1LL * arrBackward[i + 1] * kBase[0] + s[i]) % MOD;
  }
}

int getRangeFor(int l, int r) {
  ++l, ++r;
  int res = arrForward[r];
  int tmp_l = 1LL * arrForward[l - 1] * base_power[r - l + 1] % MOD;
  res = (res - tmp_l + MOD) % MOD;
  return res;
}

int getRangeBack(int l, int r) {
  int res = arrBackward[l];
  int tmp_r = 1LL * arrBackward[r + 1] * base_power[r - l + 1] % MOD;
  res = (res - tmp_r + MOD) % MOD;
  return res;
}

bool isPal(int l, int r) {
  return getRangeFor(l, r) == getRangeBack(l, r);
}
