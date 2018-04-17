#include <bits/stdc++.h>

using namespace std;

#define rep(i, s, t) for(int i = s, i##end = t; i <= i##end; ++i)
#define repo(i, s, t) for(int i = s, i##end = t; i < i##end; ++i)
#define per(i, s, t) for(int i = t, i##end = s; i >= i##end; --i)
#define debug(x) cerr << #x << " : " << x << " " << __FUNCTION__ << __LINE__ << endl;

int res;

void dfs(int x, int pre) {
	if (x == 11) {
		res++;
		return;
	}
	rep (i, pre, 10) {
		dfs(x + 1, i);
	}
}

int main() {
	dfs(1, 0);
	debug(res);
	return 0;
}
