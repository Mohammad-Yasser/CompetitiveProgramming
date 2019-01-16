#include "coprobber.h"
#include <bits/stdc++.h>
using namespace std;
 
const int N = 505;
 
vector<int> adj[N];
 
int nxt[N][N];
bool vis[N][N][2];
int losing_children[N][N];
 
int current = 0;
 
void dfs(int cop, int robber, bool cop_turn) {
  if (cop_turn) {
    if (!vis[cop][robber][false]) {
      vis[cop][robber][false] = true;
      nxt[cop][robber] = cop;
      dfs(cop, robber, false);
    }
 
    for (int v : adj[cop]) {
      if (!vis[v][robber][false]) {
        vis[v][robber][false] = true;
        nxt[v][robber] = cop;
        dfs(v, robber, false);
      }
    }
  } else {
    for (int v : adj[robber]) {
      if (++losing_children[cop][v] == adj[v].size()) {
        dfs(cop, v, true);
      }
    }
  }
}
 
int start(int n, bool A[MAX_N][MAX_N]) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (A[i][j]) {
        adj[i].push_back(j);
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    vis[i][i][true] = true;
    dfs(i, i, true);
  }
 
  for (int i = 0; i < n; ++i) {
    bool valid = true;
    for (int j = 0; j < n; ++j) {
      valid &= vis[i][j][false];
    }
    if (valid) {
      current = i;
      return i;
    }
  }
  return -1;
}
 
int nextMove(int R) {
  current = nxt[current][R];
  return current;
}
