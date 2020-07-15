int calcSpiralCell(int x, int y) {
  if (x == 0 && y == 0) return 0;
  int width = 2 * x;
  if (x < 0) width = 2 * (-x + 1);
  if (x == 0) width = 1;
  int length = 2 * y;
  if (y < 0) length = 2 * (-y + 1);
  if (y == 0) length = 1;
  int sz = max(length, width);
  int area = sz * sz;
  if (x >= 0 && width == sz) {
    return area - (y + sz / 2);
  }
  if (x < 0 && width == sz) {
    return area - 2 * sz + y - sz / 2 + 1;
  }
  if (y >= 0 && length == sz) {
    return area - 2 * sz + x + sz / 2;
  }
  if (y < 0 && length == sz) {
    return area - 3 * sz - (sz / 2 + x) + 3;
  }
  assert(false);
  return -1;
}

Long calcKthCorner(int k) {
  --k;
  Long n = k / 2;
  Long res = n * (n + 1) + (k % 2) * (n + 1);
  return res;
}
