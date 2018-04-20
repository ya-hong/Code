#include <bits/stdc++.h>
using namespace std;

#define rep(i,s,t) for(int i=s,i##end=t;i<=i##end;++i)
#define per(i,s,t) for(int i=t,i##end=s;i>=i##end;--i)
#define repo(i,s,t) for(int i=s,i##end=t;i<i##end;++i)
#define debug(x) cerr<<#x<<" : "<<x<<" "<<__FUNCTION__<<__LINE__<<endl

template <int MAXM>
struct SAM {
	static const int MAXN = MAXM * 2;
	int fa[MAXN], trans[MAXN][30], mxlen[MAXN], milen[MAXN];
	int alloc, lst;
	int newNode() {
		int p = ++alloc;
		fa[p] = -1;
		memset(trans[p], 0, sizeof(trans[p]));
		mxlen[p] = 0;
		milen[p] = 0;
		return p;
	}
	void clear() {
		alloc = -1;
		lst = newNode();
	}
	SAM() {
		clear();
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
		if (p == -1) fa[x] = 0, milen[x] = 1;
		else {
			int q = trans[p][c];
			if (mxlen[p] + 1 == mxlen[q]) fa[x] = q, milen[x] = mxlen[q] + 1;
			else {
				int y = newNode();
				memcpy(trans[y], trans[q], sizeof(trans[q]));
				
				fa[y] = fa[q];
				mxlen[y] = mxlen[p] + 1;
				milen[y] = mxlen[fa[y]] + 1;

				fa[x] = fa[q] = y;
				milen[x] = milen[q] = mxlen[y] + 1;

				while (trans[p][c] == q) {
					trans[p][c] = y;
					p = fa[p];
				}
			}
		}
	}
	void insert(const char s[]) {
		int n = strlen(s);
		repo (i, 0, n) extend(s[i]);
	}
	long long query() {
		long long res = 0;
		rep (i, 1, alloc) {
			res += mxlen[i] - milen[i] + 1;
		}
		return res;
	}
};

const int MAXN = 1000005;

char s[MAXN];
SAM <MAXN> sam;

int main() {
	scanf("%s", s);
	sam.insert(s);
	printf("%lld\n", sam.query());
	return 0;
}
