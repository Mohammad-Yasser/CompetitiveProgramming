#include <bits/stdc++.h> 
using namespace std;
#define popCnt(x) (__builtin_popcountll(x))
typedef long long ll;
typedef unsigned short ush;
int n, r, c;
const int N = 15;
const int SZ = 10004;
ush arr[N];
vector<ush> masksOfSum[SZ];
ush sumOfMask[1 << N];
char memo[1 << N][101];

inline bool subMask(ush m1, ush m2) {
	return (m1 | m2) == m1;
}

inline ush compSubMask(ush m1, ush m2) {
	return m1 ^ m2;
}

bool dp(ush mask, char width) {
	char &res = memo[mask][width];
	if (res != -1) return res;
	if (__builtin_popcount(mask) == 1)
	  return 1;

	char height = sumOfMask[mask] / width;

	for (char i = height - 1; i >= height - i; --i)
		for (auto &msk : masksOfSum[(height - i) * width])
			if (subMask(mask, msk) && sumOfMask[compSubMask(mask, msk)] == i * width &&
			  dp(msk, width) && dp(compSubMask(mask, msk), width)) return res = 1;

	for (char i = width - 1; i >= width - i; --i)
		for (auto &msk : masksOfSum[(width - i) * height])
			if (subMask(mask, msk) && sumOfMask[compSubMask(mask, msk)] == i * height &&
			  dp(msk, width - i) && dp(compSubMask(mask, msk), i)) return res = 1;

	return res = 0;
}

void genMasksSum() {
	fill(masksOfSum, masksOfSum + SZ, vector<ush>());
	for (int msk = 0; msk < (1 << n); ++msk) {
		int sum = 0;
		for (int i = 0; i < n; ++i)
			sum += !!(msk & (1 << i)) * arr[i];
		sumOfMask[msk] = sum;
		masksOfSum[sum].push_back(msk);
	}
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif
	int cs = 0;
	while (cin >> n, n) {
		memset(memo, -1, sizeof memo);
		cin >> r >> c;
		for (int i = 0; i < n; ++i)
			cin >> arr[i];
		bool res = 0;
		int sum = accumulate(arr, arr + n, 0LL);
		if (sum != r * c) goto nxt;

		genMasksSum();
		res = dp((1 << n) - 1, c);
		nxt: ;
		cout << "Case " << ++cs << ": ";
		if (res)
			cout << "Yes\n";
		else
			cout << "No\n";

	}

}
