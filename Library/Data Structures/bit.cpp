
template<class INT, int nLeaves>
struct BIT {
  const int kMaxSize = 1 << (int) ceil(log2(nLeaves + 1e-9));
  vector<INT> arr;
  INT size = 0;

  BIT() {
    arr.resize(kMaxSize);
  }

  INT get(int i) {
    i++;
    INT r = 0;
    while (i) {
      r += arr[i - 1];
      i -= i & -i;
    }
    return r;
  }
  
  INT get(int l, int r) {
    if (r < l) return 0;
    if (l == 0) return get(r);
    return get(r) - get(l - 1);
  }


  void add(int i, INT val = 1) {
    size += val;
    i++;
    while (i <= kMaxSize) {
      arr[i - 1] += val;
      i += i & -i;
    }	
  }

  // Finds element at index ind.
  int find(INT ind) {
    int s = 0;
    int m = kMaxSize >> 1;
    while (m) {
      if (arr[s + m - 1] < ind) ind -= arr[(s += m) - 1];
      m >>= 1;
    }
    return s;
  }
};
