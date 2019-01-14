#include <bits/stdc++.h>
using namespace std;
#define popCnt(x) (__builtin_popcountll(x))
typedef long long Long;
typedef unsigned long long ULong;
typedef array<int, 2> Pos;

const int N = 666;
const int SZ = 999;
const int MID = (SZ + 1) / 2;

Pos rooks[N];
bool occupied[SZ + 1][SZ + 1];
Pos king;

void readUpdate() {
  int k, x, y;
  cin >> k >> x >> y;
  if (k == -1) exit(0);
  --k;
  occupied[rooks[k][0]][rooks[k][0]] = false;
  rooks[k] = Pos( { x, y });
  occupied[x][y] = true;
}

void moveKing(const Pos& nxt) {
  king = nxt;
  cout << king[0] << " " << king[1] << endl;
  readUpdate();
}

void moveTowards(const Pos& goal) {
  while (king != goal) {
    Pos nxt = king;
    for (int i = 0; i < 2; ++i) {
      if (king[i] < goal[i]) ++nxt[i];
      if (king[i] > goal[i]) --nxt[i];
    }
    if (occupied[nxt[0]][nxt[1]]) {
      nxt[0] = king[0];
    }
    moveKing(nxt);
  }
}

Pos getEndPoint() {
  int cnt[2][2] = { 0 };
  fill((&cnt[0][0]), (&cnt[0][0]) + 4, N);

  for (auto rook : rooks) {
    int opp_x = SZ - rook[0] + 1;
    int opp_y = SZ - rook[1] + 1;
    --cnt[opp_x > MID][opp_y > MID];
  }

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      if (cnt[i][j] >= MID) {
        return Pos( { (i == 0 ? 1 : SZ), (j == 0 ? 1 : SZ) });
      }
    }
  }

  assert(false);
  return Pos( { -1, -1 });
}

int main() {
//  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifdef Local
  freopen("test.in", "r", stdin);
#else
//#define endl '\n'
#endif

  cin >> king[0] >> king[1];

  for (auto& rook : rooks) {
    cin >> rook[0] >> rook[1];
    occupied[rook[0]][rook[1]] = true;
  }

  moveTowards(Pos( { MID, MID }));
  moveTowards(getEndPoint());

}
