#include <bits/stdc++.h>
using namespace std;
#define popCnt(x) (__builtin_popcountll(x))
typedef long long Long;
typedef unsigned long long ULong;

/*
 * The terminal state will be alternating characters like abababab.
 * Since the first and last characters don't change, one can know the
 * terminal string length parity. If the first character is the same as
 * the last, then it must be of odd length, else of even length.
 *
 * Since each move changes the parity of the string, then the parity of
 * the number of moves is the parity of the initial string ^ the parity
 * of the terminal string.
 */

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifdef Local
  freopen("test.in", "r", stdin);
#else
#define endl '\n'
#endif

  string s;
  cin >> s;

  cout << (((s.size() & 1) ^ (s[0] == s.back())) ? "First" : "Second");

}
