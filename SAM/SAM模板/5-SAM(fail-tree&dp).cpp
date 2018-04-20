#include <bits/stdc++.h>
using namespace std;

#define rep(i,s,t) for(int i=s,i##end=t;i<=i##end;++i)
#define per(i,s,t) for(int i=t,i##end=s;i>=i##end;--i)
#define repo(i,s,t) for(int i=s,i##end=t;i<i##end;++i)
#define debug(x) cerr<<#x<<" : "<<x<<" "<<__FUNCTION__<<__LINE__<<endl

const int MAXN = 1e5 + 5;

struct SAM {
	static const int MAXN = (1e5 + 5) * 2, MAXC = 30, C = 26;
	int fa[MAXN], trans[MAXN][MAXC], mxlen[MAXN];
	vector <int> g[MAXN];
	int alloc, lst;

	int newNode() {
		int p = ++alloc;
		fa[p] = -1;
		memset(trans[p], 0, sizeof(trans[p]));
		mxlen[p] = 0;
		return p;
	}
	void clear() {
		alloc = -1;
		lst = newNode();
		memset(cnt, 0, sizeof(cnt));
		memset(sum, 0, sizeof(sum));
		memset(sg, 0, sizeof(sg));
		memset(deg, 0, sizeof(deg));
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
		if (p == -1) fa[x] = 0;
		else {
			int q = trans[p][c];
			if (mxlen[p] + 1 == mxlen[q]) fa[x] = q;
			else {
				int y = newNode();
				fa[y] = fa[q];
				fa[x] = fa[q] = y;
				memcpy(trans[y], trans[q], sizeof(trans[q]));
				mxlen[y] = mxlen[p] + 1;
				while (trans[p][c] == q) {
					trans[p][c] = y;
					p = fa[p];
				}
			}
		}
	}

	long long cnt[MAXN][30], sum[MAXN];
	int sg[MAXN], deg[MAXN];
	
	void build(const char s[]) {
		int n = strlen(s);
		repo (i, 0, n) extend(s[i]);

		static int que[MAXN];
		int l = 0, r = 0;
		rep (i, 0, alloc) repo (j, 0, C) if (trans[i][j]) {
			deg[i]++;
			g[trans[i][j]].push_back(i);
		}
		rep (i, 0, alloc) if (!deg[i]) que[r++] = i;
		while (l != r) {
			int x = que[l++];
			
			static bool mark[MAXC];// calc
			memset(mark, 0, sizeof(mark));
			repo (i, 0, C) if (trans[x][i]) {
				int t = trans[x][i];
				mark[sg[t]] = true;
				repo (j, 0, C) cnt[x][j] += cnt[t][j];
			}
			sg[x] = 0;
			while (mark[sg[x]]) sg[x]++;
			cnt[x][sg[x]]++;
			assert(sg[x] < C);

			repo (i, 0, g[x].size()) {
				int t = g[x][i];
				deg[t]--;
				if (!deg[t]) que[r++] = t;
			}
		}
		rep (i, 0, alloc) repo (j, 0, C) sum[i] += cnt[i][j];
	}

	string query1(long long &k, long long Bcnt[], long long Bsum, int &sgA) {
		string res;
		int now = 0;
		while (true) {
			if (Bsum - Bcnt[sg[now]] >= k) break;
			k -= Bsum - Bcnt[sg[now]];
			repo (c, 0, C) {
				int t = trans[now][c];
				if (!t) continue;
				long long s = 0;
				repo (i, 0, C) s += cnt[t][i] * (Bsum - Bcnt[i]);
				if (k > s) k -= s;
				else {
					res += c + 'a';
					now = t;
					break;
				}
			}
		}
		sgA = sg[now];
		return res;
	}
	string query2(long long &k, int sgA) {
		string res;
		int now = 0;
		while (true) {
			k -= sg[now] != sgA;
			if (k == 0) break;
			repo (c, 0, C) {
				int t = trans[now][c];
				if (!t) continue;
				long long s = sum[t] - cnt[t][sgA];
				if (k > s) k -= s;
				else {
					res += c + 'a';
					now = t;
					break;
				}
			}
		}
		return res;
	}
} samA, samB;

long long k;
char A[MAXN], B[MAXN];

void Spj() {
	long long res = 0;
	repo (i, 0, 26) {
		res += samA.cnt[0][i] * (samB.sum[0] - samB.cnt[0][i]);
		if (res >= k) break;
	}
	if (res < k) {
		puts("NO");
		exit(0);
	}
}

int main() {
	scanf("%lld %s %s", &k, A, B);
	samA.build(A);
	samB.build(B);
	Spj();
	int pre;
	cout << samA.query1(k, samB.cnt[0], samB.sum[0], pre) << endl;
	cout << samB.query2(k, pre) << endl;
	return 0;
}
