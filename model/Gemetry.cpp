#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <algorithm>
#include <iostream>
#include <string>
#include <set>

using namespace std;

typedef long long LL ;


struct point
{
    double x,y;
    point(){}
    point(LL _x,LL _y)
    {
        x=_x;
        y=_y;
    }
    LL dot(point p)      //as vector , the dot ;
    {
        return p.x*x + p.y*y;
    }
    LL mulx(point p)   // as vector , the mulx ,
    {
        return p.x*y - x*p.y;
    }
    double get_dis(point p)  //
    {
        return sqrt( (x-p.x)*(x-p.x) + (y-p.y)*(y-p.y) );
    }
    double get_dis()
    {
        return sqrt( x*x + y*y );
    }
    void ratote(double alpha)   // counterclockwise ratote by rad ;
    {
        LL rx,ry;
        rx = cos(alpha)*x - sin(alpha)*y ;
        ry = sin(alpha)*x + cos(alpha)*y ;
        x=rx,y=ry;
    }
    void move(point p)   // translation by vector p;
    {
        x += p.x;
        y += p.y;
    }
};

struct line
{
    point st,ed;
    double A,B,C;
    line(){}
    line(point _st,point _ed)
    {
        st=_st;
        ed=_ed;
        A = st.y - ed.y;
        B = ed.x - st.x;
        C = (st.y-ed.y)*st.x - (st.x-ed.x)*st.y;
    }
    double get_dis_from_point(point p)  //  the distance from a point to the line
    {
        return fabs( A*p.x + B*p.y + C ) / ( A*A + B*B );
    }
    point cross(line l)
    {
        point ret ;
        double A1=A, B1=B, C1=C;
        double A2=l.A, B2=l.B, C2=l.C;
        double ex1 = A2;
        double ex2 = A1;
        A1*=ex1,B1*=ex1,C1*=ex1;
        A2*=ex2,B2*=ex2,C2*=ex2;

    }
};

int main()
{
    point a(3,0);
    printf("%lld %lld\n",a.x,a.y);
    double c = acos(-1.0)/2;
    a.ratote(c);
    printf("%lld %lld\n",a.x,a.y);
	return 0;
}
