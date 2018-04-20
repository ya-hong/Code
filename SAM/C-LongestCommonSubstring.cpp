#include <bits/stdc++.h>
using namespace std;

#define rep(i,s,t) for(int i=s,i##end=t;i<=i##end;++i)
#define per(i,s,t) for(int i=t,i##end=s;i>=i##end;--i)
#define repo(i,s,t) for(int i=s,i##end=t;i<i##end;++i)
#define debug(x) cerr<<#x<<" : "<<x<<" "<<__FUNCTION__<<__LINE__<<endl

const int MAXN = 100005;

struct SAM {
	static const int MAXN = 100005 * 2, MAXC = 26, C = 26;
	
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
	void build(const char s[]) {
		clear();
		int n = strlen(s);
		repo (i, 0, n) extend(s[i]);
	}
	int query(const char s[]) {
		int n = strlen(s), now = 0, len = 0, res = 0;
		repo (i, 0, n) {
			int c = s[i] - 'a';
			while (now && !trans[now][c]) now = fa[now], len = mxlen[now];
			if (!trans[now][c]) now = 0, len = 0;
			else now = trans[now][c], len++, res = max(res, len);
		}
		return res;
	}
} sam;

char A[MAXN], B[MAXN];

int main() {
	while (scanf("%s %s", A, B) != EOF) {
		sam.build(A);
		cout << sam.query(B) << endl;
	}
	return 0;
}
