#include <bits/stdc++.h>
using namespace std;

#define rep(i,s,t) for(int i=s,i##end=t;i<=i##end;++i)
#define per(i,s,t) for(int i=t,i##end=s;i>=i##end;--i)
#define repo(i,s,t) for(int i=s,i##end=t;i<i##end;++i)
#define debug(x) cerr<<#x<<" : "<<x<<" "<<__FUNCTION__<<__LINE__<<endl

const int MOD = 1e9 + 7;
const int MAXN = 1000005;

void addp(int &x, int y) {
	x += y;
	if (x >= MOD) x -= MOD;
}

struct SAM {
	static const int MAXN = 1000005 * 2;
	int fa[MAXN], trans[MAXN][15], mxlen[MAXN], milen[MAXN];
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
			if (mxlen[p] + 1 == mxlen[q]) fa[x] = q, milen[x] = mxlen[fa[x]] + 1;
			else {
				int y = newNode();
				fa[y] = fa[q];
				fa[x] = fa[q] = y;
				memcpy(trans[y], trans[q], sizeof(trans[q]));
				mxlen[y] = mxlen[p] + 1;
				milen[y] = mxlen[fa[y]] + 1;
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
		extend(10);// 先添加一个分隔符号
		repo (i, 0, n) extend(s[i] - '0');
	}

	int que[MAXN], res[MAXN], cnt[MAXN], deg[MAXN];
	int query() {
		memset(res, 0, sizeof(res));
		memset(cnt, 0, sizeof(cnt));
		memset(deg, 0, sizeof(deg));
		
		rep (i, 0, alloc) {
			rep (j, 0, 10) if (trans[i][j]) deg[trans[i][j]]++;
		}

		int l = 0, r = 0;
		cnt[0] = 1;
		que[r++] = 0;
		while (l != r) {
			int x = que[l++];
			repo (i, 0, 10) {
				int t = trans[x][i];
				if (!t) continue;
				addp(res[t], (1ll * res[x] * 10 + 1ll * cnt[x] * i) % MOD);
				cnt[t] += cnt[x];
				deg[t]--;
				if (!deg[t]) que[r++] = t;
			}
			if (trans[x][10]) {
				int t = trans[x][10];
				deg[t]--;
				if (!deg[t]) que[r++] = t;
			}
		}

		int ans = 0;
		rep (i, 1, alloc) addp(ans, res[i]);
		return ans;
	}
} sam;

char tmp[MAXN];

int main() {
	int n;
	cin >> n;
	rep (i, 1, n) {
		scanf("%s", tmp);
		sam.insert(tmp);
	}
	cout << sam.query() << endl;
	return 0;
}
