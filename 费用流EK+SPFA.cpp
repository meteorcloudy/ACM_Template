#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <set>
#define maxn 55
#define maxm 500
#define clearAll(a) memset(a,0,sizeof(a))
#define oo 1000000000
using namespace std;

typedef long long ll;

int n,m,k;
int need[maxn][maxn];
int supply[maxn][maxn];
int fee[maxn][maxn][maxn];

int s,t,cnt;
struct edge
{
    int next,pair;
    int u,v,cap,flow,cost;
};

edge e[10000];

int first[maxm];
int d[maxm];
bool inq[maxm];
int pre[maxm];
ll low;

inline void addE(int x,int y,int f1,int f2,int c1,int c2)
{
    cnt++;
    e[cnt].next=first[x];
    e[cnt].u=x;
    e[cnt].v=y;
    e[cnt].pair=cnt+1;
    e[cnt].cap=f1;
    e[cnt].cost=c1;
    e[cnt].flow=0;
    first[x]=cnt;
    cnt++;
    e[cnt].next=first[y];
    e[cnt].u=y;
    e[cnt].v=x;
    e[cnt].pair=cnt-1;
    e[cnt].cap=f2;
    e[cnt].cost=c2;
    e[cnt].flow=0;
    first[y]=cnt;
}

inline bool spfa()
{
    queue<int> q;
	for (int i=1;i<=t;i++) d[i]=(i==s?0:oo);
	clearAll(pre);
	clearAll(inq);
	q.push(s);
	while (!q.empty())
	{	int x=q.front();  q.pop();
		inq[x]=false;
		for (int i=first[x];i;i=e[i].next)
		{
		    int v=e[i].v;
            if ((d[v]>d[x]+e[i].cost)&&(e[i].flow<e[i].cap))
            {	d[v]=d[x]+e[i].cost;
                pre[v]=i;
                if (!inq[v])
                {	inq[v]=true;
                    q.push(v);
                }
            }
		}
	}
	return d[t]<oo;
}


ll MinCost()
{
    ll Min=0;
    ll maxflow=0;
    while (spfa())
    {
        int add=oo;
        for (int i=pre[t];i;i=pre[e[i].u])
        {
            add=min(e[i].cap-e[i].flow,add);
        }
        maxflow+=add;
        for (int i=pre[t];i;i=pre[e[i].u])
        {
            e[i].flow+=add;
            e[e[i].pair].flow-=add;
            Min+=add*e[i].cost;
        }
    }
   // if (maxflow<low) return -1;
    return Min;
}

void build(int x)
{
    clearAll(first);
    low=0;
    cnt=0;
    s=n+m+1; t=s+1;
    for (int i=1;i<=n;i++)
    {
        addE(s,i,need[i][x],0,0,0);
        low+=need[i][x];
    }
    for (int i=1;i<=m;i++)
        addE(i+n,t,supply[i][x],0,0,0);
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
        addE(i,j+n,oo,0,fee[x][i][j],-fee[x][i][j]);
}


int main()
{

    while (scanf("%d%d%d",&n,&m,&k)==3)
    {
        if (n==0&&m==0&&k==0)
            break;
        for (int i=1;i<=n;i++)
            for (int j=1;j<=k;j++)
            scanf("%d",&need[i][j]);
        for (int i=1;i<=m;i++)
            for (int j=1;j<=k;j++)
            scanf("%d",&supply[i][j]);
        for (int t=1;t<=k;t++)
            for (int i=1;i<=n;i++)
                for (int j=1;j<=m;j++)
                scanf("%d",&fee[t][i][j]);
        ll ans=0;
        for (int i=1;i<=k;i++)
        {
            build(i);
            ll tmp = MinCost();
            if (tmp==-1)
            {
                ans=-1;
                break;
            }
            ans+=tmp;
        }
        cout << ans <<endl;
    }
}





























