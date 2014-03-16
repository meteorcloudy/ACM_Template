#include<iostream>
#include<stdio.h>
#define maxn 100005
#define oo 1000000000
using namespace std;

typedef long long ll;

struct node
{    ll x,max;
    int a,b;
    ll add;
};

node t[4*maxn];

int n,q;
ll ans,maxx;

void build(int now,int x,int y)
{    if (x==y)
    {    t[now].a=x; t[now].b=y; t[now].x=0; t[now].add=0; t[now].max=-oo;
        return ;
    }

    t[now].a=x; t[now].b=y; t[now].x=0; t[now].add=0; t[now].max=-oo;
    int mid=(x+y)/2;
    build(2*now,x,mid);
    build(2*now+1,mid+1,y);
}

void pushdown(int now)
{    if (t[now].a!=t[now].b&&t[now].add!=0)
    {
        t[2*now].x   += t[now].add*(t[2*now].b-t[2*now].a+1);
        t[2*now+1].x += t[now].add*(t[2*now+1].b-t[2*now+1].a+1);
        t[2*now].add   += t[now].add;
        t[2*now+1].add += t[now].add;
        t[2*now].max+=t[now].add;
        t[2*now+1].max+=t[now].add;
    }
    t[now].add=0;
}

long long max(long long x, long long y)
{    if (x>y) return x;
    return y;
}

void update(int now)
{   t[now].x=t[2*now].x+t[2*now+1].x;
    t[now].max=max(t[2*now].max,t[2*now+1].max);
}

void change(int now,int x,int y,int v)
{
    if (x<=t[now].a&&t[now].b<=y)
    {    t[now].x+=(t[now].b-t[now].a+1)*v;
        t[now].add+=v;
        t[now].max+=v;
        if (t[now].a==t[now].b) t[now].max=t[now].x;
        return;
    }
    if (t[now].a==t[now].b)  return;

    pushdown(now);
    int mid=(t[now].a+t[now].b)/2;
    if (x<=mid) change(2*now,x,y,v);
    if (y>mid) change(2*now+1,x,y,v);
    update(now);
}

void ask(int now,int x,int y)
{
	if (x>t[now].b||y<t[now].a) return;
	if (x<=t[now].a&&t[now].b<=y)
	{	ans+=t[now].x;
		maxx=max(maxx,t[now].max);
		return;
	}
	if (t[now].a==t[now].b) return;
	pushdown(now);
	int mid=(t[now].a+t[now].b)/2;
	if (x>mid) { ask(2*now+1,x,y); return; }
	if (y<=mid) {  ask(2*now,x,y); return; }
	ask(2*now,x,y);
	ask(2*now+1,x,y);
}

int query(int now,int x)
{   if (t[now].a==t[now].b) return t[now].a;
    pushdown(now);
    if (t[2*now+1].max>=x) return query(2*now+1,x);
    if (t[2*now].max>=x) return query(2*now,x);
    return -1;
}

void init()
{    scanf("%d %d",&n,&q);
    build(1,1,n);
    for (int i=1;i<=n;i++)
    {    int x;
        scanf("%d",&x);
        change(1,i,i,x);
    }
    string s;
    for (int i=1;i<=q;i++)
    {
        getline(cin,s);
        cin >> s;
        if (s=="query")
        {    int x;
            scanf("%d",&x);

            printf("%d\n",query(1,x));
        } else
        if (s=="change")
        {    int x,y;
            scanf("%d %d",&x,&y);
            ans=0;
            ask(1,x,x);
            int tmpx=ans;
            ans=0;
            ask(1,y,y);
            int tmpy=ans;
            change(1,x,x,-tmpx+tmpy);
            change(1,y,y,-tmpy+tmpx);

        } else
        {    int x,y,v;
            scanf("%d %d %d",&x,&y,&v);
            change(1,x,y,v);
/*            for (int j=1;j<=n;j++)
            {   ans=0;  maxx=-1000000000;
                ask(1,j,j);
                cout << ans << " " <<maxx <<endl;
            }*/
        }
    }
}

int main()
{    int tt;
    scanf("%d",&tt);
    for (int i=1;i<=tt;i++)
        init();
    return 0;
}
