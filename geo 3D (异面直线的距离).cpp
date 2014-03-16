#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <string>
#include <queue>
#include <vector>
#include <set>
#define maxn
#define eps 1e-8
#define oo 1000000000
#define clearAll(a) memset(a,0,sizeof(a))
#define sq(a) ((a)*(a))

using namespace std;

typedef long long ll;

struct Vect
{
	double x,y,z;
	Vect() { x=y=z=0.0f; }
	Vect(double _x,double _y,double _z) : x(_x),y(_y),z(_z) {}

	double operator * (Vect v)
	{	return x*v.x+y*v.y+z*v.z; }

	Vect operator & (Vect v)
	{	return Vect(y*v.z-v.y*z,-(x*v.z-v.x*z),x*v.y-v.x*y); }

	Vect operator + (Vect v)
	{	return Vect(x+v.x,y+v.y,z+v.z); }

	Vect operator * (double l)
    {
        Vect res(x*l,y*l,z*l);
        return res;
    }

	Vect operator - (Vect v)
	{	return Vect(x-v.x,y-v.y,z-v.z); }

	double length()
	{ return sqrt(sq(x)+sq(y)+sq(z)); }
};

typedef Vect Point;

struct Line
{
	Point a,b;
	Line() {}
	Line(Point &x,Point &y)
	{ a=x; b=y;	}

	Point operator & (Line &s)
	{
		Vect x=b-a,y=s.b-s.a,z=s.a-a;
		double t=(y&z).length()/(y&x).length();
		return a+x*t;
	}
};

struct Plane
{
	Point a,b,c;
	Plane() {}
	Plane(Point _a,Point _b,Point _c)
	{
		a=_a;
		b=_b;
		c=_c;
	}

	Vect pverti()
	{
		return (a-b)&(b-c);
	}
};

Point find(Line l,Plane s)
{
	Point tmp=(s.a-s.b)&(s.b-s.c);

	double t1=(tmp.x*(s.a.x-l.a.x)+tmp.y*(s.a.y-l.a.y)+tmp.z*(s.a.z-l.a.z));
	double t2=(tmp.x*(l.b.x-l.a.x));
	t2+=(tmp.y*(l.b.y-l.a.y));
	t2+=(tmp.z*(l.b.z-l.a.z));
    double t=t1/t2;
	tmp.x=l.a.x+(l.b.x-l.a.x)*t;
	tmp.y=l.a.y+(l.b.y-l.a.y)*t;
	tmp.z=l.a.z+(l.b.z-l.a.z)*t;

	return tmp;
}


Point p[5][2];
Vect v[5];
Point p1,p2;

int main()
{
    freopen("C:\\Users\\py\\Desktop\\input.txt","r",stdin);
    //freopen("C:\\Users\\py\\Desktop\\output.txt","w",stdout);

    int tt;

    scanf("%d",&tt);

    while (tt--)
    {
    	int n;

    	for (int i=1;i<=2;i++)
    		for (int j=0;j<2;j++)
    			scanf("%lf%lf%lf",&p[i][j].x,&p[i][j].y,&p[i][j].z);

    	for (int i=1;i<=2;i++)
    		v[i]=p[i][1]-p[i][0];

    	double ans = oo;

    	Vect dir = v[1]&v[2];

    	Vect w = p[1][0]-p[2][0];
    	ans = fabs(dir*w/dir.length());

    	Line l1(p[1][0],p[1][1]);
    	Line l2(p[2][0],p[2][1]);

    	p2 = find(l2,Plane(p[1][0],p[1][1],p[1][1]+dir));
    	p1 = find(l1,Plane(p[2][0],p[2][1],p[2][1]+dir));

    	printf("%.6f\n",ans);
    	printf("%.6f %.6f %.6f ",p1.x,p1.y,p1.z);
    	printf("%.6f %.6f %.6f\n",p2.x,p2.y,p2.z);
    }

    return 0;
}
