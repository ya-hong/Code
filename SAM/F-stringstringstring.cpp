#include <bits/stdc++.h>
using namespace std;

#define rep(i,s,t) for(int i=s,i##end=t;i<=i##end;++i)
#define per(i,s,t) for(int i=t,i##end=s;i>=i##end;--i)
#define repo(i,s,t) for(int i=s,i##end=t;i<i##end;++i)
#define debug(x) cerr<<#x<<" : "<<x<<" "<<__FUNCTION__<<__LINE__<<endl

const int MAXN = 1e5 + 5;

struct SAM {
	static const int MAXN = (1e5 + 5) * 2, MAXC = 30, C = 26;
	int trans[MAXN][MAXC], fa[MAXN], mxlen[MAXN], sz[MAXN];
	int alloc, lst;
	vector <int> g[MAXN];

	int newNode() {
		int x = alloc++;
		memset(trans[x], 0, sizeof(trans[x]));
		fa[x] = -1;
		mxlen[x] = 0;
		sz[x] = 0;
		g[x].clear();
		return x;
	}
	void clear() {
		alloc = 0;
		lst = newNode();
	}
	void extend(int c) {
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
	}

	void dfs(int x) {
		repo (i, 0, g[x].size()) {
			int t = g[x][i];
			dfs(t);
			sz[x] += sz[t];
		}
	}
	void build(const char s[]) {
		clear();
		int n = strlen(s);
		repo (i, 0, n) extend(s[i]);
		repo (i, 1, alloc) g[fa[i]].push_back(i);
		dfs(0);
	}
	long long query(int k) {
		long long res = 0;
		repo (i, 1, alloc) {
			if (sz[i] == k) res += mxlen[i] - mxlen[fa[i]];
		}
		return res;
	}
} sam;

char s[MAXN];

int main() {
	int T, k;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &k);
		scanf("%s", s);
		sam.build(s);
		printf("%lld\n", sam.query(k));
	}
	return 0;
}
