
const int N = 5003;
int vis[N];
int vis_id;

struct State {
  int getInd() const {}
  bool isVisited() const { return vis[getInd()] == vis_id; }
  void markVisited() const { vis[getInd()] = vis_id; }
  bool valid(bool check_vis = true) const {
    return (!check_vis || !isVisited());
  }
  bool isGoal() const { return true; }
  void process(queue<State>& q) {}
};

queue<State> q;

template <class T>
void clear(queue<T>& q) {
  while (!q.empty()) q.pop();
}

int bfs(const State& start) {
  ++vis_id;
  clear(q);
  q.emplace(start);
  start.markVisited();
  int level = 0;
  while (!q.empty()) {
    int sz = q.size();
    while (sz--) {
      auto curr = q.front();
      q.pop();
      if (curr.isGoal()) return level;
      curr.process(q);
    }
    ++level;
  }
  return -1;
}

//////////////========================================================

const int N = 5003;
const int K = 55;
int vis[N * K * 5];
int vis_id;
int n, m, k;
char grid[N];

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

struct Cell {
  int x, y;
  int getInd() const {
    int res = x * m + y;
    assert(res >= 0 && res < N);
    return res;
  }
  bool valid() const {
    return min(x, y) >= 0 && x < n && y < m && grid[getInd()] != '#';
  }
};

struct State {
  Cell cell;
  int k;
  int more = 0;
  int getInd() const {
    int res = more * N * K + (k * N + cell.getInd());
    assert(res >= 0 && res < N * K * 5);
    return res;
  }
  bool isVisited() const { return vis[getInd()] == vis_id; }
  void markVisited() const { vis[getInd()] = vis_id; }
  bool valid(bool check_vis = true) const {
    return k >= 0 && cell.valid() && (!check_vis || !isVisited());
  }
  bool isGoal() const { return more == 0 && grid[cell.getInd()] == 'B'; }
  void process(queue<State>& q) {
    if (more) {
      State nxt = *this;
      --nxt.more;
      if (nxt.valid()) {
        nxt.markVisited();
        q.push(nxt);
      }
      return;
    }

    for (int i = 0; i < 4; ++i) {
      State nxt = *this;
      nxt.cell.x += dx[i], nxt.cell.y += dy[i];
      if (!nxt.cell.valid()) continue;
      if (grid[nxt.cell.getInd()] == 'D') {
        // Open nxt door.
        ++nxt.more;
        --nxt.k;
      }
      if (!nxt.valid(false)) continue;
      if (nxt.valid()) {
        q.push(nxt);
        nxt.markVisited();
      }
      if (grid[cell.getInd()] == 'D') {
        // Close this door after moving.
        ++nxt.k;
        ++nxt.more;
        if (nxt.valid()) {
          q.push(nxt);
          nxt.markVisited();
        }
      }
    }
  }
};

queue<State> q;

template <class T>
void clear(queue<T>& q) {
  while (!q.empty()) q.pop();
}

int bfs(const State& start) {
  ++vis_id;
  clear(q);
  q.emplace(start);
  start.markVisited();
  int level = 0;
  while (!q.empty()) {
    int sz = q.size();
    while (sz--) {
      auto curr = q.front();
      q.pop();
      if (curr.isGoal()) return level;
      curr.process(q);
    }
    ++level;
  }
  return -1;
}