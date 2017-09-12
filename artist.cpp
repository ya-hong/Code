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

const int MAXN=500005;

int n;
double A[MAXN],B[MAXN];
double T;

struct Main {
	double SA[MAXN],SB[MAXN];
	double calc(double a,double b) {
		return T*(b/(a+b))*a;
	}
	double getMid(double lA,double lB,double rA,double rB) {
		double P1=lA+lB,P2=rA+rB,s=lB+rB;
		if (P1==0&&P2==0) return 0;
		if (P1==0) return calc(rA,rB);
		if (P2==0) return calc(lA,lB);
		double S=T*s;
		double l=0,r=T; 
		l=max(l,(S-T*P2)/P1);
		r=min(r,S/P1);
		return min(lA*l+rA*(S-l*P1)/P2 , lA*r+rA*(S-r*P1)/P2);
	}
	void main() {
		SA[0]=SB[0]=0;
		rep (i,1,n) SA[i]=SA[i-1]+A[i];
		rep (i,1,n) SB[i]=SB[i-1]+B[i];
		double res=1.0/0.0;
		rep (k,1,n) {
			int lA,lB,rA,rB;
			lA=SA[k],lB=SB[k];
			rA=SA[n]-SA[k],rB=SB[n]-SB[k];
			res=min(res,getMid(lA,lB,rA,rB));
		}
		printf("%.2f\n",res);
	}
} pmain;

void Read() {
	scanf("%d",&n);
	rep (i,1,n) scanf("%lf%lf",&A[i],&B[i]);
	scanf("%lf",&T);
}
void Solve() {
	pmain.main();
}
int main() {
//	freopen("artist.in","r",stdin);
//	freopen("artist.out","w",stdout);
	Read();
	Solve();
	
//	cerr<<"\n\n-------------------------------------"<<endl;
//	int sum=
//		+sizeof(Main)
//	;	
//	int std=512;
//	cerr<<(sum>>20)<<" MB"<<endl;
//	cerr<<std<<" -std"<<endl;
//	assert((sum>>20)<std); 
	return 0;
}
