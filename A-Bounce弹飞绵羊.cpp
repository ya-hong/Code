#include <bits/stdc++.h>
using namespace std;

#define rep(i,s,t) for(int i=s,i##end=t;i<=i##end;++i)
#define per(i,s,t) for(int i=t,i##end=s;i>=i##end;--i)
#define repo(i,s,t) for(int i=s,i##end=t;i<i##end;++i)
#define debug(x) cerr<<#x<<" : "<<x<<" "<<__FUNCTION__<<__LINE__<<endl

const int MAXN=200005;

struct LinkCutTree {
	int ch[MAXN][2], fa[MAXN];
	int cnt[MAXN];
	bool isRoot(int x) {
		return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
	}
	void up(int x) {
		cnt[x]=cnt[ch[x][0]]+cnt[ch[x][1]]+1;
	}
	void Rotate(int x) {
		int y=fa[x],z=fa[y];
		if (!isRoot(y)) ch[z][ch[z][1] == y] = x;
		bool f = ch[y][1] == x;
		fa[x] = z;
		fa[y] = x;
		fa[ch[x][!f]] = y;
		ch[y][f] = ch[x][!f];
		ch[x][!f] = y;
		up(y);
	}
	void Splay(int x) {
		if (!x) return;
		while (!isRoot(x)) {
			int y = fa[x];
			if (isRoot(y)) Rotate(x);
			else {
				int z = fa[y];
				if ((ch[z][0] == y) ^ (ch[y][0] == x)) Rotate(x);
				else Rotate(y);
				Rotate(x);
			}
		}
		up(x);
	}
	void Access(int x) {
		int p = 0;
		while (x) {
			Splay(x);
			ch[x][1] = p;
			up(x);
			p = x;
			x = fa[x];
		}
	}
	void cut(int x) {
		Access(x);
		Splay(x);
		fa[ch[x][0]] = 0;
		ch[x][0] = 0;
		up(x);
	}
//	int mxid;
	void link(int x,int y) {
//		mxid=max(mxid,x);
//		mxid=max(mxid,y);
		
		Access(x);
		Splay(x);
		Access(y);
		Splay(y);
		fa[x] = y;
	}
	int query(int x) {
		Access(x);
		Splay(x);
		return cnt[ch[x][0]]+1;
	}
//	void print() {
//		rep (i,1,mxid) {
//			cerr<<query(i)<<" ";
//		}
//		puts("");
//	}
} tree;

int n,m;

int main() {
	cin>>n;
	rep (i,1,n) {
		int k;
		scanf("%d",&k);
		if (i+k>n) tree.link(i,0);
		else tree.link(i,i+k);
	}
//	tree.print();
//	puts("------------");
	cin>>m;
	rep (i,1,m) {
		int t,j,k;
		scanf("%d%d",&t,&j);
		j++;
		if (t==1) printf("%d\n",tree.query(j));
		else {
			scanf("%d",&k);
			tree.cut(j);
			if (j+k>n) tree.link(j,0);
			else tree.link(j,j+k);
		}
	}
	
	return 0;
}
