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
	
	int mx[MAXN];
	long long calc() {
		static int deg[MAXN], que[MAXN];
		memset(deg, 0, sizeof(deg));
		
		long long res = 0;
		repo (i, 1, alloc) res += mxlen[i] - mxlen[fa[i]];
		rep (i, 1, alloc) deg[fa[i]]++;
		int l = 0, r = 0;
		rep (i, 1, alloc) if (!deg[i]) que[r++] = i;
		while (l != r) {
			int x = que[l++];
			if (!x) continue;
			mx[x] = min(mx[x], mxlen[x]);
			if (mx[x] > mxlen[fa[x]]) res -= mx[x] - mxlen[fa[x]];
			deg[fa[x]]--;
			mx[fa[x]] = max(mx[fa[x]], mx[x]);
			if (deg[fa[x]] == 0) que[r++] = fa[x];
		}
		return res;
	}
	long long query(const char s[], int n) {
		memset(mx, 0, sizeof(mx));
		int now = 0, len = 0;
		repo (i, 0, n) {
			int c = s[i] - 'a';
			if (s[i] == '#') {
				now = len = 0;
			}
			else {
				while (now && !trans[now][c]) now = fa[now], len = mxlen[now];
				if (trans[now][c]) {
					now = trans[now][c], len++;
					mx[now] = max(mx[now], len);
				}
				else now = 0, len = 0;
			}
		}
		return calc();
	}
} sam;

char s[MAXN];
char B[MAXN * 2], tmp[MAXN];

void Solve() {
	int n;
	scanf("%d", &n);
	scanf("%s", s);
	sam.build(s);
	
	int tot = 0;
	rep (i, 1, n) {
		scanf("%s", tmp);
		repo (j, 0, strlen(tmp)) B[tot++] = tmp[j];
		B[tot++] = '#';
	}
	
	static int cas = 0;
	printf("Case %d: %lld\n", ++cas, sam.query(B, tot));
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		Solve();
	}
	
//	{
//		int mem = 0;
//		mem += sizeof(SAM);
//		mem += sizeof(s);
//		mem += sizeof(B);
//		mem += sizeof(tmp);
//		mem >>= 10;
//		debug(mem);	
//	}
	return 0;
}

/*
1
1
aaa
bbb

*/
