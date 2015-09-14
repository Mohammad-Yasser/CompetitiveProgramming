#include <bits/stdc++.h>
using namespace std;
typedef complex<double> Complex;
const Complex I(0, 1);


const double PI = acos(-1);

void fft(double theta, vector<Complex> &a) {
	int n = a.size();
	for (int m = n; m >= 2; m >>= 1) {
		int mh = m >> 1;
		for (int i = 0; i < mh; i++) {
			Complex w = exp(i * theta * I);
			for (int j = i; j < n; j += m) {
				int k = j + mh;
				Complex x = a[j] - a[k];
				a[j] += a[k];
				a[k] = w * x;
			}
		}
		theta *= 2;
	}
	int i = 0;
	for (int j = 1; j < n - 1; j++) {
		for (int k = n >> 1; k > (i ^= k); k >>= 1) {
		}
		if (j < i)
		  swap(a[i], a[j]);
	}
}

void fft(vector<Complex> &a) {
	int n = ceil(log(a.size()) / log(2));
	a.resize(1 << n);
	fft(2 * PI / a.size(), a);
}
void ifft(vector<Complex> &a) {
	int n = ceil(log(a.size()) / log(2));
	a.resize(1 << n);
	fft(-2 * PI / a.size(), a);
	for (int i = 0; i < a.size(); i++)
		a[i] /= a.size();
}

vector<int> mul(const vector<int> &poly1, const vector<int> &poly2) {
	int size = poly1.size() + poly2.size() + 1;
	vector<Complex> p1(size), p2(size), ans;

	for (int i = 0; i < poly1.size(); ++i)
		p1[i] = poly1[i];

	for (int i = 0; i < poly2.size(); ++i)
		p2[i] = poly2[i];

	fft(p1), fft(p2);

	size = p1.size();

	ans.resize(size);

	for (int i = 0; i < size; ++i)
		ans[i] = p1[i] * p2[i];

	ifft(ans);

	vector<int> ret(size);
	for (int i = 0; i < size; ++i)
		ret[i] = round(ans[i].real());

	return ret;

}

vector<int> poly(200001);

int main() {

	int n;
	while (cin >> n) {
		fill(poly.begin(), poly.end(), 0);
		while (n--) {
			int ind;
			cin >> ind;
			poly[ind] = 1;
		}

		vector<int> vec(mul(poly, poly));
		int m, ans = 0;
		cin >> m;
		while (m--) {
			int ind;
			cin >> ind;
			ans += !!vec[ind] or poly[ind];
		}
		cout << ans << '\n';
	}

}
