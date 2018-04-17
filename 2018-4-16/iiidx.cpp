#include <bits/stdc++.h>

using namespace std;

#define rep(i, s, t) for(int i = s, i##end = t; i <= i##end; ++i)
#define repo(i, s, t) for(int i = s, i##end = t; i < i##end; ++i)
#define per(i, s, t) for(int i = t, i##end = s; i >= i##end; --i)
#define debug(x) cerr << #x << " : " << x << " " << __FUNCTION__ << __LINE__ << endl;

const int MAXN = 500005 * 2;

int n;
double k;
vector <int> g[MAXN];
int d[MAXN], cnt[MAXN], sz[MAXN];
int res[MAXN];

struct segTree {
#define ls (p << 1)
#define rs (p << 1 | 1)
	int sum[MAXN << 2];
	void insert(int x, int v, int L = 1, int R = MAXN - 1, int p = 1) {
		if (L == R) {
			sum[p] += v;
			return;
		}
		int mid = (L + R) >> 1;
		if (x <= mid) insert(x, v, L, mid, ls);
		else insert(x, v, mid + 1, R, rs);
		sum[p] = sum[ls] + sum[rs];
	}
	int query(int x, int L = 1, int R = MAXN - 1, int p = 1) {
		if (L == R) return L;
		int mid = (L + R) >> 1;
		if (sum[rs] >= x) return query(x, mid + 1, R, rs);
		else return query(x - sum[rs], L, mid, ls);
	}
#undef ls
#undef rs
} tr;

void clear() {
	repo (i, 0, MAXN) {
		g[i].clear();
		d[i] = cnt[i] = sz[i] = res[i] = 0;
	}
	memset(tr.sum, 0, sizeof(tr.sum));
}

int main() {
	clear();
	scanf("%d %lf", &n, &k);
	rep (i, 1, n) scanf("%d", &d[i]);
	sort(d + 1, d + 1 + n);

	d[n + 1] = -1;
	per (i, 1, n) {
		if (d[i] == d[i + 1]) cnt[i] = cnt[i + 1] + 1;
		else cnt[i] = 1;
	}

	per (i, 1, n) {
		sz[i]++;
		int p = i / k;
		sz[p] += sz[i];
		g[p].push_back(i);
	}

	repo (i, 0, g[0].size()) {
		int t = g[0][i];
		tr.insert(t, sz[t]);
	}
	rep (i, 1, n) {
		int w = tr.query(cnt[i]);
		res[w] = d[i];
		tr.insert(w, -sz[w]);
		repo (i, 0, g[w].size()) {
			int t = g[w][i];
			tr.insert(t, sz[t]);
		}
	}

	rep (i, 1, n) printf("%d ", res[i]);
	puts("");
	return 0;
}
