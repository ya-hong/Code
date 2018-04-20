#include <bits/stdc++.h>
using namespace std;

#define rep(i,s,t) for(int i=s,i##end=t;i<=i##end;++i)
#define per(i,s,t) for(int i=t,i##end=s;i>=i##end;--i)
#define repo(i,s,t) for(int i=s,i##end=t;i<i##end;++i)
#define debug(x) cerr<<#x<<" : "<<(x)<<" "<<__FUNCTION__<<__LINE__<<endl

const int MAXN = 100005;


struct SAM {
	static const int MAXN = 100005 * 2, MAXC = 30, C = 26;
	int trans[MAXN][MAXC], fa[MAXN], mxlen[MAXN], mip[MAXN], sz[MAXN];
	vector <int> rpos[MAXN];
	int alloc, lst;

	int newNode() {
		int x = alloc++;
		memset(trans[x], 0, sizeof(trans[x]));
		fa[x] = -1;
		mxlen[x] = 0;
		rpos[x].clear();
		mip[x] = MAXN - 1;
		sz[x] = 0;
		return x;
	}
	void clear() {
		alloc = 0;
		lst = newNode();
	}
	int extend(int c, int ID) {
		c -= 'a';
		int x = newNode(), p = lst;
		lst = x;
		mip[x] = ID;
		sz[x] = 1;
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
	void init() {
		static int deg[MAXN], que[MAXN];
		memset(deg, 0, sizeof(deg));
		int l = 0, r = 0;
		repo (i, 1, alloc) deg[fa[i]]++;
		repo (i, 1, alloc) if (!deg[i]) que[r++] = i;
		while (l != r) {
			int x = que[l++];
			if (!x) continue;
			int t = fa[x];
			mip[t] = min(mip[t], mip[x]);
			sz[t] += sz[x];
			deg[t]--;
			if (!deg[t]) que[r++] = t;
		}
	}
	void query(const char s[]) {
		clear();
		int n = strlen(s);
		repo (i, 0, n) extend(s[i], i);
		init();
		for (int i = 0; i < n;) {
			int j = i, now = 0, pre = 0;
			for (;j < n; ++j) {
				int c = s[j] - 'a';
				now = trans[now][c];
				if (!(sz[now] != 1 && j != mip[now])) break;
				pre = now;
			}
			if (j == i) printf("%d %d\n", -1, s[i]), i = j + 1;
			else printf("%d %d\n", j - i, mip[pre] - (j - i - 1)), i = j;
		}
	}
} sam;

char s[MAXN];

int main() {
	int T;
	scanf("%d", &T);
	rep (t, 1, T) {
		printf("Case #%d:\n", t);
		scanf("%s", s);
		sam.query(s);
	}
	return 0;
}
