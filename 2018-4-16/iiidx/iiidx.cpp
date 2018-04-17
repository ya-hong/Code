#include <bits/stdc++.h>

using namespace std;

#define rep(i, s, t) for(int i = s, i##end = t; i <= i##end; ++i)
#define repo(i, s, t) for(int i = s, i##end = t; i < i##end; ++i)
#define per(i, s, t) for(int i = t, i##end = s; i >= i##end; --i)
#define debug(x) cerr << #x << " : " << x << " " << __FUNCTION__ << __LINE__ << endl;

const int MAXN = 500005;

int n;
double k;
int d[MAXN];

struct Part1 {
	int pre[MAXN];
	int res[MAXN];
	void main() {
		rep (i, 1, n) pre[i] = (int)(i / k);
		sort(d + 1, d + 1 + n);
		rep (i, 1, n) res[i] = d[i];

		do {
			bool chk = true;
			rep (i, 1, n) if (d[i] < d[pre[i]]) chk = false;
			if (chk) {
				bool mx = false;
				rep (i, 1, n) {
					if (d[i] > res[i]) {
						mx = true;
						break;
					}
					else if (d[i] < res[i]) break;
				}
				if (mx) rep (i, 1, n) res[i] = d[i];
			}
		} while (next_permutation(d + 1, d + 1 + n));

		rep (i, 1, n) printf("%d ", res[i]);
		puts("");
	}
} part1;

struct Part2 {// di 不相同
	vector <int> g[MAXN];
	int sz[MAXN];
	int res[MAXN];

	void dfsinit(int x) {
		sz[x] = 1;
		repo (i, 0, g[x].size()) {
			int t = g[x][i];
			dfsinit(t);
			sz[x] += sz[t];
		}
	}

	void dfs(int x, int p) {
		res[x] = d[p];
		p++;
		per (i, 0, g[x].size() - 1) {
			int t = g[x][i];
			dfs(t, p);
			p += sz[t];
		}
	}

	void main() {
		rep (i, 1, n) {
			int p = (int)(i / k);
			g[p].push_back(i);
		}
		sort(d + 1, d + 1 + n);
		dfsinit(0);
		dfs(0, 0);
		rep (i, 1, n) printf("%d ", res[i]);
		puts("");
	}
} part2;

struct Part3 {// 瞎写
	vector <int> g[MAXN];
	int sz[MAXN];
	int res[MAXN];

	int pre[MAXN], nxt[MAXN];//双向链表
	void init() {
		rep (i, 0, n + 1) {
			pre[i] = i - 1;
			nxt[i] = i + 1;
		}
	}
	void del(int x) {
		pre[nxt[x]] = pre[x];
		nxt[pre[x]] = nxt[x];
	}

	void dfsinit(int x) {
		sz[x] = 1;
		repo (i, 0, g[x].size()) {
			int t = g[x][i];
			dfsinit(t);
			sz[x] += sz[t];
		}
	}

	void dfs(int x, int ed) {
		repo (i, 0, g[x].size()) {
			int t = g[x][i];

			int p = ed, q = ed;
			rep (j, 1, sz[t]) p = pre[p];
			while (d[pre[p]] == d[p]) p = pre[p], q = pre[q];

			del(p);
			res[t] = d[p];
			dfs(t, q);
		}
	}

	void main() {
		init();
		rep (i, 1, n) {
			int p = (int)(i / k);
			g[p].push_back(i);
		}
		sort(d + 1, d + 1 + n);
		dfsinit(0);
		dfs(0, n + 1);

		rep (i, 1, n) printf("%d ", res[i]);
		puts("");
	}
} part3;

bool judge1() {
	return n <= 10;
}
bool judge2() {
	bool chk = true;
	sort(d + 1, d + 1 + n);
	rep (i, 2, n) if (d[i] == d[i - 1]) chk = false;
	return chk;
}

void Read() {
	scanf("%d%lf", &n, &k);
	rep (i, 1, n) scanf("%d", &d[i]);
}
void Solve() {
	if (0);
	else if (judge1()) {
		part1.main();
	}
	else if (judge2()) {
		part2.main();
	}
	else {
		part3.main();
	}
}

int main() {
	Read();
	Solve();
	return 0;
}
