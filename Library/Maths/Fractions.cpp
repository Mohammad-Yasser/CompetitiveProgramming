
__int128 abs(__int128 x) {
  if (x < 0) return -x;
  return x;
}

template <typename Long>
struct Fraction {
  Long num = 0, den = 1;
  Fraction(Long num = 0, Long den = 1) : num(num), den(den) { normalize(); }
  void normalize() {
    Long g = __gcd(num, den);
    num /= g, den /= g;
  }
  Fraction operator*(const Fraction& other) const {
    Fraction res = other;
    res.num *= num;
    res.den *= den;
    res.normalize();
    return res;
  }
  Fraction operator/(const Fraction& other) const {
    return (*this) * Fraction(other.den, other.num);
  }
  Fraction operator+(const Fraction& other) const {
    Fraction res = other;
    Long lcm = res.den / __gcd(res.den, den) * den;
    res.num *= lcm / res.den;
    res.num += lcm / den * num;
    res.den = lcm;
    res.normalize();
    return res;
  }
  Fraction operator-(const Fraction& other) const {
    Fraction res = other * Fraction(-1);
    return (*this) + res;
  }
  bool operator==(const Fraction& other) const {
    // Must be normalized.
    return num == other.num && den == other.den;
  }

  bool isNegative() const { return (num < 0) ^ (den < 0); }

  bool operator<(const Fraction& other) const {
    if ((*this) == other) return false;
    if (den == 0) return false;
    if (other.den == 0) return true;
    if (isNegative() && !other.isNegative()) return true;
    if (!isNegative() && other.isNegative()) return false;
    if (isNegative() && other.isNegative())
      return other * Fraction(-1) < (*this) * Fraction(-1);

    // Uncomment this if it's possible to overflow.

    // if (num / den > other.num / other.den) return false;
    // if (num / den < other.num / other.den) return true;

    // Fraction a = Fraction(den, num % den);
    // Fraction b = Fraction(other.den, other.num % other.den);

    // return b < a;

    return num * other.den < den * other.num;
  }
  friend Fraction abs(const Fraction& x) {
    Fraction res = x;
    res.num = abs(res.num), res.den = abs(res.den);
    return res;
  }

  friend ostream& operator<<(ostream& os, const Fraction& f) {
    return os << f.num << "/" << f.den << " : " << fixed << setprecision(30)
              << 1.0L * f.num / f.den;
  }
};

istream& operator>>(istream& is, __int128& n) {
  Long x;
  is >> x;
  n = x;
  return is;
}

typedef Fraction<__int128> Fract;
