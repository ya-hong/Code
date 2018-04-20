#include <bits/stdc++.h>
using namespace std;

#define rep(i,s,t) for(int i=s,i##end=t;i<=i##end;++i)
#define per(i,s,t) for(int i=t,i##end=s;i>=i##end;--i)
#define repo(i,s,t) for(int i=s,i##end=t;i<i##end;++i)
#define debug(x) cerr<<#x<<" : "<<x<<" "<<__FUNCTION__<<__LINE__<<endl

const int MAXN = 100005;

struct SAM {
	static const int MAXN = 200005 * 2, MAXC = 30, C = 27;
	
	int trans[MAXN][MAXC], fa[MAXN], mxlen[MAXN];
	int cnt[MAXN];
	int alloc, lst;

	int newNode() {
		int x = alloc++;
		memset(trans[x], 0, sizeof(trans[x]));
		fa[x] = -1;
		mxlen[x] = 0;
		return x;
	}
	void clear() {
		alloc = 0;
		lst = newNode();
	}
	void extend(int c) {
		c -= 'a';
		int x = newNode(), p = lst;
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
	void build() {
		static int que[MAXN], deg[MAXN];
		int l = 0, r = 0;
		memset(deg, 0, sizeof(deg));
		memset(cnt, 0, sizeof(cnt));
		cnt[0] = 1;
		repo (i, 0, alloc) {
			repo (j, 0, C) if (trans[i][j]) deg[trans[i][j]]++;
		}
		que[r++] = 0;
		while (l != r) {
			int x = que[l++];
			repo (i, 0, C - 1) {
				int t = trans[x][i];
				if (!t) continue;
				cnt[t] += cnt[x];
				deg[t]--;
				if (!deg[t]) que[r++] = t;
			}
			if (trans[x][C - 1]) {
				int t = trans[x][C - 1];
				deg[t]--;
				if (!deg[t]) que[r++] = t;
			}
		}
	}
	int query(const char s[]) {
		int now = 0, n = strlen(s);
		repo (i, 0, n) {
			int c = s[i] - 'a';
			if (!trans[now][c]) return 0;
			now = trans[now][c];
		}
		return cnt[now];
	}
} sam;

char s[MAXN];

void Solve() {
	static int T = 0;
	printf("Case #%d:\n", ++T);
	
	sam.clear();
	int n, m;
	scanf("%d %d", &n, &m);
	rep (i, 1, n) {
		scanf("%s", s);
		repo (k, 0, strlen(s)) sam.extend(s[k]);
		sam.extend('z' + 1);
	}
	sam.build();
	rep (i, 1, m) {
		scanf("%s", s);
		printf("%d\n", sam.query(s));
	}
}

int main() {
	int T;
	cin >> T;
	while (T--) Solve();
	return 0;
}

