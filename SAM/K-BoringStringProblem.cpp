#include <bits/stdc++.h>
using namespace std;

#define rep(i,s,t) for(int i=s,i##end=t;i<=i##end;++i)
#define per(i,s,t) for(int i=t,i##end=s;i>=i##end;--i)
#define repo(i,s,t) for(int i=s,i##end=t;i<i##end;++i)
#define debug(x) cerr<<#x<<" : "<<x<<" "<<__FUNCTION__<<__LINE__<<endl

const int MAXN = 1e5 + 5;

struct SAM {
	static const int MAXN = ::MAXN * 2, MAXC = 30, C = 26;
	int trans[MAXN][MAXC], fa[MAXN], mxlen[MAXN], mipos[MAXN];
	long long sum[MAXN];
	int alloc, lst;
	int newNode() {
		int x = alloc++;
		memset(trans[x], 0, sizeof(trans[x]));
		fa[x] = -1;
		mxlen[x] = 0;
		mipos[x] = MAXN + 1;
		return x;
	}
	void clear() {
		alloc = 0;
		lst = newNode();
	}
	void extend(int c, int ID) {
		c -= 'a';
		int x = newNode(), p = lst;
		lst = x;
		mxlen[x] = mxlen[p] + 1;
		mipos[x] = ID;
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
	void initSum() {
		static int deg[MAXN], que[MAXN];
		vector <int> g[MAXN];
		repo (i, 0, MAXN) g[i].clear();
		memset(deg, 0, sizeof(deg));

		int l = 0, r = 0;
		sum[0] = 0;
		repo (i, 1, alloc) sum[i] = 1;
		repo (i, 0, alloc) repo (j, 0, C) if (trans[i][j]) {
			deg[i]++;
			g[trans[i][j]].push_back(i);
		}
		repo (i, 0, alloc) if (!deg[i]) que[r++] = i;
		while (l != r) {
			int x = que[l++];
			repo (i, 0, g[x].size()) {
				int t = g[x][i];
				sum[t] += sum[x];
				deg[t]--;
				if (!deg[t]) que[r++] = t;
			}
		}
	}
	void initmiPos() {
		static int deg[MAXN], que[MAXN];
		memset(deg, 0, sizeof(deg));

		int l = 0, r = 0;
		repo (i, 1, alloc) deg[fa[i]]++;
		repo (i, 0, alloc) if (!deg[i]) que[r++] = i;
		while (l != r) {
			int x = que[l++];
			if (!x) continue;
			int t = fa[x];
			mipos[t] = min(mipos[t], mipos[x]);
			deg[t]--;
			if (!deg[t]) que[r++] = t;
		}
	}
	void build(const char s[], int n) {
		clear();
		rep (i, 1, n) extend(s[i], i);
		initSum();
		initmiPos();
	}
	void query(long long k, int &l, int &r) {
		if (sum[0] < k) {
			l = r = 0;
			return;
		}
		int now = 0, len = 0;
		while (k) {
			repo (i, 0, C) {
				int t = trans[now][i];
				if (!t) continue;
				if (k > sum[t]) k -= sum[t];
				else {
					k--;
					now = t;
					len++;
					break;
				}
			}
		}
		r = mipos[now];
		l = mipos[now] - len + 1;
//		while (!(r > 0 && l > 0));
	}
} sam;

char s[MAXN];

void Solve() {
	sam.build(s, strlen(s + 1));
	int l = 0, r = 0, q;
	long long v;
	scanf("%d", &q);
	rep (i, 1, q) {
		scanf("%lld", &v);
		long long k = (l ^ r ^ v) + 1;
		sam.query(k, l, r);
		printf("%d %d\n", l, r);
	}
}

int main() {
	while (scanf("%s", s + 1) != EOF) Solve();
	return 0;
}

/*
aba
1
2


*/
