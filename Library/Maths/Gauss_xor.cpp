bool isSet(int n, int b) {
  return (n >> b) & 1;
}

int getRank(const vector<int>& mat) {
  vector<int> res = mat;
  int rank = 0;
  for (int row = 0, col = 0; row < res.size() && col < 20; ++col) {
    for (int i = row; i < res.size(); ++i) {
      if (isSet(res[i], col)) {
        swap(res[row], res[i]);
        break;
      }
    }
    if (!isSet(res[row], col)) continue;
    ++rank;
    for (int i = 0; i < res.size(); ++i) {
      if (i == row) continue;
      if (isSet(res[i], col)) {
        res[i] ^= res[row];
      }
    }
    ++row;
  }

  return rank;
}

// Another one, with Longs and iterating from MSB to LSB instead of vice versa.

bool isSet(Long n, int b) {
  return (n >> b) & 1LL;
}

void printRow(int x) {
  cout << bitset<5>(x).to_string() << endl;
}

void printMat(const vector<Long>& mat) {
  for (auto& x : mat) {
    printRow(x);
  }
}

vector<Long> getRREF(const vector<Long>& mat) {
  vector<Long> res = mat;
  int rank = 0;
  for (int row = 0, col = 63; row < res.size() && col >= 0; --col) {
    for (int i = row; i < res.size(); ++i) {
      if (isSet(res[i], col)) {
        swap(res[row], res[i]);
        break;
      }
    }
    if (!isSet(res[row], col)) continue;
    ++rank;
    for (int i = 0; i < res.size(); ++i) {
      if (i == row) continue;
      if (isSet(res[i], col)) {
        res[i] ^= res[row];
      }
    }

    ++row;
  }

  return res;
}

int getRank(const vector<Long>& mat) {
  int res = 0;
  for (auto& x : mat) {
    res += (x != 0);
  }
  return res;
}

