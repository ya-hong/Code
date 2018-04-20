#include <bits/stdc++.h>
using namespace std;

#define rep(i,s,t) for(int i=s,i##end=t;i<=i##end;++i)
#define per(i,s,t) for(int i=t,i##end=s;i>=i##end;--i)
#define repo(i,s,t) for(int i=s,i##end=t;i<i##end;++i)
#define debug(x) cerr<<#x<<" : "<<x<<" "<<__FUNCTION__<<__LINE__<<endl

const int MAXN = 2005;

struct SAM {
	static const int MAXN = 2005 * 2, MAXC = 30, C = 26;
	int trans[MAXN][MAXC], fa[MAXN], mxlen[MAXN];
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
	void build(char s[], int n) {
		clear();
		repo (i, 0, n) extend(s[i]);
	}
	int query() {
		int res = 0;
		repo (i, 1, alloc) {
			res += mxlen[i] - mxlen[fa[i]];
		}
		return res;
	}
} sam;

char s[MAXN];

void Solve() {
	int q;
	scanf("%s", s + 1);
	scanf("%d", &q);
	rep (i, 1, q) {
		int l, r;
		scanf("%d %d", &l, &r);
		sam.build(s + l, r - l + 1);
		printf("%d\n", sam.query());
	}
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		Solve();
	} 
	return 0;
}
