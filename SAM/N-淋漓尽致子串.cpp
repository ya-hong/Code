#include <bits/stdc++.h>
using namespace std;

#define rep(i,s,t) for(int i=s,i##end=t;i<=i##end;++i)
#define per(i,s,t) for(int i=t,i##end=s;i>=i##end;--i)
#define repo(i,s,t) for(int i=s,i##end=t;i<i##end;++i)
#define debug(x) cerr<<#x<<" : "<<x<<" "<<__FUNCTION__<<__LINE__<<endl

const int MAXN = 100005;

struct SAM {
	static const int MAXN = ::MAXN * 2, MAXC = 30, C = 26;
	int trans[MAXN][MAXC], fa[MAXN], mxlen[MAXN], sz[MAXN];
	bool mark[MAXN];
	int alloc, lst;
	int newNode() {
		int x = alloc++;
		memset(trans[x], 0, sizeof(trans[x]));
		fa[x] = -1;
		mxlen[x] = 0;
		sz[x] = 1;
		mark[x] = false;
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
	void chk1() {
		int que[MAXN], deg[MAXN];
		bool markson[MAXN];
		memset(deg, 0, sizeof(deg));
		memset(markson, 0, sizeof(markson));
		repo (i, 1, alloc) deg[fa[i]]++;
		int l = 0, r = 0;
		repo (i, 0, alloc) if (!deg[i]) que[r++] = i;
		while (l != r) {
			int x = que[l++];
			if (!x) continue;
			if (!markson[x] && sz[x] > 1) mark[x] = true;
			int t = fa[x];
			sz[t] += sz[x];
			markson[t] |= markson[x] | mark[x];
			deg[t]--;
			if (!deg[t]) que[r++] = t;
		}
	}
	void chk2() {
		vector <int> fr[MAXN];
		int que[MAXN], deg[MAXN];
		bool markson[MAXN];
		memset(deg, 0, sizeof(deg));
		memset(markson, 0, sizeof(markson));
		repo (i, 0, MAXN) fr[i].clear();
		repo (i, 0, alloc) repo (j, 0, C) if (trans[i][j]) {
			int t = trans[i][j];
			fr[t].push_back(i);
			deg[i]++;
		}
		int l = 0, r = 0;
		repo (i, 0, alloc) if (!deg[i]) que[r++] = i;
		while (l != r) {
			int x = que[l++];
			if (markson[x]) mark[x] = false;
			repo (i, 0, fr[x].size()) {
				int t = fr[x][i];
				markson[t] |= markson[x] | mark[x];
				deg[t]--;
				if (!deg[t]) que[r++] = t;
			}
		}
	}
	int query(char s[], int n) {
		clear();
		repo (i, 0, n) extend(s[i]);
		chk1();
		chk2();
		int res = 0;
		repo (i, 1, alloc) res += mark[i];
		return res;
	}
} sam;

char s[MAXN];

int main() {
	scanf("%s", s);
	printf("%d\n", sam.query(s, strlen(s)));
	return 0;
}
