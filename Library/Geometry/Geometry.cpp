#include <bits/stdc++.h>
using namespace std;

typedef long double Double;

const Double EPS = 1e-10;

enum Relation { LESS_THAN, EQUAL, GREATER_THAN };

bool areEqual(Double x, Double y, Double eps = EPS) {
  auto diff = abs(x - y);
  x = abs(x), y = abs(y);
  if (diff <= eps) return true;
  if (min(x, y) <= eps) return false;
  return diff <= eps * max(x, y);
}

bool isZero(Double x, Double eps = EPS) { return abs(x) <= eps; }

int compareDoubles(Double x, Double y, Double eps = EPS) {
  if (areEqual(x, y, eps)) return Relation::EQUAL;
  if (x < y) return Relation::LESS_THAN;
  return Relation::GREATER_THAN;
}

// Checks if c lies in the range [a,b]. NOTE: if b < a, returns false.
bool checkInRange(Double a, Double b, Double c, Double eps = EPS) {
  if (areEqual(a, c)) return true;
  if (areEqual(b, c)) return true;
  return a <= c && c <= b;
}
