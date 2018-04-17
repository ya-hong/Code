#include <bits/stdc++.h>

using namespace std;

#define rep(i, s, t) for(int i = s, i##end = t; i <= i##end; ++i)
#define repo(i, s, t) for(int i = s, i##end = t; i < i##end; ++i)
#define per(i, s, t) for(int i = t, i##end = s; i >= i##end; --i)
#define debug(x) cerr << #x << " : " << x << " " << __FUNCTION__ << __LINE__ << endl;

#define R ((rand() * rand()) ^ (rand() * rand()))

int rnd(int l, int r) {
	return R % (r - l + 1) + l;
}

int main() {
	srand(time(NULL));

	int n = 10, m = 10;
	cout << n << " "<< m << endl;
	rep (i, 1, n) {
		rep (j, 1, m) cout << rnd(0, 100000) << " ";
		cout << endl;
	}
	rep (i, 1, n) {
		rep (j, 1, m) cout << rnd(0, 100000) << " ";
		cout << endl;
	}
	return 0;
}
