int lvl[N], anc[N][MaxLog];

void dfs(int node, int level) {
	lvl[node] = level;
	for (int child : children[node]) {
		dfs(child, level + 1);
	}
}

void buildLCA() {
	dfs(1, 1);
	for (int i = 1; i <= n; ++i) {
		anc[i][0] = parent[i];
	}

	for (int j = 1; j < MaxLog; ++j) {
		for (int i = 1; i <= n; ++i) {
			anc[i][j] = anc[anc[i][j - 1]][j - 1];
		}
	}
}

int getLCA(int i, int j) { // returns node ID (LCA for i, j)
	int st = MaxLog - 1;
	if (lvl[i] > lvl[j])
		swap(i, j);
	int cur = lvl[j];
	for (; st >= 0; st--)
		if (cur - (1 << st) >= lvl[i])
			cur -= (1 << st), j = anc[j][st];
	if (i == j)
		return i;
	cur = lvl[i];
	for (st = MaxLog - 1; st >= 0; st--)
		if (anc[i][st] != anc[j][st])
			cur -= (1 << st), i = anc[i][st], j = anc[j][st];
	return anc[i][0];
}

