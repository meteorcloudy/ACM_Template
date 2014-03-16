#include <iostream>
#include <stdio.h>
#define maxn 100005
#define oo 1000000000
#define LL (2*id)
#define RR (2*id+1)
using namespace std;


struct node
{    long long sum,max;
    int l,r;
    long long lazy;
};

node t[4*maxn];

int n,q;
long long ans,maxx;

void build(int id,int x,int y)
{    
    t[id].l=x; t[id].r=y; t[id].sum=0; t[id].lazy=0; t[id].max=-oo;

    if (x==y)  return ;
    
    int mid=(x+y)/2;
    build(LL,x,mid);
    build(RR,mid+1,y);
}

void pushdown(int id)
{    if (t[id].l!=t[id].r&&t[id].lazy!=0)
    {
        t[LL].sum   += t[id].lazy*(t[LL].r-t[LL].l+1);
        t[RR].sum += t[id].lazy*(t[RR].r-t[RR].l+1);
        t[LL].lazy   += t[id].lazy;
        t[RR].lazy += t[id].lazy;
        t[LL].max+=t[id].lazy;
        t[RR].max+=t[id].lazy;
    }
    t[id].lazy=0;
}

long long max(long long x, long long y)
{    if (x>y) return x;
    return y;
}

void update(int id)
{   t[id].sum=t[LL].sum+t[RR].sum;
    t[id].max=max(t[LL].max,t[RR].max);
}

void change(int id,int x,int y,int v) // 区间[x,y]整体加上v
{
    if (x<=t[id].l&&t[id].r<=y)
    {   t[id].sum+=(t[id].r-t[id].l+1)*v;
        t[id].lazy+=v;
        t[id].max+=v;
        if (t[id].l==t[id].r) t[id].max=t[id].sum;
        return;
    }
    if (t[id].l==t[id].r)  return;

    pushdown(id);
    int mid=(t[id].l+t[id].r)/2;
    if (x<=mid) change(LL,x,y,v);
    if (y>mid) change(RR,x,y,v);
    update(id);
}

void ask(int id,int x,int y) //询问区间[x,y]
{
	if (x>t[id].r||y<t[id].l) return;
	if (x<=t[id].l&&t[id].r<=y)
	{	ans+=t[id].sum;
		maxx=max(maxx,t[id].max);
		return;
	}
	if (t[id].l==t[id].r) return;
	pushdown(id);
	int mid=(t[id].l+t[id].r)/2;
	if (x>mid) { ask(RR,x,y); return; }
	if (y<=mid) {  ask(LL,x,y); return; }
	ask(LL,x,y);
	ask(RR,x,y);
}

int query(int id,int x)     //询问点x
{   if (t[id].l==t[id].r) return t[id].l;
    pushdown(id);
    if (t[RR].max>=x) return query(RR,x);
    if (t[LL].max>=x) return query(LL,x);
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
