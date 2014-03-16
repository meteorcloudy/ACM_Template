#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <cmath>
#include <vector>
#include <cstring>
#include <list>
#include <ctime>
#include <sstream>
#include <ctime>
#define mod 1000000007
#define INF 10000
using namespace std;

const double pi = acos(-1.0);

const double eps = 1e-16;

struct Point
{
    double x,y;
    Point(){}
    Point(double _x,double _y)
    {
        x=_x,y=_y;
    }
    Point operator -(const Point &b)const
    {
        return Point(x-b.x,y-b.y);
    }
    double operator *(const Point &b)const
    {
        return x*b.y-y*b.x;
    }
    double operator &(const Point &b)const
    {
        return x*b.x+y*b.y;
    }
    void transXY(double B)
    {
        double tx = x,ty = y;
        x = tx*cos(B)-ty*sin(B);
        y = tx*sin(B)+ty*cos(B);
    }
};

struct Line
{
    Point s,e,d;
    double k;
    Line(){}
    Line(Point _s, Point _e)
    {
        s=_s,e=_e;
        k=atan2(e.y-s.y,e.x-s.x);
    }
    Point operator &(const Line &b)const
    {
        Point res=s;
        double t;
        t = ((s-b.s)*(b.s-b.e))/((s-e)*(b.s-b.e));
        res.x += (e.x-s.x)*t;
        res.y += (e.y-s.y)*t;
        return res;
    }
};

bool HPIcmp(Line a,Line b)
{
   // Point temp1(a.e.x-a.s.x,a.e.y-a.s.y),temp2(b.e.x-b.s.x,b.e.y-b.s.y),temp(1.0,0.0);
/*
    if(fabs(temp1*temp2)>eps)
    {
        if(temp*temp1>0&&temp*temp2<0)
            return 0;
        else if(temp*temp1<0&&temp*temp2>0)
            return 1;
        else
            return temp1*temp2<0;
    }
    else
        return ((a.s-b.s)*(b.e-b.s))<0;
*/
/*
    if(temp*temp1>0&&temp*temp2<0)
        return 0;
    else if(temp*temp1<0&&temp*temp2>0)
        return 1;
    if(fabs(temp1*temp2)>eps)
        return temp1*temp2<0;
    else
        return ((a.s-b.s)*(b.e-b.s))<0;
*/

    if(fabs(a.k-b.k)>eps)
        return a.k<b.k;
    else
        return ((a.s-b.s)*(b.e-b.s))<0;

}

Line Q[1600];
void HPI(Line line[],int n,Point res[],int &resn)
{
    int tot=n;
    sort(line,line+n,HPIcmp);
    tot=1;
    for(int i=1;i<n;i++)
        if(fabs(line[i].k-line[i-1].k)>eps)
            line[tot++]=line[i];
    int head=0,tail=1;
    Q[0]=line[0];
    Q[1]=line[1];
    resn=0;
    for(int i=2;i<tot;i++)
    {
        if(fabs((Q[tail].e-Q[tail].s)*(Q[tail-1].e-Q[tail-1].s))<
            eps||
            fabs((Q[head].e-Q[head].s)*(Q[head+1].e-Q[head+1].s))<
                eps)
            return;
        while(head<tail&&(((Q[tail]&Q[tail-1])-line[i].s)*(
            line[i].e-line[i].s))>eps)
            tail--;
        while(head<tail&&(((Q[head]&Q[head+1])-line[i].s)*(
            line[i].e-line[i].s))>eps)
            head++;
        Q[++tail]=line[i];
    }
    while(head<tail&&(((Q[tail]&Q[tail-1])-Q[head].s)*(Q[
        head].e-Q[head].s))>eps)
        tail--;
    while(head<tail&&(((Q[head]&Q[head+1])-Q[tail].s)*(Q[
        tail].e-Q[tail].s))>eps)
        head++;
    if(tail<=head+1)return;
    for(int i=head;i<tail;i++)
        res[resn++]=Q[i]&Q[i+1];
    if(head<tail+1)
        res[resn++]=Q[head]&Q[tail];
}

double CalcArea(Point p[],int n)
{
    double res=0.0f;
    for(int i=0;i<n;i++)
        res+=(p[i]*p[(i+1)%n])/2;
    return res;
}

double x[110],y[110],z[110];

Point res[110],p1,p2;

Line line[110];

int resn;

double X[110],Y[110],Z[110];

int main()
{
    int n,i,j,k,flag;
    double delta,deltb,deltc,xx,yy;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%lf%lf%lf",&X[i],&Y[i],&Z[i]);
        X[i]=1.0/X[i];
        Y[i]=1.0/Y[i];
        Z[i]=1.0/Z[i];
    }
    for(i=0;i<n;i++)
    {
        flag=0;
        k=0;
        for(j=0;j<n;j++)
        {
            if(i==j)
                continue;
            delta=X[i]-X[j];
            deltb=Y[i]-Y[j];
            deltc=Z[j]-Z[i];
            if(fabs(deltc)>eps)
            {
                if(fabs(delta)<eps&&fabs(deltb)<eps)
                {
                    if(deltc<-eps)
                    {
                        flag=1;
                        break;
                    }
                }
                else if(fabs(deltb)>eps)
                {
                    p1=Point(0,deltc/deltb);
                    p2=Point(1,(deltc-delta)/deltb);
                    if(deltc/deltb>eps)
                    {
                        if(deltc<0)
                            line[k++]=Line(p1,p2);
                        else
                            line[k++]=Line(p2,p1);
                    }
                    else
                    {
                        if(deltc>0)
                            line[k++]=Line(p1,p2);
                        else
                            line[k++]=Line(p2,p1);
                    }
                }
                else
                {
                    p1=Point(deltc/delta,0);
                    p2=Point(deltc/delta,1);
                    if(deltc/delta>eps)
                    {
                        if(deltc>0)
                            line[k++]=Line(p1,p2);
                        else
                            line[k++]=Line(p2,p1);
                    }
                    else
                    {
                        if(deltc<0)
                            line[k++]=Line(p1,p2);
                        else
                            line[k++]=Line(p2,p1);
                    }
                }
            }
            else
            {
                if(fabs(delta)>eps)
                {
                    p1=Point(0,0);
                    p2=Point(-deltb/delta,1);
                    if(delta>0)
                        line[k++]=Line(p1,p2);
                    else
                        line[k++]=Line(p2,p1);
                }
                else
                {
                    p1=Point(0,0);
                    p2=Point(-1,0);
                    if(fabs(deltb)>eps)
                    {
                        if(deltb>0)
                            line[k++]=Line(p1,p2);
                        else
                            line[k++]=Line(p2,p1);
                    }
                    else
                    {
                        flag=1;
                        break;
                    }
                }
            }
        }
        if(flag==1)
        {
            printf("No\n");
            continue;
        }
        p1.x=0.0f;
        p1.y=0.0f;
        p2.x=1.0f;
        p2.y=0.0f;
        line[k++]=Line(p1,p2);
        p1.x=0.0f;
        p1.y=1.0f;
        p2.x=0.0f;
        p2.y=0.0f;
        line[k++]=Line(p1,p2);
        p1.x=1000000.0f;
        p1.y=0.0f;
        p2.x=1000000.0f;
        p2.y=1000000.0f;
        line[k++]=Line(p1,p2);
        p1.x=1000000.0f;
        p1.y=1000000.0f;
        p2.x=0.0f;
        p2.y=1000000.0f;
        line[k++]=Line(p1,p2);
        HPI(line,k,res,resn);
        if(fabs(CalcArea(res,resn))<eps)
            printf("No\n");
        else
            printf("Yes\n");
    }
    return 0;
}
