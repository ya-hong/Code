#include <bits/stdc++.h>
#include <cmath>
using namespace std;
#define rep(i,s,t) for(int i=s,i##end=t;i<=i##end;++i)
#define per(i,s,t) for(int i=t,i##end=s;i>=i##end;--i)
#define repo(i,s,t) for(int i=s,i##end=t;i<i##end;++i)
#define debug(x) cerr<<#x<<" : "<<x<<" "<<__FUNCTION__<<__LINE__<<endl

const double EPS=1e-9;
const double pi=acos(-1);
const double INF=1.0/0.0;

bool eq(double a,double b) {
	return fabs(a-b)<EPS;
}

struct Point {
	double x,y;
	Point() {}
	Point(double _x,double _y) {
		x=_x,y=_y;
	}
	Point operator + (const Point &t) const {return Point(x+t.x,y+t.y);}
	Point operator - (const Point &t) const {return Point(x-t.x,y-t.y);}
	Point operator - () const {return Point(-x,-y);}
	double dot (const Point &t) const {
		return x*t.x+y*t.y;
	}
	double cross (const Point &t) const {
		return x*t.y-y*t.x;
	}
	double len() const {
		return sqrt(x*x+y*y);
	} 
	Point rotate (double a) const {
		return Point(x*cos(a)-y*sin(a),y*cos(a)+x*sin(a));
	}
	double angle() const {
		return atan2(y,x);
	}
};

ostream& operator << (ostream &out,const Point &p) {
	out<<"( "<<p.x<<" , "<<p.y<<" )";
	return out;
}

typedef Point Vector;

struct Line {
	Point p;
	Vector v;
	Line(const Point &_p,const Vector &_v) {
		p=_p,v=_v;
	}
	Line rotate(double a) const {
		return Line(p,v.rotate(a));
	}
	void getStd(double &a,double &b,double &c) const {
		a=v.y,b=-v.x;
		c=-p.x*a-p.y*b;
	}
	double angle() const {
		return atan2(v.y,v.x);
	}
	double dist(const Point &p) const {
		double a,b,c;
		getStd(a,b,c);
		return (a*p.x+b*p.y+c)/sqrt(a*a+b*b);
	}
	double dist2(const Point &p) const {
		double a,b,c;
		getStd(a,b,c);
		
		double P1=(a*p.x+b*p.y+c);
		double P2=a*a+b*b;
		return P1*P1/P2;
	}
};

struct Circle {
	Point c;
	double r;
	Point point(double a) const {
		return c+Point(r*cos(a),r*sin(a));
	}
	double getdist(double a) {
		return r*a;
	}
	void Link(const Point &p,vector <Point>& v) const { //得到两个切点. 
		Line l=Line(c,c-p);
		double d=l.v.len();
		double a=pi-acos(r/d);
		v.push_back(point(l.rotate(a).angle()));
		v.push_back(point(l.rotate(-a).angle()));
		return;
	}
	void Link(const Circle &t,vector <Point> &A,vector <Point> &B) const {//得到两组切点 
		Line l=Line(c,t.c-c);
		double d=l.v.len();
		double dr=t.r-r,sr=t.r+r;
		{//外公切线 
			double a=asin(dr/d)+pi/2;
			double ang=l.angle();
			A.push_back(point(ang+a));
			B.push_back(t.point(ang+a));
			A.push_back(point(ang-a));
			B.push_back(t.point(ang-a));
		}
		{//内公切线 
			double a=asin(sr/d)-pi/2;
			double ang=l.angle();
			A.push_back(point(ang+a));
			B.push_back(t.point(ang+a-pi));
			A.push_back(point(ang-a));
			B.push_back(t.point(ang-a-pi));
		}
		return;
	}
	bool intersect(const Line &l) const {
		double d=l.dist2(c);
		if (r*r-EPS>d) {
			bool chk=true;
			chk&=l.v.dot(c-l.p) > -EPS ;
			Point p=l.p+l.v;
			chk&=(-l.v).dot(c-p) > -EPS ;
			return chk;
		}
		else return false;
	}
};

const int MAXN=505;
const int MAXS=MAXN*MAXN*6;


struct edge {
	int t;
	double d;
	edge(){}
	edge(int _t,double _d) {
		t=_t,d=_d;
	}
};

int n,tot;
Point s,t,A[MAXS];
vector <edge> g[MAXS];

Circle C[MAXN];
vector <int> poc[MAXN];

struct PointCmp {
	Point S;
	bool operator () (const int &a,const int &b) const {
		return (A[a]-S).angle()<(A[b]-S).angle();
	}
};

struct node {
	int x;
	double d;
	node(){}
	node(int _x,double _d){x=_x,d=_d;}
	bool operator < (const node &t) const {
		return d>t.d;
	}
};
double Dijkstra(int s,int t) {
	static double dis[MAXS];
	priority_queue <node> que;
	fill(dis,dis+MAXS,INF);
	
	dis[s]=0;
	que.push(node(s,0));
	while (!que.empty()) {
		node now=que.top();
		que.pop();
		if (now.d-EPS>dis[now.x]) continue;
		int x=now.x;
		repo (i,0,g[x].size()) {
			int t=g[x][i].t;
			if (dis[t]>dis[x]+g[x][i].d) {
				dis[t]=dis[x]+g[x][i].d;
				que.push(node(t,dis[t]));
			}
		}
	}
	return dis[t];
}


void initST(int id,Point x) {
	rep (i,1,n) {
		static vector <Point> now;
		C[i].Link(x,now);
		repo (j,0,now.size()) {
			A[++tot]=now[j];
			poc[i].push_back(tot);
			
			int p=id,q=tot;
			Line l=Line(x,A[q]-x);
			bool chk=true;
			rep (k,1,n) if (C[k].intersect(l)) chk=false;
			if (chk) {
				g[p].push_back((edge){q,l.v.len()});
				g[q].push_back((edge){p,l.v.len()});
			}
		}
		now.clear();
	}
	
}

int main() {
	scanf("%lf%lf%lf%lf",&s.x,&s.y,&t.x,&t.y);
	cin>>n;
	rep (i,1,n) {
		scanf("%lf%lf%lf",&C[i].c.x,&C[i].c.y,&C[i].r);
	}
	
	A[++tot]=s,A[++tot]=t;
	
	{
		Line l=Line(s,t-s);
		bool chk=true;
		rep (i,1,n) if (C[i].intersect(l)) chk=false;
		if (chk) {
			g[1].push_back(edge(2,l.v.len()));
			g[2].push_back(edge(1,l.v.len()));
		}
	}
	
	initST(1,s);
	initST(2,t);
	rep (i,1,n) {
		rep (j,i+1,n) {
			static vector <Point> Pi,Pj;
			C[i].Link(C[j],Pi,Pj);
			int l1=tot+1;
			repo (k,0,Pi.size()) {
				A[++tot]=Pi[k];
				poc[i].push_back(tot);
			}
			int l2=tot+1;
			repo (k,0,Pj.size()) {
				A[++tot]=Pj[k];
				poc[j].push_back(tot);
			}
			
			repo (k,0,Pi.size()) {
				int p=l1+k,q=l2+k;
				Line l=Line(A[p],A[q]-A[p]);
				bool chk=true;
				repo (c,1,n) if (C[c].intersect(l)) {
					chk=false;
					break;
				}
				if (chk) {
					g[p].push_back(edge(q,l.v.len()));
					g[q].push_back(edge(p,l.v.len()));
				}
			}
			
			Pi.clear();
			Pj.clear();
		}
	}
	
	rep (i,1,n) {
		Point c=C[i].c;
		PointCmp cmp;
		cmp.S=c;
		sort(poc[i].begin(),poc[i].end(),cmp);
		repo (k,1,poc[i].size()) {
			int p=poc[i][k-1],q=poc[i][k];
			double a=(A[q]-c).angle()-(A[p]-c).angle();
			if (a<0) continue;
			double d=C[i].getdist(a);
			g[p].push_back(edge(q,d));
			g[q].push_back(edge(p,d));
		}
		int p=poc[i][0],q=poc[i].back();
		double a=2*pi-((A[q]-c).angle()-(A[p]-c).angle());
		double d=C[i].getdist(a);
		g[p].push_back(edge(q,d));
		g[q].push_back(edge(p,d));
	}
	
	printf("%.1f\n",Dijkstra(1,2));
	
	return 0;
}
