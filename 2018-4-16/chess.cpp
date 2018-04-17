#include <bits/stdc++.h>

using namespace std;

#define rep(i, s, t) for(int i = s, i##end = t; i <= i##end; ++i)
#define repo(i, s, t) for(int i = s, i##end = t; i < i##end; ++i)
#define per(i, s, t) for(int i = t, i##end = s; i >= i##end; --i)
#define debug(x) cerr << #x << " : " << x << " " << __FUNCTION__ << __LINE__ << endl;

const int MAXN = 15;
const int INF = 1e9 + 5;

int n, m;
int A[2][MAXN][MAXN];

struct Part1 {
	struct HashTable {
		static const int MAXN = 400007;
		pair <vector <int>, int> A[MAXN];
		int head[MAXN], nxt[MAXN];
		int tot;
		void clear() {
			tot = 0;
			memset(head, 0, sizeof(head));
			memset(nxt, 0, sizeof(nxt));
		}
		bool find(const vector <int> &V) const {
			int k = 0;
			repo (i, 0, V.size()) k = (k * 10 + V[i]) % MAXN;
			for (int i = head[k]; i; i = nxt[i]) {
				if (A[i].first == V) return true;
			}
			return false;
		}
		int& operator [] (const vector <int> &V) {
			int k = 0;
			repo (i, 0, V.size()) k = (k * 10 + V[i]) % MAXN;
			for (int i = head[k]; i; i = nxt[i]) {
				if (A[i].first == V) return A[i].second;
			}
			tot++;
			nxt[tot] = head[k];
			head[k] = tot;
			A[tot].first = V;
			return A[tot].second;
		}
	} dp;
	int dfs(vector <int> l, bool op) {
		if (dp.find(l)) return dp[l];
		int &res = dp[l] = -INF;
		bool ed = true;
		repo (i, 0, n) if (l[i] != m) {
			ed = false;
			bool f = i == 0 ? true : l[i] < l[i - 1];
			if (!f) continue;
			l[i]++;
			res = max(res, A[op][i + 1][l[i]] - dfs(l, !op));
			l[i]--;
		}
		if (ed) res = 0;
		return res;
	}
	void main() {
		dp.clear();
		vector <int> now(n);
		printf("%d\n", dfs(now, 0));
	}
} part1;

void Read() {
	scanf("%d %d", &n, &m);
	rep (i, 1, n) rep (j, 1, m) scanf("%d", &A[0][i][j]);
	rep (i, 1, n) rep (j, 1, m) scanf("%d", &A[1][i][j]);
}
void Solve() {
	part1.main();
}

int main() {
	Read();
	Solve();
	return 0;
}
