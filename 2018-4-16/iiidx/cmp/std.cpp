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

struct Part2 {
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
			int p = (int)i / k;
			g[p].push_back(i);
		}
		sort(d + 1, d + 1 + n);
		dfsinit(0);
		dfs(0, 0);
		rep (i, 1, n) printf("%d ", res[i]);
		puts("");
	}
} part2;

void Read() {
	scanf("%d%lf", &n, &k);
	rep (i, 1, n) scanf("%d", &d[i]);
}
void Solve() {
	part1.main();
}

int main() {
	Read();
	Solve();
	return 0;
}
