#include <bits/stdc++.h>
using namespace std;

#define rep(i,s,t) for(int i=s,i##end=t;i<=i##end;++i)
#define per(i,s,t) for(int i=t,i##end=s;i>=i##end;--i)
#define repo(i,s,t) for(int i=s,i##end=t;i<i##end;++i)
#define debug(x) cerr<<#x<<" : "<<x<<" "<<__FUNCTION__<<__LINE__<<endl

const int MAXN = 1000005;

struct SAM {
	static const int MAXN = 1000005 * 2;

	SAM() {
		clear();
	}
	
	int fa[MAXN], trans[MAXN][30], mxlen[MAXN];
	int alloc, lst;
	vector <int> g[MAXN];
	int sz[MAXN];

	int newNode() {
		int x = ++alloc;
		fa[x] = -1;
		memset(trans[x], 0, sizeof(trans[x]));
		mxlen[x] = 0;
		return x;
	}
	void clear() {
		alloc = -1;
		lst = newNode();
		repo (i, 0, MAXN) g[i].clear();
		memset(sz, 0, sizeof(sz));
	}

	void extend(int c) {
		c -= 'a';
		int x = newNode(), p = lst;
		mxlen[x] = mxlen[p] + 1;
		sz[x] = 1;
		lst = x;
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
				sz[y] = 0;
				memcpy(trans[y], trans[q], sizeof(trans[q]));
				fa[y] = fa[q];
				fa[q] = fa[x] = y;
				mxlen[y] = mxlen[p] + 1;
				while (trans[p][c] == q) {
					trans[p][c] = y;
					p = fa[p];
				}
			}
		}
	}
	void dfs(int x) {
		repo (i, 0, g[x].size()) {
			dfs(g[x][i]);
			sz[x] += sz[g[x][i]];
		}
	}
	void build(const char s[]) {
		int n = strlen(s);
		repo (i, 0, n) extend(s[i]);
		rep (i, 1, alloc) g[fa[i]].push_back(i);
		dfs(0);
	}
	void query(int res[], int n) {
		rep (i, 1, n) res[i] = 0;
		rep (i, 1, alloc) {
			int x = mxlen[i];
			res[x] = max(res[x], sz[i]);
		}
		per (i, 1, n - 1) res[i] = max(res[i], res[i + 1]);
	}
} sam;

char s[MAXN];
int res[MAXN];

int main() {
	scanf("%s", s);
	int n = strlen(s);
	sam.build(s);
	sam.query(res, n);
	rep (i, 1, n) printf("%d\n", res[i]);
	return 0;
}
