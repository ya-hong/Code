#include <bits/stdc++.h>

using namespace std;

#define rep(i, s, t) for(int i = s, i##end = t; i <= i##end; ++i)
#define repo(i, s, t) for(int i = s, i##end = t; i < i##end; ++i)
#define per(i, s, t) for(int i = t, i##end = s; i >= i##end; --i)
#define debug(x) cerr << #x << " : " << x << " " << __FUNCTION__ << __LINE__ << endl;

const int MAXN = 1705;
const int MOD = 64123;

inline void addp(int &x, int y) {
	x += y;
	if (x >= MOD) x -= MOD;
}

int n, k, W;
int d[MAXN];
vector <int> g[MAXN];

struct Part1 {
	bool mark[MAXN];
	void dfs(int x, int S) {
		mark[x] = true;
		repo (i, 0, g[x].size()) {
			int t = g[x][i];
			if (!mark[t] && (S >> (t - 1) & 1)) {
				dfs(t, S);
			}
		}
	}
	bool chk(int S) {
		memset(mark, 0, sizeof(mark));
		rep (i, 1, n) {
			if (S >> (i - 1) & 1) {
				dfs(i, S);
				break;
			}
		}
		rep (i, 1, n) {
			if ((S >> (i - 1) & 1) && !mark[i]) {
				return false;
			}
		}
		return true;
	}

	int calc(int S) {
		static int arr[MAXN], tot;
		tot = 0;
		rep (i, 1, n) if (S >> (i - 1) & 1) {
			arr[++tot] = d[i];
		}
		if (tot < k) return 0;
		else {
			sort(arr + 1, arr + 1 + tot, greater<int>());
			return arr[k];
		}
	}

	void main() {
		int res = 0;
		repo (S, 0, 1 << n) {
			if (chk(S)) addp(res, calc(S));
		}
		printf("%d\n", res);
	}
} part1;

struct Part2 {// Á´ 

	int arr[MAXN], tot;
	void dfs(int x, int fa) {
		arr[++tot] = d[x];
		repo (i, 0, g[x].size()) {
			int t = g[x][i];
			if (t != fa) dfs(t, x);
		}
	}
	
	void main() {
		rep (i, 1, n) {
			if (g[i].size() == 1) {
				dfs(i, i);
				break;
			}
		}
		priority_queue <int, vector <int>, greater <int> > que;
		int res = 0;
		rep (i, 1, n - k + 1) {
			while (!que.empty()) que.pop();
			rep (j, i, i + k - 1) que.push(arr[j]);
			addp(res, que.top());
			rep (j, i + k, n) {
				que.push(arr[j]);
				que.pop();
				addp(res, que.top());
			}
		}
		printf("%d\n", res);
	}
} part2;

struct Part3 {
	static const int MAXK = 505;

	int dp[MAXN][MAXK];
	int len[MAXN];

	void rec(int x, int fa, int s) {
		repo (i, 0, g[x].size()) if (g[x][i] != fa) rec(g[x][i], x, s);

		int *A, *B;
		static int tmp[MAXK];

		A = dp[x];
		
		if (d[x] > d[s] || (d[x] == d[s] && x > s)) {
			A[1] = 1;
			len[x] = 1;
		}
		else A[0] = 1, len[x] = 0;
		
		repo (i, 0, g[x].size()) {
			int t = g[x][i];
			if (t == fa) continue;
			B = dp[t];
			rep (p, 0, len[x]) rep (q, 0, min(k - 1 - p, len[t])) {
				tmp[p + q] = (tmp[p + q] + 1ll * A[p] * B[q]) % MOD;
			}
			len[x] = min(len[x] + len[t], k - 1);
			rep (i, 0, len[x]) A[i] = tmp[i], tmp[i] = 0;
		}
		addp(A[0], 1);

//		cerr << "-> " << x << endl;
//		rep (i, 0, k - 1) cerr << dp[x][i] << " ";
//		cerr << endl;
	}

	void main() {
		int res = 0;
		rep (i, 1, n) {
			memset(dp, 0, sizeof(dp));
			rec(i, i, i);
			addp(res, 1ll * d[i] * dp[i][k - 1] % MOD);
		}
		printf("%d\n", res);
	}
} part3;

bool judge1() {
	return n <= 20;
}
bool judge2() {
	int cnt = 0;
	rep (i, 1, n) if (g[i].size() == 1) cnt++;
	return cnt == 2;
}

void Read() {
	scanf("%d %d %d", &n, &k, &W);
	rep (i, 1, n) scanf("%d", &d[i]);
	rep (i, 1, n - 1) {
		int x, y;
		scanf("%d %d", &x, &y);
		g[x].push_back(y);
		g[y].push_back(x);
	}
}
void Solve() {
	if (0);
	else if (judge1()) {
		part1.main();
	}
	else if (judge2()) {
		part2.main();
	}
	else {
		part3.main();
	}
}

int main() {
	Read();
	Solve();
	return 0;
}

/*
5 2 5
1 3 2 1 5
1 2
2 3
3 4
4 5

*/
