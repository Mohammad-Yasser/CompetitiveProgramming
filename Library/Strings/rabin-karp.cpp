const int MOD = 179424673;

const int kBase[2] = {5, 7};

const int N = 5e6 + 5;
int base_power[N];

int arrForward[N];
int arrBackward[N];

string s;

void init() {
  base_power[0] = 1;
  for (int i = 1; i < N; ++i) {
    base_power[i] = 1LL * base_power[i - 1] * kBase[0] % MOD;
  }
}

vector<int> build(string s) {
  for (char& c : s) {
    ++c;
    c -= 'a';
  }

  vector<int> res(s.size() + 1, 0);
  res[0] = 1;
  for (int i = 0; i < s.size(); ++i) {
    res[i + 1] = (1LL * res[i] * kBase[0] + s[i]) % MOD;
  }
  return res;
}

int getRangeFor(int l, int r, const vector<int>& arrForward) {
  if (l > r) return -1;
  ++l, ++r;
  int res = arrForward[r];
  int tmp_l = 1LL * arrForward[l - 1] * base_power[r - l + 1] % MOD;
  res = (res - tmp_l + MOD) % MOD;
  return res;
}

bool isPal(int l, int r) { return getRangeFor(l, r) == getRangeBack(l, r); }
