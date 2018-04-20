#include <bits/stdc++.h>
using namespace std;

#define rep(i,s,t) for(int i=s,i##end=t;i<=i##end;++i)
#define per(i,s,t) for(int i=t,i##end=s;i>=i##end;--i)
#define repo(i,s,t) for(int i=s,i##end=t;i<i##end;++i)
#define debug(x) cerr<<#x<<" : "<<x<<" "<<__FUNCTION__<<__LINE__<<endl

const int MAXN = 250005;

template <int MAXN>
struct disJointSet {
	int fa[MAXN];
	disJointSet() {
		repo (i, 0, MAXN) fa[i] = i;
	}
	int find(int x) {
		return fa[x] == x ? x : fa[x] = find(fa[x]);
	}
	void merge(int x, int y) {
		x = find(x), y = find(y);
		fa[x] = y;
	}
};

struct SAM {
	static const int MAXN = 250005 * 2, MAXC = 30, C = 26;
	int trans[MAXN][MAXC], fa[MAXN], mxlen[MAXN], k;
	int alloc, lst;

	vector <int> g[MAXN];
	disJointSet <MAXN> S;
	int sz[MAXN], del[MAXN];
	long long sum;

	int newNode() {
		int x = alloc++;
		memset(trans[x], 0, sizeof(trans[x]));
		fa[x] = -1;
		mxlen[x] = 0;
		g[x].clear();
		sz[x] = del[x] = 0;
		return x;
	}
	void clear() {
		alloc = 0;
		sum = 0;
		lst = newNode();
	}
	int extend(int c) {
		c -= 'a';
		int x = newNode(), p = lst;
		sz[x] = 1;
		lst = x;
		mxlen[x] = mxlen[p] + 1;
		while (p != -1 && !trans[p][c]) {
			trans[p][c] = x;
			p = fa[p];
		}
		if (p == -1) fa[x] = 0;
		else {
			int q = trans[p][c];
			if (mxlen[p] + 1 == mxlen[q]) fa[x] = q;
			else {
				int y = newNode();
				memcpy(trans[y], trans[q], sizeof(trans[q]));
				fa[y] = fa[q];
				fa[x] = fa[q] = y;
				mxlen[y] = mxlen[p] + 1;
				while (trans[p][c] == q) {
					trans[p][c] = y;
					p = fa[p];
				}
			}
		}
		return x;
	}

	void dfs(int x) {
		repo (i, 0, g[x].size()) {
			int t = g[x][i];
			dfs(t);
			sz[x] += sz[t];
		}
	}
	void build(int n, const char s[], int num[], int _k) {
		clear();
		k = _k;
		repo (i, 0, n) num[i] = extend(s[i]);
		repo (i, 1, alloc) g[fa[i]].push_back(i);
		dfs(0);
		repo (i, 1, alloc) if (sz[i] >= k) sum += mxlen[i] - mxlen[fa[i]];
	}
	void erase(int x) {
		long long res = 0;
		int d = 1;
		x = S.find(x);
		while (x) {
			int pre = sz[x];
			sz[x] -= d;
			del[x] += d;
			d = del[x];
			if (sz[x] >= k) break;
			del[x] = 0;
			if (pre >= k) res += mxlen[x] - mxlen[fa[x]];
			S.merge(x, fa[x]);
			x = S.find(x);
		}
		sum -= res;
	}
	long long query() {
		return sum;
	}
} sam;

char s[MAXN];
int ID[MAXN], tot;

int tp[MAXN];
char c[MAXN];
long long res[MAXN];

void Solve(int n, int m, int k) {
	scanf("%s", s);
	tot = n;
	rep (i, 1, m) {
		scanf("%d", &tp[i]);
		char tmp[5];
		if (tp[i] == 1) {
			scanf("%s", tmp), c[i] = tmp[0];
			s[tot++] = c[i];
		}
	}
	sam.build(tot, s, ID, k);
//	debug(sam.query());
	per (i, 1, m) {
		if (tp[i] == 1) sam.erase(ID[--tot]);
		else res[i] = sam.query();
	}
	rep (i, 1, m) if (tp[i] == 2) printf("%lld\n", res[i]);
}

int main() {
	int n, m, k;
	while (cin >> n >> m >> k) Solve(n, m, k);
	return 0;
}

/*
7 5 3
cdaaacd
1 b
1 d
1 a
1 b
2 

11 1 3
cdaaacdbdab
2

*/
