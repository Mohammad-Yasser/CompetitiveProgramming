#include <bits/stdc++.h>
using namespace std;
 
const int MOD = 98765431;
 
#define rep(x,y) for (int x = 0 ; x < (y) ; ++x)
 
typedef long long ll;
typedef vector<vector<ll> > Matrix;
typedef vector<ll> row;
 
Matrix matMulti(Matrix& m1, Matrix& m2) {
 
	ll r1 = m1.size(), c1 = m1[0].size();
	ll r2 = m2.size(), c2 = m2[0].size();
	Matrix res(r1, row(c2, 0));
	if (c1 != r2)
		return res;
 
	rep(i, r1)
		rep(j, c2)
			rep(k, c1)
				res[i][j] = (res[i][j] + 1LL * m1[i][k] * m2[k][j]) % MOD;
	return res;
}
 
Matrix ident(ll size) {
	Matrix res(size, row(size));
	for (ll i = 0; i < size; ++i)
		for (ll j = 0; j < size; ++j)
			res[i][j] = i == j;
	return res;
}
 
Matrix matPower(Matrix& mat, ll p) {
 
	if (!p)
		return ident(mat.size());
 
	Matrix res;
	res = matPower(mat, p / 2);
	res = matMulti(res, res);
 
	if (p % 2 != 0)
		res = matMulti(res, mat);
 
	return res;
}
int main() {
	Matrix trans(2, row(2));
 
	ll n, t;
	cin >> n >> t;
	ll c[n];
	ll sum = 0;
	for (ll i = 0; i < n; ++i)
		cin >> c[i], sum += c[i];
 
	trans[0][0] = n - 2, trans[1][0] = n - 1, trans[0][1] = 1, trans[1][1] = 0;
 
	trans = matPower(trans, t);
 
	for (int i = 0; i < n; ++i) {
		Matrix mat(2, row(2));
		mat[0][0] = (sum - c[i]) % MOD, mat[0][1] = c[i], mat[1][0] = 123, mat[1][1] = 1234;
 
		cout << (matMulti(mat, trans)[0][1] % MOD + MOD) % MOD << '\n';
 
	}
 
}
