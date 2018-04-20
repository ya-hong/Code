#include <bits/stdc++.h>
using namespace std;

#define rep(i,s,t) for(int i=s,i##end=t;i<=i##end;++i)
#define per(i,s,t) for(int i=t,i##end=s;i>=i##end;--i)
#define repo(i,s,t) for(int i=s,i##end=t;i<i##end;++i)
#define debug(x) cerr<<#x<<" : "<<(x)<<" "<<__FUNCTION__<<__LINE__<<endl
#define us unsigned

const int MAXN = 1e5 + 5;

struct SAM {
	static const int MAXN = ::MAXN * 2, MAXC = 30, C = 26;
	int trans[MAXN][MAXC], fa[MAXN], mxlen[MAXN], mip[MAXN];
	int alloc, lst;

	int newNode() {
		int x = alloc++;
		memset(trans[x], 0, sizeof(trans[x]));
		fa[x] = -1;
		mxlen[x] = 0;
		mip[x] = MAXN + 1;
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
		mxlen[x] = mxlen[p] + 1;
		mip[x] = ID;
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
	void initMiPos() {
		static int deg[MAXN], que[MAXN];
		memset(deg, 0, sizeof(deg));
		
		int l = 0, r = 0;
		repo (i, 1, alloc) deg[fa[i]]++;
		repo (i, 0, alloc) if (!deg[i]) que[r++] = i;
		while (l != r) {
			int x = que[l++];
			if (!x) continue;
			int t = fa[x];
			mip[t] = min(mip[t], mip[x]);
			deg[t]--;
			if (!deg[t]) que[r++] = t;
		}
	}
	void getDp(const char s[], int val[], int A, int B, long long dp[]) {
		clear();
		int n = strlen(s);
		repo (i, 0, n) extend(s[i], i);
		initMiPos();

		static int que[MAXN];
		int l = 0, r = 0, now = 0;
		rep (i, 1, n) {
			int c = s[i - 1] - 'a';
			now = trans[now][c];
			
			while (now && mip[now] + 1 > i - (mxlen[fa[now]] + 1)) now = fa[now];
			int mxp = max(mip[now] + 1, i - mxlen[now]);
			
			while (l != r && que[l] < mxp) l++;
			dp[i] = dp[i - 1] + val[c];
			if (l != r) dp[i] = min(dp[i], dp[que[l]] + 1ll * (i - que[l]) * A + 2ll * B);
			while (l != r && dp[que[r - 1]] - 1ll * A * que[r - 1] >= dp[i] - 1ll * A * i) r--;
			que[r++] = i;
		}
	}
} sam;

char s[MAXN];
int val[30], A, B;
long long dp[MAXN];

void Solve() {
	scanf("%s", s);
	int n = strlen(s);
	repo (i, 0, 26) scanf("%d", &val[i]);
	scanf("%d %d", &A, &B);
	sam.getDp(s, val, A, B, dp);
	static int cas = 0;
	printf("Case #%d: %lld\n", ++cas, dp[n]);
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
