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
#define MAXNODE 205
#define MAXLINE 205
#define oo 1000000000
#define eps (1e-8)
#define clearAll(a) memset(a,0,sizeof(a))
#define sq(a) ((a)*(a))

using namespace std;

typedef long long ll;

struct Vect // basic structer
{
  double x,y;
	Vect ()
	{ x=y=0.0; }
	Vect (double xx,double yy)
	{ x=xx; y=yy; }

	Vect operator + (const Vect &v) const
	{	Vect res(x+v.x,y+v.y);
		return res;
	}

	Vect operator - (const Vect &v) const
	{	Vect res(x-v.x,y-v.y);
		return res;
	}

	Vect operator * (double l)
    {
        Vect res(x*l,y*l);
        return res;
    }

	double operator * (const Vect &v) const
	{
		return v.x*x+v.y*y;
	}

	double operator & (const Vect &v) const
	{
		return x*v.y-y*v.x;
	}

	void Rotate(double B)
	{
		double tx = x, ty = y;
		x = tx*cos(B) - ty*sin(B);
		y = ty*sin(B) + ty*cos(B);
	}
};

struct Point // basic structer
{
	double x,y;
	Point ()
	{ x=y=0.0; }
	Point (double xx,double yy)
	{ x=xx; y=yy; }

	void setPoint (double xx,double yy)
	{ x=xx; y=yy; }

	Vect operator - (Point &a)
	{ 	Vect res(x-a.x,y-a.y);
		return res;
	}

	Point operator + (Vect &v)
	{
	    Point res(x+v.x,y+v.y);
	    return res;
	}

	Point operator - (Vect &v)
	{
        Point res(x-v.x,y-v.y);
	    return res;
	}

	bool operator == (Point a)
	{
		return fabs(x-a.x)<eps&&fabs(y-a.y)<eps;
	}
};

struct Segment // Point is needed;
{
	Point a,b;
	Segment() {}
	Segment(Point &x,Point &y)
	{ a=x; b=y;}
	Segment(double x1,double y1,double x2,double y2)
	{ a.x=x1; a.y=y1; b.x=x2; b.y=y2;}
};

struct Circle	// Point is needed;
{
	Point c;
	double r;
	Circle() { r=1.0; }
	Circle(Point &cc,double R) { c=cc; r=R; }
	Circle(double x,double y,double r) { c.x=x,c.y=y,r=r;}
};

struct Polygon 	// Point is needed; MAXNODE should be defined; the Points is clockwise or anti-clockwise;
{
	int n;
	Point a[MAXNODE];
};

struct Line
{
	Point a,b;
	double k;
	double A,B,C;

	Line() {}
	Line(Point &x,Point &y)
	{ a=x; b=y;
	  k = atan2(b.y-a.y,b.x-a.x);
	}
	Line(double x1,double y1,double x2,double y2)
	{ a.x=x1; a.y=y1; b.x=x2; b.y=y2;}

	Point operator & (Line &s)		// line interset
	{
		double t = ((a-s.a)&(s.a-s.b))/((a-b)&(s.a-s.b));
		Point res = a;
		res.x += (b.x-a.x)*t;
		res.y += (b.y-a.y)*t;
		return res;
	}

	void setLine(Point &x,Point &y)
	{ a=x; b=y;
	  k = atan2(b.y-a.y,b.x-a.x);
	}


	void setLine(double x1,double y1,double x2,double y2)
	{ a.x=x1; a.y=y1; b.x=x2; b.y=y2;
	  k = atan2(b.y-a.y,b.x-a.x);
	}

};

struct Geometry
{
	static double length(Vect &v)
	{ return sqrt(v.x*v.x+v.y+v.y); }

	static double length(Segment &s)
	{ double x = s.a.x-s.b.x;
	  double y = s.a.y-s.b.y;
	  return sqrt(x*x+y*y);
	}

	static double dist(Point &a,Point &b)
	{ double x = a.x-b.x;
	  double y = a.y-b.y;
	  return sqrt(x*x+y*y);
	}
	
	static bool isPotOnSeg(Point &a,Segment &s)
	{
		if (fabs((a-s.a)&(s.b-s.a))>eps) return false;
		bool flag1 = min(s.a.x,s.b.x)-eps<a.x&&a.x<max(s.a.x,s.b.x)+eps;
		bool flag2 = min(s.a.y,s.b.y)-eps<a.y&&a.y<max(s.a.y,s.b.y)+eps;
		return flag1&&flag2;
	}

	static bool isPotOnLine(Point &a,Line &s)
	{
		return (fabs((a-s.a)&(s.b-s.a))<eps);
	}

	static bool HPIcmp(Line a,Line b)
	{
		if (fabs(a.k-b.k)>eps) return a.k<b.k;
		return ((a.a-b.a)&(b.b-b.a))<0;
	}

	static void HPI(Line line[],int n,Point res[],int &resn) // line[] 0 ~ n-1 , MAXLINE should be defined
	{
		Line q[MAXLINE];
		int tot = n;
		sort(line,line+n,HPIcmp);
		tot = 1;
		for (int i=1;i<n;i++)
			if (fabs(line[i].k-line[i-1].k)>eps)
				line[tot++]=line[i];
		int l=0,r=1;
		q[0]=line[0]; q[1]=line[1];
		resn = 0;
		for (int i=2;i<tot;i++)
		{
			if (fabs((q[r].b-q[r].a)&(q[r-1].b-q[r-1].a))<eps
			  ||fabs((q[l].b-q[l].a)&(q[l+1].b-q[l+1].a))<eps)
			return;

			while (l<r&&(((q[r]&q[r-1])-line[i].a)&(line[i].b-line[i].a))>eps)
				r--;

			while (l<r&&(((q[l]&q[l+1])-line[i].a)&(line[i].b-line[i].a))>eps)
				l++;

			q[++r]=line[i];
		}

		while (l<r&&(((q[r]&q[r-1])-line[l].a)&(line[l].b-line[l].a))>eps)
			r--;

		while (l<r&&(((q[l]&q[l+1])-line[r].a)&(line[r].b-line[r].a))>eps)
			l++;

		if (r<=l+1) return;

		for (int i=l;i<r;i++)
			res[resn++]=q[i]&q[i+1];

		if (l<r+1)
			res[resn++]=(q[l]&q[r]);
	}

	static double AreaOfPolygon(Polygon A)
	{
		double area = 0.0f;

		Point O = A.a[0];
		for (int i=0;i<A.n;i++)
			area += (A.a[i]-O)&(A.a[(i+1)%A.n]-O);

		return fabs(area/2.0);
	}
};



int main()
{
    freopen("C:\\Users\\py\\Desktop\\input.txt","r",stdin);
    //freopen("C:\\Users\\py\\Desktop\\output.txt","w",stdout);

    Line l1(100099,100099,100100,100100);
    //Line l2(0,1,-1,2);
    Line l2(-101,102,-100,101);
    Point res = l2&l1;

    cout << res.x <<" " <<res.y <<endl;
    return 0;
}
