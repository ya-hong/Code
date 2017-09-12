#include <bits/stdc++.h>
using namespace std;
#define db double
const int M=5e5+5;
db suma[M],sumb[M];
db T,ans=1e18;
db a[M],b[M];
int n,tot;
void chk(db &x,db y){
    if(x>y)x=y;
}
bool ep(db x){
    return x<=1e-6;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        db x,y;
        scanf("%lf %lf",&x,&y);
        if(ep(x)&&ep(y))continue;
        ++tot;
        a[tot]=x;
        b[tot]=y;
        suma[tot]=suma[tot-1]+a[tot];
        sumb[tot]=sumb[tot-1]+b[tot];
    }
    n=tot;
    scanf("%lf",&T);
    for(int i=0;i<=n;i++){
        db p,q;
        db A=suma[i];
        db B=suma[n]-A;
        db C=sumb[i];
        db D=sumb[n]-C;
        db TOT=T*(C+D);
        if(ep(A+C)||ep(B+D))continue;
        
        double l,r;
        l=max(0.0,(TOT-T*(B+D))/(A+C));
        r=min(T,TOT/(A+C));
        chk(ans,A*l+B*(TOT-(A+C)*l)/(B+D));
        chk(ans,A*r+B*(TOT-(A+C)*r)/(B+D));

 //       if(B*C<A*D){
 //           q=min(T,TOT/(B+D));//可行域的最大值 
 //           p=(TOT-(B+D)*q)/(A+C);
 //       }else{
 //           q=max(0.0,(TOT-T*(A+C))/(B+D));//可行域的最小值 
 //          p=(TOT-(B+D)*q)/(A+C);
 //       }
 //     if(p>=0&&p<=T)chk(ans,A*p+B*q);
 //      
 //     if(B*C>A*D){
 //         p=min(T,TOT/(A+C));
 //         q=(TOT-(A+C)*p)/(B+D);
 //     }else{
 //         p=max(0.0,(TOT-T*(B+D))/(A+C));
 //         q=(TOT-(A+C)*p)/(B+D);
 //     }
 //     if(q>=0&&q<=T)chk(ans,A*p+B*q);
    }
    if(ans==1e18)printf("0.00\n");
    else printf("%.2lf\n",ans);
    return 0;
}
