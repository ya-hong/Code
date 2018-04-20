#include <bits/stdc++.h>
using namespace std;

#define rep(i,s,t) for(int i=s,i##end=t;i<=i##end;++i)
#define per(i,s,t) for(int i=t,i##end=s;i>=i##end;--i)
#define repo(i,s,t) for(int i=s,i##end=t;i<i##end;++i)
#define debug(x) cerr<<#x<<" : "<<x<<" "<<__FUNCTION__<<__LINE__<<endl

const int MAXN = 1005;

struct SAM {
	static const int MAXN = 1005 * 2, MAXC = 30, C = 26;
	int trans[MAXN][MAXC], fa[MAXN], mxlen[MAXN];
	int mipos[MAXN], mxpos[MAXN];
	int alloc, lst;
	vector <int> g[MAXN];

	int newNode() {
		int x = alloc++;
		memset(trans[x], 0, sizeof(trans[x]));
		fa[x] = -1;
		mxlen[x] = 0;
		mipos[x] = MAXN + 1, mxpos[x] = -1;
		return x;
	}
	void clear() {
		alloc = 0;
		lst = newNode();
		repo (i, 0, MAXN) g[i].clear();
	}
	void extend(int c, int ID) {
		c -= 'a';
		int x = newNode(), p = lst;
		lst = x;
		mxlen[x] = mxlen[p] + 1;
		mipos[x] = mxpos[x] = ID;
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
	}

	void dfs(int x) {
		repo (i, 0, g[x].size()) {
			int t = g[x][i];
			dfs(t);
			mipos[x] = min(mipos[x], mipos[t]);
			mxpos[x] = max(mxpos[x], mxpos[t]);
		}
	}
	void build(const char s[]) {
		clear();
		int n = strlen(s);
		repo (i, 0, n) extend(s[i], i);
		repo (i, 1, alloc) {
			g[fa[i]].push_back(i);
		}
		dfs(0);
	}
	int query() {
		int res = 0;
		repo (i, 1, alloc) {
			int l = mxlen[fa[i]] + 1, r = mxlen[i];
			int d = mxpos[i] - mipos[i];
			res += max(0, min(r, d) - l + 1);
		}
		return res;
	}
} sam;

char s[MAXN];

int main() {
	while (true) {
		scanf("%s", s);
		if (s[0] == '#') break;
		sam.build(s);
		printf("%d\n", sam.query());
	}
	return 0;
}
