struct KMP {
  string s;
  vi pi;
  vector<vi> dfa;

  // kactl
  // Description: pi[x] computes the length of the longest prefix of s that ends
  // at x, other than s[0...x] itself (abacaba -> 0010123).
  static vi buildPi(const string& s) {
    vi p(sz(s));
    rep(i, 1, sz(s)) {
      int g = p[i - 1];
      while (g && s[i] != s[g]) g = p[g - 1];
      p[i] = g + (s[i] == s[g]);
    }
    return p;
  }

  // Returns L[i][j] --> The length of longest prefix of s that matches a
  // suffix of the prefix of length i after appending the character j to it.
  static vector<vi> buildDFA(const string& s, const vi& pi) {
    static const int A = 'z' - 'a' + 1;
    vector<vi> res(sz(s) + 1, vi(A, 0));
    res[0][s[0] - 'a'] = 1;
    for (int i = 0; i < sz(s); ++i) {
      for (int j = 0; j < A; ++j) {
        if (s[i + 1] - 'a' == j) {
          res[i + 1][j] = i + 2;
        } else {
          res[i + 1][j] = res[pi[i]][j];
        }
      }
    }
    return res;
  }

  KMP(const string& s) : s(s) {
    pi = buildPi(s);
    dfa = buildDFA(s, pi);
  }
};
