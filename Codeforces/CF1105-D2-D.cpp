#include <bits/stdc++.h>
using namespace std;

#define popCnt(x) (__builtin_popcountll(x))
#define getMSB(x) (__builtin_clzll(x))

typedef long long Long;
typedef unsigned long long ULong;

const int N = 1003;
const int P = 10;
char grid[N][N];

int s[P];

queue<pair<int, int>> q[P];

int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };
int n, m;

bool valid(int x, int y) {
  return x >= 0 && y >= 0 && x < n && y < m && (grid[x][y] == '.');
}

void bfs(int p, int s) {
  auto& q = ::q[p];
  while (!q.empty() && s--) {
    int sz = q.size();
    while (sz--) {
      auto curr = q.front();
      q.pop();
      for (int i = 0; i < 4; ++i) {
        int nx = curr.first + dx[i];
        int ny = curr.second + dy[i];
        if (valid(nx, ny)) {
          q.emplace(nx, ny);
          grid[nx][ny] = '0' + p;
        }
      }
    }
  }
}

int res[P];

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifdef Local
  freopen("test.in", "r", stdin);
#else
#define endl '\n'
#endif

  int p;
  cin >> n >> m >> p;
  for (int i = 1; i <= p; ++i) {
    cin >> s[i];
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> grid[i][j];
      if (isdigit(grid[i][j])) {
        q[grid[i][j] - '0'].emplace(i, j);
      }
    }
  }

  while (true) {
    bool player_found = false;
    for (int i = 1; i <= p; ++i) {
      bfs(i, s[i]);
      player_found |= !q[i].empty();
    }
    if (!player_found) break;
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (isdigit(grid[i][j])) {
        ++res[grid[i][j] - '0'];
      }
//      cout << grid[i][j];
    }
//    cout << endl;
  }

  for (int i = 1; i <= p; ++i) {
    cout << res[i] << " ";
  }

}
