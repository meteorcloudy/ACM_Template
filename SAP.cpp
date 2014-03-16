#include <cstdio>
#include <algorithm>
#include <string.h>
#define maxn 1500
#define oo 1000000000
#define clearAll(a) memset(a,0,sizeof(a))

using namespace std;

struct edge
{
    int next,pair;
    int v,cap,flow;
};

edge e[500005];

int n,m,s,t,cnt;
int first[maxn];
int numb[maxn];
int dist[maxn];
int cure[maxn];
int pre[maxn];
int F,D;
char s1[210][210],s2[210][210];

inline void addE(int x,int y,int f1,int f2)
{
    cnt++;
    e[cnt].next=first[x];
    e[cnt].v=y;
    e[cnt].pair=cnt+1;
    e[cnt].cap=f1;
    e[cnt].flow=0;
    first[x]=cnt;
    cnt++;
    e[cnt].next=first[y];
    e[cnt].v=x;
    e[cnt].pair=cnt-1;
    e[cnt].cap=f2;
    e[cnt].flow=0;
    first[y]=cnt;
}

inline void build()
{
    cnt=0;
	clearAll(first);
    int cap;
    for (int i=1;i<=F;i++)
    {
        scanf("%d",&cap);
        addE(s,i+2*n,cap,0);
    }
    for (int i=1;i<=D;i++)
    {
        scanf("%d",&cap);
        addE(i+2*n+F,t,cap,0);
    }

    for (int i=1;i<=n;i++)
        scanf("%s",s1[i]+1);
    for (int i=1;i<=n;i++)
        scanf("%s",s2[i]+1);
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=F;j++)
            if (s1[i][j]=='Y')
                addE(j+2*n,i,1,0);
        for (int j=1;j<=D;j++)
            if (s2[i][j]=='Y')
                addE(i+n,2*n+F+j,1,0);
        addE(i,i+n,1,0);
    }
}

int SAP()
{
    int cur_flow,max_flow,u,tmp,neck,i;
    clearAll(dist);
    clearAll(numb);
    clearAll(pre);
    for (int i=0;i<=t;i++)
        cure[i]=first[i];
    numb[t]=t;
    max_flow=0;
    u=s;
    while (dist[u]<t)
    {
        if (u==t)
        {
            cur_flow=oo;
            for (i=s;i!=t;i=e[cure[i]].v)
                if (cur_flow>e[cure[i]].cap)
                {
                    neck=i;
                    cur_flow=e[cure[i]].cap;
                }
            for (i=s;i!=t;i=e[cure[i]].v)
            {
                tmp=cure[i];
                e[tmp].cap-=cur_flow;
                e[tmp].flow+=cur_flow;
                tmp=e[tmp].pair;
                e[tmp].cap+=cur_flow;
                e[tmp].flow-=cur_flow;
            }
            max_flow+=cur_flow;
            u=neck;
        }

        for (i=cure[u];i;i=e[i].next)
            if (e[i].cap>0&&dist[u]==dist[e[i].v]+1)
                break;
        if (i)
        {
            cure[u]=i;
            pre[e[i].v]=u;
            u=e[i].v;
        } else
        {
            numb[dist[u]]--;
            if (numb[dist[u]]==0) break;
            cure[u]=first[u];
            for (tmp=t,i=first[u];i;i=e[i].next)
            if (e[i].cap>0)
            {
                tmp=min(tmp,dist[e[i].v]);
            }
            dist[u]=tmp+1;
            ++numb[dist[u]];
            if (u!=s) u=pre[u];
        }
    }
    return max_flow;
}

int main()
{
    while (scanf("%d%d%d",&n,&F,&D)==3)
    {
        s=n*2+F+D+1;
        t=s+1;

        build();
        printf("%d\n",SAP());
    }
}









