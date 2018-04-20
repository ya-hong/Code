#include <bits/stdc++.h>
using namespace std;

#define rep(i,s,t) for(int i=s,i##end=t;i<=i##end;++i)
#define per(i,s,t) for(int i=t,i##end=s;i>=i##end;--i)
#define repo(i,s,t) for(int i=s,i##end=t;i<i##end;++i)
#define debug(x) cerr<<#x<<" : "<<x<<" "<<__FUNCTION__<<__LINE__<<endl

const int MAXN = 100005;

struct SAM {
	static const int MAXN = 100005 * 2;
	int fa[MAXN], trans[MAXN][30], mxlen[MAXN], sz[MAXN];
	vector <int> g[MAXN];
	int alloc, lst;

	int newNode() {
		int p = ++alloc;
		fa[p] = -1;
		memset(trans[p], 0, sizeof(trans[p]));
		mxlen[p] = 0;
		return p;
	}
	void clear() {
		alloc = -1;
		lst = newNode();
		repo (i, 0, MAXN) g[i].clear();
	}
	SAM() {
		clear();
	}
	void extend(int c) {
		c -= 'a';
		int x = newNode(), p = lst;
		lst = x;
		mxlen[x] = mxlen[p] + 1;
		sz[x] = 1;
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
				fa[y] = fa[q];
				fa[x] = fa[q] = y;
				memcpy(trans[y], trans[q], sizeof(trans[q]));
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
	int mark[MAXN];
	long long query(char s[]) {
		static int T = 0;
		T++;

		int n = strlen(s);
		repo (i, 0, n - 1) s[i + n] = s[i];

		int now = 0, len = 0;
		long long res = 0;
		repo (i, 0, n + n - 1) {
			int c = s[i] - 'a';
			while (now && !trans[now][c]) now = fa[now], len = mxlen[now];
			if (trans[now][c]) now = trans[now][c], len++;
			while (mxlen[fa[now]] >= n) now = fa[now], len = mxlen[now];
			if (len >= n && mark[now] != T) {
				mark[now] = T;
				res += sz[now];
			}
		}
		return res;
	}
} sam;

int n;
char str[MAXN], tmp[MAXN * 2];

int main() {
	scanf("%s", str);
	sam.build(str);
	cin >> n;
	rep (i, 1, n) {
		scanf("%s", tmp);
		printf("%lld\n", sam.query(tmp));
	}
	return 0;
}
