#include <bits/stdc++.h> 
using namespace std;

int p[40004], n;

#ifdef ONLINE_JUDGE
#define endl '\n'
#endif

int lis() {
	set<int> s;
	set<int>::iterator it;
	for (int i = 0; i < n; ++i) {
		s.insert(p[i]);
		it = s.upper_bound(p[i]);
		if (it != s.end())
		  s.erase(it);

	}
	return s.size();
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n ;
	while (cin >> n) {
		for (int i = 0; i < n; ++i)
			cin >> p[i];
		cout << lis() << endl;
	}
}
