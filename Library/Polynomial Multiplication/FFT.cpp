
template <typename Double = Double>
struct Complex {
  Double real, imag;
  Complex() : real(0), imag(0) {}
  Complex(Double n) : real(n), imag(0) {}
  Complex(Double r, Double i) : real(r), imag(i) {}
  Complex operator+(Complex b) { return Complex(real + b.real, imag + b.imag); }
  Complex operator+=(Complex b) {
    real += b.real, imag += b.imag;
    return *this;
  }
  Complex operator-(Complex b) { return Complex(real - b.real, imag - b.imag); }
  Complex operator*(Complex b) {
    return Complex(real * b.real - imag * b.imag,
                   real * b.imag + imag * b.real);
  }
  Complex operator/(Double n) { return Complex(real / n, imag / n); }
  Complex operator*=(Complex b) { return (*this) = (*this) * b; }
  Complex operator/=(Double n) { return (*this) = (*this) / n; }
  Complex conj() const { return Complex(real, -imag); }
};

// kactl
using C = Complex<>;
using vd = vector<Double>;
void fft(vector<C>& a) {
  int n = sz(a), L = 31 - __builtin_clz(n);
  static vector<C> R(2,
                     1);  // (use long double here if more accuracy is needed.).
  static vector<C> rt(2, 1);
  for (static int k = 2; k < n; k *= 2) {
    R.resize(n);
    rt.resize(n);
    auto x = polar(1.0, acos(-1.0) / k);
    C x_c(x.real(), x.imag());
    rep(i, k, 2 * k) rt[i] = R[i] = i & 1 ? R[i / 2] * x_c : R[i / 2];
  }
  vi rev(n);
  rep(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
  rep(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int k = 1; k < n; k *= 2)
    for (int i = 0; i < n; i += 2 * k) rep(j, 0, k) {
        auto x = (Double*)&rt[j + k], y = (Double*)&a[i + j + k];
        C z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);
        a[i + j + k] = a[i + j] - z;
        a[i + j] += z;
      }
}
vd conv(const vd& a, const vd& b) {
  if (a.empty() || b.empty()) return {};
  vd res(sz(a) + sz(b) - 1);
  int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
  vector<C> in(n), out(n);
  copy(all(a), begin(in));
  rep(i, 0, sz(b)) in[i].imag = b[i];
  fft(in);
  for (C& x : in) x *= x;
  rep(i, 0, n) out[i] = in[-i & (n - 1)] - in[i].conj();
  fft(out);
  rep(i, 0, sz(res)) res[i] = out[i].imag / (4 * n);
  return res;
}