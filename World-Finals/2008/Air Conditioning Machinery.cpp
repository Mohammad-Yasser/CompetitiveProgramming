#include <bits/stdc++.h> 
using namespace std;
#define popCnt(x) (__builtin_popcountll(x))
typedef long long ll;

string dir = "xyz";
valarray<int> dim(3), st(3), gl(3), dSt(3), dGl(3);

inline bool invalid(const valarray<int> &pos) {
	return (pos < 0).max() or (pos >= dim).max();
}

inline void read(valarray<int> &dSt, valarray<int> &st) {
	char d1, d2;
	for (int i = 0; i < 3; ++i)
		cin >> st[i];
	st -= 1;
	cin >> d1 >> d2;
	dSt = {0,0,0};
	dSt[dir.find(d2)] += ((d1 == '+') << 1) - 1;

}

bool vis[21][21][21];
int best, curSteps;

inline void init() {
	memset(vis, 0, sizeof vis);
	best = 1e9;
}

inline bool markOrCheck(valarray<int> &curr, valarray<int> &target, valarray<int>&dir, bool mark,
bool check) {
	while ((curr * dir != target * dir).max()) {
		curr += dir;
		if (check) {
			if (vis[curr[0]][curr[1]][curr[2]]) return 0;
		} else
			vis[curr[0]][curr[1]][curr[2]] = mark;
	}
	return 1;
}

void bt(valarray<int>& pos, valarray<int>& dir) {
	if ((pos == gl).min() && (dir == dGl).min()) {
		best = min(best, curSteps);
		return;
	}
	if (++curSteps > 6) {
		--curSteps;
		return;
	}

	for (int a = 3; a > 1; --a) {
		int b = 4 - a;
		for (int d = -b; d <= b; d += 2 * b) {
			valarray<int> v( { 0, 0, 1 });
			do {
				if ((v == abs(dir)).min()) continue;
				valarray<int> curr = pos, target = pos + dir * a + v * d, newDir = v * abs(d) / d;
				if (invalid(target)) continue;
				if (!markOrCheck(curr, target, dir, 0, 1))
				  continue;

				if (!markOrCheck(curr, target, newDir, 0, 1))
				  continue;

				curr = pos;

				markOrCheck(curr, target, dir, 1, 0);
				markOrCheck(curr, target, newDir, 1, 0);

				bt(target, newDir);

				curr = pos;

				markOrCheck(curr, target, dir, 0, 0);
				markOrCheck(curr, target, newDir, 0, 0);
			} while (next_permutation(begin(v), end(v)));
		}
	}

	--curSteps;

}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif

	int cs = 0;
	while (cin >> ws, cin.peek() != '0') {
		init();
		for (int i = 0; i < 3; ++i)
			cin >> dim[i];
		read(dSt, st);
		st -= dSt;
		read(dGl, gl);
		bt(st, dSt);
		cout << "Case " << ++cs << ": ";
		if (best > 6)
			cout << "Impossible\n";
		else
			cout << best << '\n';
	}

}
