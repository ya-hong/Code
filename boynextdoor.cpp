#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

#define rep(i,s,t) for(int i=s,i##end=t;i<=i##end;++i)
#define per(i,s,t) for(int i=t,i##end=s;i>=i##end;--i)
#define repo(i,s,t) for(int i=s,i##end=t;i<i##end;++i)

void Max(int &x,int y) {
	if (x<y) x=y;
}
const int INF=1<<28;

const int MAXT=100005;
const int MAXN=100005;

int T,A[MAXT],B[MAXT];

int GETANS(int x,int y) {
	int res=0;
	if (x<=y) {
		x--;
		swap(x,y);
		res=-(x-y+1);
	}
	else {
		res=x-y-2;
	}
	return res;
}

struct Dp {
	/*
	dp[i][j][v] , n^3 x T  
	*/
	Dp() {
		repo (i,0,MAXN) repo (j,0,MAXN) repo (v,0,MAXN+MAXN) dp[i][j][v]=-INF;
	}
	static const int MAXN=105;
	
	int dp[MAXN][MAXN][MAXN+MAXN];
	int rec(int x,int y,int v) {
		if (!x) return -y-v;
		if (!y) return x+v;
		if (dp[x][y][v]!=-INF) return dp[x][y][v];
		
		int &res=dp[x][y][v]=-INF;
		
//		////////////////////
//		if (v) {
//			int A=-rec(y,x,0)-v,B=-rec(y,x-1,v+1);
//			if (x<y) assert(A>=B);
//			if (x==y&&v) assert(A>=B);
//			if (x>y) {
//				assert(A==x-y+2-v);
//				assert(B==x+v-y-2);
////				cerr<<x<<" "<<y<<" "<<v<<" -> "<<B<<endl;
//			}
//		}
//		////////////////////
		
		if (v) Max(res,-rec(y,x,0)-v);
		Max(res,-rec(y,x-1,v+1));
		
		return res;
	}
	void main() {
 		rep (i,1,T) printf("%d\n",rec(A[i],B[i],0));
	}
} p50;

struct P100 {
	void main() {
		rep (i,1,T) {
			int x=A[i],y=B[i];
			int res=0;
			if (x<=y) {
				x--;
				swap(x,y);
				res=-(x-y+1);
			}
			else {
				res=x-y-2;
			}
			printf("%d\n",res);
		}
	}
} pmain;

void Read() {
	scanf("%d",&T);
	rep (i,1,T) scanf("%d%d",&A[i],&B[i]);
}
void Solve() {
	int mxA=0,mxB=0;
	rep (i,1,T) Max(mxA,A[i]),Max(mxB,B[i]);
	if (0);
	else if (T<=10&&mxA<=100&&mxB<=100) {
		p50.main();
	}
	else {
		pmain.main();
	}
}
int main() {
//	freopen("boynextdoor.in","r",stdin);
//	freopen("boynextdoor.out","w",stdout);
	Read();
	Solve();
	
//	{
//		cerr<<"\n\n-------------------------------------"<<endl;
//		int sum=
//			+sizeof(Dp)
//			+sizeof(P100)
//		;
//		int std=512;
//		cerr<<(sum>>20)<<" MB"<<endl;
//		cerr<<std<<" -std"<<endl;
//		assert((sum>>20)<std); 
//	}
	return 0;
}
