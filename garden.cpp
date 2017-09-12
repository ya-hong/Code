#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

using namespace std;

#define rep(i,s,t) for(int i=s,i##end=t;i<=i##end;++i)
#define per(i,s,t) for(int i=t,i##end=s;i>=i##end;--i)
#define repo(i,s,t) for(int i=s,i##end=t;i<i##end;++i)

void getc(char &c) {
//	c=getchar();
//	return;
	static char buf[50000],*p1=buf,*p2=buf;
	if (p1==p2) p2=(p1=buf)+fread(buf,1,50000,stdin);
	c=*p1++;
}
void Rd(int &x) {
	char c;
	x=0;
	while (getc(c),!isdigit(c));
	do x=(x<<1)+(x<<3)+(c^48);
	while (getc(c),isdigit(c));
}

struct edge {
	int x,y,v;
	bool operator < (const edge &t) const {
		return v<t.v;
	}
};
struct node {
	int t,v;
};

const int MAXN=100005;
const int MAXE=300005;
const int MAXQ=100005;

int n,m,TYPE;
int col[MAXN];
edge edg[MAXE];
int q;

struct BFRC {
	static const int MAXN=1005;
	struct disJointSet {
		int fa[MAXN];
		disJointSet() {
			repo (i,0,MAXN) fa[i]=i;
		}
		int find(int x) {
			return fa[x]==x?x:fa[x]=find(fa[x]);
		}
		bool merge(int x,int y) {
			x=find(x),y=find(y);//find 
			if (x==y) return false;
			fa[x]=y;
			return true;
		}
	} S;
	vector <node> g[MAXN];
	bool mark[MAXN];
	int cnt[MAXN];
	
	void dfs(int x,int w) {
		if (mark[x]) return;
		mark[x]=true;
		cnt[col[x]]++;
		repo (i,0,g[x].size()) if (g[x][i].v<=w) dfs(g[x][i].t,w);
	}
	
	void main() {
		sort(edg+1,edg+1+m);
		rep (i,1,m) {
			int x=edg[i].x,y=edg[i].y;
			if (S.merge(x,y)) {
				g[x].push_back((node){y,edg[i].v});
				g[y].push_back((node){x,edg[i].v});
			}
		}
		
		int lastans=0;
		rep (i,1,q) {
			int x,w;
			Rd(x),Rd(w);
			x^=lastans,w^=lastans;
			memset(mark,0,sizeof(mark));
			memset(cnt,0,sizeof(cnt));
			dfs(x,w);
			int res=1;
			rep (i,1,n) {
				if (cnt[i]>cnt[res]) res=i;
			}
			printf("%d\n",res);
			lastans=res;
		}
	}
} p40;

struct OffLine {
	struct disJointSet {
		int fa[MAXN];
		map <int,int> cnt[MAXN];
		int res[MAXN];
		void init(){
			repo (i,0,MAXN) fa[i]=i;
			repo (i,0,MAXN) cnt[i][col[i]]++,res[i]=col[i];
		}
		int find(int x) {
			return fa[x]==x?x:fa[x]=find(fa[x]);
		}
		bool merge(int x,int y) {
			x=find(x),y=find(y);//find 
			if (x==y) return false;
			if (cnt[x].size()>cnt[y].size()) swap(x,y);
			int mx=cnt[y][res[y]];
			for (map <int,int> :: iterator it=cnt[x].begin();it!=cnt[x].end();++it) {
				int a=it->first,b=it->second;
				cnt[y][a]+=b;
				int now=cnt[y][a];
				if (mx<now||(mx==now&&a<res[y])) mx=now,res[y]=a;
			}
			fa[x]=y;
			return true;
		}
		int query(int x) {
			x=find(x);
			return res[x];
		}
	} S;
	struct query {
		int x,w,id;
		bool operator < (const query &t) const {
			return w<t.w;
		}
	} que[MAXQ];
	int res[MAXQ];
	void main() {
		S.init();
		rep (i,1,q) Rd(que[i].x),Rd(que[i].w),que[i].id=i;
		sort(que+1,que+1+q);
		sort(edg+1,edg+1+m);
		int eid=1;
		rep (i,1,q) {
			int x=que[i].x,w=que[i].w;
			while (eid<=m&&edg[eid].v<=w) {
				S.merge(edg[eid].x,edg[eid].y);
				eid++;
			}
			res[que[i].id]=S.query(x);
		}
		rep (i,1,q) printf("%d\n",res[i]);
	}
} p70;

/*
5 6 0
2 1 1 3 2
1 2 2
1 3 4
2 3 7
3 4 5
4 5 6
5 3 3
4
1 1
2 2
4 4
5 8
*/

void Read() {
//	scanf("%d%d%d",&n,&m,&TYPE);
//	rep (i,1,n) scanf("%d",&col[i]);
//	rep (i,1,m) scanf("%d%d%d",&edg[i].x,&edg[i].y,&edg[i].v);
//	scanf("%d",&q);
	
	Rd(n),Rd(m),Rd(TYPE);
	rep (i,1,n) Rd(col[i]);
	rep (i,1,m) Rd(edg[i].x),Rd(edg[i].y),Rd(edg[i].v);
	Rd(q);
}
void Solve() {
	if (0);
	else if (TYPE==1) {
		p40.main();
	}
	else {
		p70.main();
	}
}

int main() {
//	freopen("garden.in","r",stdin);
//	freopen("garden.out","w",stdout);
	Read();
	Solve();
	
//	cerr<<"\n\n-------------------------------------"<<endl;
//	int sum=
//		+sizeof(BFRC)
//		+sizeof(OffLine);
//	;	
//	int std=512;
//	cerr<<(sum>>20)<<" MB"<<endl;
//	cerr<<std<<" -std"<<endl;
//	assert((sum>>20)<std); 
	return 0;
}
