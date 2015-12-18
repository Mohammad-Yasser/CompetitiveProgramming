#include <bits/stdc++.h> 
using namespace std;
typedef long long ll;

int memo[201][51];

const int INF = 201;

int apt, n, t[51], m1, m2, d[51], e[51];

int dp(int tm, int station) {
	if (tm > apt) return  INF;

	int &ret = memo[tm][station];
	if (ret != -1) return ret;


	ret = INF;
	if (tm <= apt && station == n - 1) ret = apt - tm;


	if (station + 1 < n)
	  for (int i = 0; i < m1; ++i)
		  if (t[station] + d[i] >= tm)
		    ret = min(ret, t[station] + d[i] - tm + dp(t[station + 1] + d[i], station + 1));

	if (station)
	  for (int i = 0; i < m2; ++i)
		  if (t[n - 1] - t[station] + e[i] >= tm)
		    ret = min(ret,
		      t[n - 1] - t[station] + e[i] - tm + dp(t[n - 1] - t[station - 1] + e[i], station - 1));

	return ret;

}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif

	int cs = 0;
	while (cin >> n, n) {
		cin >> apt;
		memset(memo, -1, sizeof memo);
		for (int i = 1; i < n; ++i)
			cin >> t[i], t[i] += t[i - 1];

		cin >> m1;
		for (int i = 0; i < m1; ++i)
			cin >> d[i];

		cin >> m2;
		for (int i = 0; i < m2; ++i)
			cin >> e[i];


		cout << "Case Number " << ++cs << ": ";
		if (dp(0, 0) > apt)
			cout << "impossible\n";
		else
			cout << dp(0, 0) << '\n';
	}

}
