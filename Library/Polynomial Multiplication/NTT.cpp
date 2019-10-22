typedef vector<int> Polynomial;

const int N = (1 << 20) + 3;
const int g = 3, bigp = 479 * (1 << 21) + 1, x = 21;

struct FFTSolver {
  int length_a, length_b;
  // N must be greater than 1 << (ceil(log2(length_a + length_b)))
  int a[N], b[N], w[N], res[N];
  int n;

  int powc(int a, int b) {
    int d;
    if (b == 0) return 1;
    d = powc(a, b / 2);
    d = (Long) d * d % bigp;
    if (b % 2 == 1) d = (Long) d * a % bigp;
    return d;
  }

  inline void fft(int x[], bool inverse) {
    //K is the length of x[]
    //v=0 : DFT,  v=1 : IDFT
    w[0] = 1;
    int G = powc(g, (bigp - 1) / n);
    for (int i = 1; i <= n; i++)
      w[i] = (Long) w[i - 1] * G % bigp;
    for (int i = 0, j = 0; i < n; i++) {
      if (i > j) swap(x[i], x[j]);
      for (int l = n >> 1; (j ^= l) < l; l >>= 1)
        ;
    }
    for (int i = 2; i <= n; i <<= 1)
      for (int j = 0; j < n; j += i)
        for (int l = 0; l < i >> 1; l++) {
          int t;
          if (!inverse)
            t = (Long) x[j + l + (i >> 1)] * w[(n / i) * l] % bigp;
          else
            t = (Long) x[j + l + (i >> 1)] * w[n - (n / i) * l] % bigp;
          x[j + l + (i >> 1)] = ((Long) x[j + l] - t + bigp) % bigp;
          x[j + l] += t;
          x[j + l] %= bigp;
        }
    if (inverse) {
      int r = powc(n, bigp - 2);
      for (int i = 0; i < n; i++)
        x[i] = (Long) x[i] * r % bigp;
    }
  }

  void calculate() {
    //length_a, length_b are length of a[] and b[] (include a[0] and b[0])
    int c = length_a + length_b;
    n = 1;
    while (n <= c) {
      n *= 2;
    }
    for (int i = length_a; i < n; i++)
      a[i] = 0;
    for (int i = length_b; i < n; i++)
      b[i] = 0;
    fft(a, 0);
    fft(b, 0);
    for (int i = 0; i < n; i++) {
      res[i] = (Long) a[i] * b[i] % bigp;
    }
    fft(res, 1);
  }

  Polynomial multiply(const Polynomial& a, const Polynomial& b) {
    length_a = a.size();
    length_b = b.size();

    for (int i = 0; i < length_a; ++i) {
      this->a[i] = a[i];
    }

    for (int i = 0; i < length_b; ++i) {
      this->b[i] = b[i];
    }

    calculate();

    return Polynomial(res, res + n);;
  }
} fft_solver;
