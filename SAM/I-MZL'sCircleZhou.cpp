#include <bits/stdc++.h>
using namespace std;

#define rep(i,s,t) for(int i=s,i##end=t;i<=i##end;++i)
#define per(i,s,t) for(int i=t,i##end=s;i>=i##end;--i)
#define repo(i,s,t) for(int i=s,i##end=t;i<i##end;++i)
#define debug(x) cerr<<#x<<" : "<<(x)<<" "<<__FUNCTION__<<__LINE__<<endl
#define us unsigned

const int MAXN = 90005;

struct SAM {
	static const int MAXN = ::MAXN * 2, MAXC = 30, C = 26;
	int trans[MAXN][MAXC], fa[MAXN], mxlen[MAXN];
	long long sum, cnt[MAXC];
	int sz[MAXN];
	int alloc, lst;

	int newNode() {
		int x = alloc++;
		memset(trans[x], 0, sizeof(trans[x]));
		fa[x] = -1;
		mxlen[x] = 0;
		sz[x] = 0;
		return x;
	}
	void clear() {
		alloc = 0;
		lst = newNode();
		memset(cnt, 0, sizeof(cnt));
	}
	int extend(int c) {
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
		return x;
	}
	
	void initsz() {
		static int deg[MAXN], que[MAXN];
		memset(deg, 0, sizeof(deg));
		int l = 0, r = 0;
		repo (i, 0, alloc) deg[fa[i]]++;
		repo (i, 0, alloc) if (!deg[i]) que[r++] = i;
		while (l != r) {
			int x = que[l++];
			if (!x) continue;
			int t = fa[x];
			sz[t] += sz[x];
			deg[t]--;
			if (!deg[t]) que[r++] = t;
		}
		sz[0] = 1;
	}
	void initcnt() {
		static int deg[MAXN], que[MAXN], ct[MAXN][MAXC];
		memset(deg, 0, sizeof(deg));
		memset(ct, 0, sizeof(ct));
		
		int l = 0, r = 0;
		repo (i, 0, alloc) repo (j, 0, C) {
			if (trans[i][j]) deg[trans[i][j]]++;
		}
		repo (i, 0, C) {
			int t = trans[0][i];
			if (!t) continue;
			ct[t][i]++;
			deg[t]--;
			if (!deg[t]) que[r++] = t;
		}
		while (l != r) {
			int x = que[l++];
			repo (i, 0, C) {
				int t = trans[x][i];
				if (!t) continue;
				repo (j, 0, C) ct[t][j] += ct[x][j];
				deg[t]--;
				if (!deg[t]) que[r++] = t;				
			}
		}
		sum = 1;
		repo (i, 1, alloc) sum += mxlen[i] - mxlen[fa[i]];
		repo (i, 1, alloc) repo (j, 0, C) cnt[j] += ct[i][j];
	}
	void build(const char s[]) {
		clear();
		int n = strlen(s);
		repo (i, 0, n) extend(s[i]);
		initsz();
		initcnt();
	}
	us long long query(long long Bsum, long long Bcnt[]) {
		static int que[MAXN], deg[MAXN];
		int l = 0, r = 0;
		memset(deg, 0, sizeof(deg));
		repo (i, 0, alloc) repo (j, 0, C) {
			if (trans[i][j]) deg[trans[i][j]]++;
		}
		us long long res = 0;
		que[r++] = 0;
		while (l != r) {
			int x = que[l++];
			long long s = Bsum;
			repo (i, 0, C) {
				int t = trans[x][i];
				if (!t) continue;
				s -= Bcnt[i];
				deg[t]--;
				if (!deg[t]) que[r++] = t;
			}
			if (!x) res += s;
			else res += 1ull * s * (mxlen[x] - mxlen[fa[x]]);
		}
		return res;
	}
} samA, samB;

char A[MAXN], B[MAXN];

void Solve() {
	scanf("%s %s", A, B);
	samA.build(A);
	samB.build(B);
	printf("%llu\n", samA.query(samB.sum, samB.cnt));
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) Solve();
	return 0;
}

/*
1
aa
ab

*/
