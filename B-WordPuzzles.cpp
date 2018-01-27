#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

#define rep(i,s,t) for(int i=s,i##end=t;i<=i##end;++i)
#define per(i,s,t) for(int i=t,i##end=s;i>=i##end;--i)
#define repo(i,s,t) for(int i=s,i##end=t;i<i##end;++i)
#define debug(x) cerr<<#x<<" : "<<x<<" "<<__FUNCTION__<<__LINE__<<endl

const int MAXN=1005;
const int rx[]={-1,-1, 0, 1, 1, 1, 0,-1};
const int ry[]={ 0, 1, 1, 1, 0,-1,-1,-1};


struct AC {
	static const int MAXN=1005*1005;
	int trie[MAXN][30],dep[MAXN],fail[MAXN];
	int ansx[MAXN],ansy[MAXN],ansf[MAXN];
	int tot;
	AC() {
		memset(this,0,sizeof(*this));
		repo (i,0,MAXN) ansx[i]=MAXN;
		dep[0]=-1;
	}
	void check(int &x,int &y,int &f,int tx,int ty,int tf) {
//		cout<<x<<" "<<y<<" "<<f<<" "<<tx<<" "<<ty<<" "<<tf<<endl;
		if (tx<x) x=tx,y=ty,f=tf;
		else if (tx>x) return;
		if (ty<y) x=tx,y=ty,f=tf;
		else if (ty>y) return;
		if (tf<f) x=tx,y=ty,f=tf;
		else if (tf>f) return;
	}
	int insert(char s[]) {
		int len=strlen(s);
		int cur=0;
		int d=0;
		repo (i,0,len) {
			int c=s[i]-'A';
			if (!trie[cur][c]) trie[cur][c]=++tot;
			cur=trie[cur][c];
			dep[cur]=d++;
		}
		return cur;
	}
	void build() {
		static int que[MAXN];
		int l=0,r=0;
		repo (i,0,26) if (trie[0][i]) que[r++]=trie[0][i];
		while (l!=r) {
			int x=que[l++];
			repo (i,0,26) {
				int t=trie[x][i];
				if (t) {
					fail[t]=trie[fail[x]][i];
					que[r++]=t;
				}
				else trie[x][i]=trie[fail[x]][i];
			}
		}
	}
	void query(const char s[],int x,int y,int dx,int dy,int f) {
		int cur=0;
		repo (i,0,strlen(s)) {
			int t=trie[cur][s[i]-'A'];
			cur=t;
			check(ansx[t],ansy[t],ansf[t],x-dep[t]*dx,y-dep[t]*dy,f);
			x+=dx,y+=dy;
		}
	}
	void update(int x=0) {
		repo (i,0,26) {
			int t=trie[x][i];
			if (dep[x]+1==dep[t]) {
				update(t);
				check(ansx[x],ansy[x],ansf[x],ansx[t],ansy[t],ansf[t]);
			}
		}
	}
} ac;

int n,m,q;
char mp[MAXN][MAXN];
char str[MAXN][MAXN];
int ID[MAXN];

bool chk(int x,int y) {
	return x>=0&&x<n&&y>=0&&y<m;	
}

int main() {
	cin>>n>>m>>q;
	repo (i,0,n) scanf("%s",mp[i]);
	repo (i,0,q) {
		scanf("%s",str[i]);
		ID[i]=ac.insert(str[i]);
	}
	ac.build();
	
	repo (i,0,n) {
		repo (j,0,m) {
			if (i!=0&&i!=n-1&&j!=0&&j!=m-1) continue;
			repo (f,0,8) {
				int x=i,y=j,dx=rx[f],dy=ry[f];
				string s="";
				while (chk(x,y)) s+=mp[x][y],x+=dx,y+=dy;
				ac.query(s.c_str(),i,j,dx,dy,f);
			}
		}
	}
	ac.update();
	
	repo (i,0,q) printf("%d %d %c\n",ac.ansx[ID[i]],ac.ansy[ID[i]],ac.ansf[ID[i]]+'A');
	
	return 0;
}


