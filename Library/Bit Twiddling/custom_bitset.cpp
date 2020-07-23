struct Bitset {
  uint64_t* arr = nullptr;
  int size;
  static const int MASK = 63;
  Bitset(int n) : size((n + 63) / 64), arr(new uint64_t[(n + 63) / 64]) {}
  bool test(int ind) const { return arr[ind >> 6] & (1ULL << (ind & MASK)); }
  void set(int ind, bool val) {
    if (val) {
      arr[ind >> 6] |= (1ULL << (ind & MASK));
    } else {
      arr[ind >> 6] &= ~(1ULL << (ind & MASK));
    }
  }
  void reset() {
    for (int i = 0; i < size; ++i) {
      arr[i] = 0;
    }
  }
};